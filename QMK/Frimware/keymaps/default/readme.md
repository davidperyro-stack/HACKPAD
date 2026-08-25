# default keymap for hackpad

Fixed 9-function layout, no layers:

```
+---------+---------+---------+
| Spotify |  Steam  |  Power  |
+---------+---------+---------+
| Vol Up  |  Mute   | Vol Dwn |
+---------+---------+---------+
|  Paste  |  Copy   | Opera GX|
+---------+---------+---------+
```

- **Spotify / Steam / Opera GX**: taps Windows key, types the app name,
  hits Enter (i.e. drives Start Menu search). Edit the strings passed
  to `launch_via_start_menu()` in `keymap.c` if an app doesn't show up
  under that name on your machine.
- **Copy / Paste**: sends Ctrl+C / Ctrl+V.
- **Power**: sends the HID "System Power Down" signal (`KC_PWR`).
- **Volume Up/Down/Mute**: standard consumer control keys.
