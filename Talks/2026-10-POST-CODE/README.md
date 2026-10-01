# POST CODE

A transparent native presentation on your live desktop, built with Quickshell
and integrated into your Omarchy shell. The wallpaper is supplied by the desktop;
the presentation draws only text and the parrot.

## Controls

| Control | Action |
| --- | --- |
| Super+P | Open or close the presentation chooser |
| Enter in the chooser | Start POST CODE |
| Space / Enter / Right / Page Down / left click | Play or replay the parrot entrance |
| Left / Backspace / Home / right click | Return to the title |
| Escape | Close the chooser, or end the presentation |

The title holds until you advance. The parrot peeks up from the bottom, takes
off, flies two figure-eight laps, then replaces the title and hovers in the
middle. Its wings keep flapping. The date/time and weather become
`PRESENTATION MODE` in the bar. The presentation uses a dedicated empty workspace
on DP-4 and inhibits idle while active. Exiting restores the previous workspace.

Edit [presentations.json](presentations.json) to change the title, byline, date,
monitor, or add another presentation to the chooser. The requested placeholder
is `Oct xx, 2025`.

## Install and develop

Run `python scripts/install.py` to install or update the plugin. It backs up the
user's bar and keybinding config, clones the clock and weather widgets via
Omarchy, installs project-owned files under `~/.config/omarchy/plugins/`, and
restarts the shell to load the complete plugin.
End the presentation before reinstalling. No packaged Omarchy files are edited.

The installed copies of `cph.clock` and `cph.weather` import the shared
`PresentationState` singleton, so entering and exiting update the bar without
rewriting its layout during a talk. Normal clock/calendar and weather behavior
continues outside presentation mode.

The parrot's native SVG parts follow the logo in
`~/Work/nvlabs-parrot/docs/_static/logo.png`; the wings have independent shoulder
pivots. Its flight timeline is in `plugin/Flight.js`.

The chooser, byline, and date use bundled JetBrains Mono. POST CODE uses Russo One
at its regular weight for naturally thick, boxy lettering. The chooser has square corners
and a translucent background. Font licenses are in `plugin/assets/fonts/`.

IPC controls: `omarchy-shell cph.presentations toggle`, `start`, `next`, `title`,
`stop`, and `status`.

The initial desktop config backups are in `.backups/`; each reinstall also writes
timestamped backups beside `bindings.lua` and `shell.json`. To remove integration,
remove the POST CODE binding block, restore clock/weather IDs to
`omarchy.clock`/`omarchy.weather` (including `centerAnchor`), remove
`cph.presentations` from the plugins list, and remove the presentation plugin and
its two cloned bar widgets. Run `hyprctl reload` and check `hyprctl configerrors`.
