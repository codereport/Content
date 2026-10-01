#!/usr/bin/env python3
"""Show a clean live desktop and restore its workspace when the talk ends."""
import json
import os
from pathlib import Path
import re
import subprocess
import sys

STATE = Path(os.environ.get("XDG_RUNTIME_DIR", f"/run/user/{os.getuid()}")) / "post-code-session.json"
WORKSPACE = "name:post-code-presentation"


def hypr(*args):
    result = subprocess.run(["hyprctl", *args], capture_output=True, text=True, check=True)
    if any(line.lstrip().lower().startswith(("error:", "invalid ")) for line in result.stdout.splitlines()):
        raise RuntimeError(result.stdout.strip())
    return result.stdout


def enter(monitor):
    if not re.fullmatch(r"[A-Za-z0-9_-]+", monitor):
        raise ValueError("Invalid monitor name")
    if STATE.exists():
        leave()
    monitors = json.loads(hypr("monitors", "-j"))
    selected = next((item for item in monitors if item["name"] == monitor), None)
    if selected is None:
        raise ValueError(f"Monitor {monitor} is disconnected")
    # The overlay is transparent: use a dedicated empty workspace so ordinary
    # applications do not sit between the wallpaper and the presentation.
    clients = json.loads(hypr("clients", "-j"))
    if any(item["workspace"]["name"] == WORKSPACE.removeprefix("name:") for item in clients):
        raise ValueError("The presentation workspace contains a window; move it before starting.")
    focused = next((item for item in monitors if item.get("focused")), selected)
    previous = selected["activeWorkspace"]
    workspace = str(previous["id"]) if previous["id"] > 0 else "name:" + previous["name"]
    STATE.write_text(json.dumps({"monitor": monitor, "workspace": workspace,
        "focused": focused["name"]}))
    STATE.chmod(0o600)
    try:
        hypr("eval", f'hl.dispatch(hl.dsp.focus({{ monitor = "{monitor}" }})); '
            f'hl.dispatch(hl.dsp.focus({{ workspace = "{WORKSPACE}" }})); '
            f'hl.dispatch(hl.dsp.workspace.move({{ monitor = "{monitor}" }}))')
    except Exception:
        leave()
        raise


def leave():
    if not STATE.exists():
        return
    state = json.loads(STATE.read_text())
    monitors = json.loads(hypr("monitors", "-j"))
    selected = next((item for item in monitors if item["name"] == state["monitor"]), None)
    if selected and selected["activeWorkspace"]["name"] == WORKSPACE.removeprefix("name:"):
        hypr("eval", f'hl.dispatch(hl.dsp.focus({{ monitor = "{state["monitor"]}" }})); '
            f'hl.dispatch(hl.dsp.focus({{ workspace = {json.dumps(state["workspace"], ensure_ascii=False)} }}))')
        if any(item["name"] == state["focused"] for item in monitors):
            hypr("eval", f'hl.dispatch(hl.dsp.focus({{ monitor = "{state["focused"]}" }}))')
    STATE.unlink(missing_ok=True)


if __name__ == "__main__":
    try:
        if sys.argv[1] == "enter":
            enter(sys.argv[2])
        elif sys.argv[1] == "exit":
            leave()
        else:
            raise ValueError("Expected enter <monitor> or exit")
    except Exception as error:
        print(error, file=sys.stderr)
        sys.exit(1)
