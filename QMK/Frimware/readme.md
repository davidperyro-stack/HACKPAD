# HACKPAD — 3x3 macropad (Seeed XIAO RP2040)

A minimal 3x3 ortholinear macropad, row/column matrix with diodes,
built on the Seeed XIAO RP2040.

* Hardware Supported: Seeed XIAO RP2040
* Hardware Availability: custom PCB / handwired

## Pinout used in this firmware

| XIAO pin (silkscreen) | GPIO   | Matrix role |
|------------------------|--------|-------------|
| D0                      | GP26   | Row 0       |
| D1                      | GP27   | Row 1       |
| D2                      | GP28   | Row 2       |
| D3                      | GP29   | Col 0       |
| D4                      | GP6    | Col 1       |
| D5                      | GP7    | Col 2       |

Change these in `info.json` under `matrix_pins` if you wired it
differently — the GPxx numbers are what QMK actually reads; the D0-D10
labels are just what's silkscreened on the XIAO board.

## Wiring

`diode_direction` is set to `COL2ROW`, meaning current flows from the
column pin, through the diode, into the row pin. Orient every diode
the same way (cathode/stripe toward the row wire):

```
        COL0 (D3)   COL1 (D4)   COL2 (D5)
          │           │           │
ROW0 ─────┼──|>|──────┼──|>|──────┼──|>|─────  (D0)
          │  SW        │  SW        │  SW
ROW1 ─────┼──|>|──────┼──|>|──────┼──|>|─────  (D1)
          │  SW        │  SW        │  SW
ROW2 ─────┼──|>|──────┼──|>|──────┼──|>|─────  (D2)
             SW           SW           SW
```

Each switch sits between a row/column intersection, in series with a
1N4148 diode. The diode's stripe (cathode) points toward the row pin.

## Build

```sh
qmk compile -kb hackpad -km default
```

or, if you're inside a full `qmk_firmware` checkout without the `qmk`
CLI configured:

```sh
make hackpad:default
```

This produces `hackpad_default.uf2`.

## Flash

The XIAO RP2040 boots into its UF2 bootloader when you double-tap the
reset button (or short/bridge the `B` pads on the back per Seeed's
docs while plugging in).

1. Double-tap reset — a drive named `RPI-RP2` shows up.
2. Copy `hackpad_default.uf2` onto that drive.
3. The board reboots automatically running the new firmware.

`bootmagic` is also enabled, so once firmware is flashed you can
usually re-enter the bootloader by holding the top-left key (K00)
while plugging in — matches QMK's default bootmagic behavior of
holding the top-left switch.

## Installing this into a qmk_firmware checkout

Drop this whole `hackpad` folder into `qmk_firmware/keyboards/`, so
you end up with:

```
qmk_firmware/
  keyboards/
    hackpad/
      info.json
      rules.mk
      readme.md
      keymaps/
        default/
          keymap.c
          readme.md
```

Then run the build command above from the root of `qmk_firmware`.

## Keymap: what each key does

```
┌─────────┬─────────┬─────────┐
│ Spotify │  Steam  │  Power  │
├─────────┼─────────┼─────────┤
│ Vol Up  │  Mute   │ Vol Dwn │
├─────────┼─────────┼─────────┤
│  Paste  │  Copy   │ Opera GX│
└─────────┴─────────┴─────────┘
```

**Volume Up/Down, Mute** — plain QMK consumer keycodes (`KC_VOLU`,
`KC_VOLD`, `KC_MUTE`). Nothing to configure.

**Copy / Paste** — there's no dedicated "copy"/"paste" HID key, so
these just send `Ctrl+C` / `Ctrl+V` (`LCTL(KC_C)` / `LCTL(KC_V)`).
Works anywhere those shortcuts normally work.

**Power** — sends the HID "System Power Down" control (`KC_PWR`).
What actually happens depends on your OS's power-button behavior
(instant shutdown, sleep, or a prompt) — check your power settings if
it doesn't do what you expect.

**Spotify / Steam / Opera GX** — there's no universal HID key for
"launch this specific app," so these are macros: tap the Windows key
(opens Start Menu search), type the app name, press Enter. Defined in
`keymap.c`:

```c
static void launch_via_start_menu(const char *name) {
    tap_code(KC_LGUI);
    wait_ms(APP_LAUNCH_DELAY_MS);
    send_string(name);
    wait_ms(150);
    tap_code(KC_ENT);
}
```

Notes/caveats:
- **Assumes Windows.** On macOS, swap `tap_code(KC_LGUI)` for
  `tap_code16(LGUI(KC_SPC))` to open Spotlight instead. On Linux it
  depends on your DE — many use `KC_LGUI` for an app launcher too,
  but not all.
- **The typed string has to match what shows up in search** — if
  Steam shows up as "Steam" and Spotify as "Spotify Music" on your
  system, adjust the strings passed into `launch_via_start_menu()`.
- **Timing**: `APP_LAUNCH_DELAY_MS` (default 300ms) is how long it
  waits for the search box to appear before typing. If the app
  doesn't launch reliably, increase it.
- **More reliable alternative**: if you'd rather not depend on Start
  Menu search matching, you can send a direct URI/Run command instead
  — e.g. `tap_code16(LGUI(KC_R))` to open Run, then
  `send_string("spotify:")` (Spotify's URI handler) or
  `send_string("steam://open/main")` (Steam's), then Enter. Opera GX
  doesn't have a URI scheme, so for that one you'd point to its full
  `.exe` path instead.

If you want a hardware encoder later, add `"encoder": {...}` to
`info.json` and `ENCODER_MAP_ENABLE = yes` to `rules.mk`.
