#include QMK_KEYBOARD_H

// Custom keycodes for "open an app" macros.
// These work by tapping the Windows key (opens Start Menu search),
// typing the app name, then pressing Enter -- same as doing it by hand.
// Requires Windows + the app actually showing up in Start Menu search
// under that name. See readme.md for Mac/Linux notes and alternatives.
enum custom_keycodes {
    SPOTIFY = SAFE_RANGE,
    STEAM,
    OPERAGX,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * +---------+---------+---------+
     * | Spotify |  Steam  |  Power  |
     * +---------+---------+---------+
     * | Vol Up  |  Mute   | Vol Dwn |
     * +---------+---------+---------+
     * |  Paste  |  Copy   | Opera GX|
     * +---------+---------+---------+
     */
    [0] = LAYOUT(
        SPOTIFY,     STEAM,       KC_PWR,
        KC_VOLU,     KC_MUTE,     KC_VOLD,
        LCTL(KC_V),  LCTL(KC_C),  OPERAGX
    ),
};

// How long to let the Start Menu search box pop up before we start typing.
// Bump this up if the app search fails to trigger (slower PCs may need more).
#define APP_LAUNCH_DELAY_MS 300

static void launch_via_start_menu(const char *name) {
    tap_code(KC_LGUI);          // open Start Menu / search
    wait_ms(APP_LAUNCH_DELAY_MS);
    send_string(name);
    wait_ms(150);
    tap_code(KC_ENT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        // only fire on key-down, ignore key-up
        switch (keycode) {
            case SPOTIFY:
            case STEAM:
            case OPERAGX:
                return false;
            default:
                return true;
        }
    }

    switch (keycode) {
        case SPOTIFY:
            launch_via_start_menu("spotify");
            return false;
        case STEAM:
            launch_via_start_menu("steam");
            return false;
        case OPERAGX:
            launch_via_start_menu("opera gx");
            return false;
    }
    return true;
}
