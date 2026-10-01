#!/usr/bin/env python3
"""Install project-owned plugin files and integrate the cloned bar widgets."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import time

PROJECT = Path(__file__).resolve().parents[1]
CONFIG = Path.home() / ".config"
PLUGINS = CONFIG / "omarchy/plugins"
DEST = PLUGINS / "cph.presentations"


def install():
    stamp = str(int(time.time()))
    for path in [CONFIG / "hypr/bindings.lua", CONFIG / "omarchy/shell.json"]:
        shutil.copy2(path, path.with_name(path.name + ".bak.post-code." + stamp))
    # Clone through Omarchy's supported workflow. Its usual two-second IPC
    # timeout is too short for a full plugin rescan on this desktop.
    for source in ["clock", "weather"]:
        target = PLUGINS / ("cph." + source)
        if not target.exists():
            subprocess.run(["omarchy", "plugin", "clone", "omarchy." + source],
                env={**os.environ, "OMARCHY_SHELL_IPC_TIMEOUT": "20s"}, check=True)
    shutil.copytree(PROJECT / "plugin", DEST, dirs_exist_ok=True)
    old_config_link = DEST / "presentations.json"
    if old_config_link.is_symlink():
        old_config_link.unlink()
    (DEST / "Location.js").write_text("var projectConfigPath = " + json.dumps(str(PROJECT / "presentations.json")) + "\n")
    helper = Path.home() / ".local/bin/post-code-session"
    helper.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(PROJECT / "scripts/desktop-session.py", helper)
    helper.chmod(0o755)

    clock = PLUGINS / "cph.clock/BarWidget.qml"
    text = clock.read_text()
    if 'import "../cph.presentations" as Presentation' not in text:
        text = text.replace("import QtQuick\n", 'import QtQuick\nimport "../cph.presentations" as Presentation\n', 1)
        text = text.replace("readonly property string displayText: formatted(displayDate)",
            'readonly property bool presenting: Presentation.PresentationState.active\n'
            '  readonly property string displayText: presenting ? "PRESENTATION MODE" : formatted(displayDate)')
        text = text.replace("if (b === Qt.RightButton) root.cycleFormat()", "if (root.presenting) return\n      if (b === Qt.RightButton) root.cycleFormat()")
        clock.write_text(text)
    weather = PLUGINS / "cph.weather/BarWidget.qml"
    text = weather.read_text()
    if 'import "../cph.presentations" as Presentation' not in text:
        text = text.replace("import QtQuick\n", 'import QtQuick\nimport "../cph.presentations" as Presentation\n', 1)
        text = text.replace('visible: panelLoader.item && panelLoader.item.label !== ""',
            'visible: !Presentation.PresentationState.active && panelLoader.item && panelLoader.item.label !== ""')
        weather.write_text(text)

    shell_path = CONFIG / "omarchy/shell.json"
    shell = json.loads(shell_path.read_text())
    if not any(item.get("id") == "cph.presentations" for item in shell.get("plugins", [])):
        shell.setdefault("plugins", []).append({"id": "cph.presentations"})
    shell["bar"]["centerAnchor"] = "cph.clock"
    shell_path.write_text(json.dumps(shell, indent=2) + "\n")

    bindings = CONFIG / "hypr/bindings.lua"
    text = bindings.read_text()
    if "-- POST CODE presentations" not in text:
        text += '\n-- POST CODE presentations (SUPER + P previously toggled pseudo windows).\n'
        text += 'hl.unbind("SUPER + P")\n'
        text += 'o.bind("SUPER + P", "Presentations", "omarchy-shell cph.presentations toggle")\n'
        bindings.write_text(text)
    subprocess.run(["hyprctl", "reload"], check=True)
    errors = subprocess.check_output(["hyprctl", "configerrors"], text=True).strip()
    if errors:
        raise RuntimeError(errors)
    subprocess.run(["omarchy-shell", "shell", "rescanPlugins"],
        env={**os.environ, "OMARCHY_SHELL_IPC_TIMEOUT": "20s"}, check=True)
    # This host retains cached QML services after a rescan. Restart once the
    # complete tree is installed, so both fresh installs and updates use it.
    subprocess.run(["omarchy", "restart", "shell"], check=True)
    for _ in range(40):
        result = subprocess.run(["omarchy-shell", "cph.presentations", "status"], capture_output=True, text=True)
        try:
            ready = json.loads(result.stdout)
            if ready.get("presentations", 0) > 0:
                break
        except json.JSONDecodeError:
            pass
        time.sleep(0.1)
    else:
        raise RuntimeError("Presentation plugin did not load its presentation list")
    print("Installed POST CODE. Super+P opens the chooser.")


if __name__ == "__main__":
    install()
