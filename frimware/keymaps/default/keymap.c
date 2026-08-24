#include QMK_KEYBOARD_H

enum custom_keycodes {
    OPEN_SPOTIFY = SAFE_RANGE,
    OPEN_STEAM,
    OPEN_OPERAGX,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        OPEN_SPOTIFY, LCTL(LSFT(KC_ESC)), KC_VOLU,
        OPEN_STEAM,   OPEN_OPERAGX,       KC_MUTE,
        LCTL(KC_C),   LCTL(KC_V),         KC_VOLD
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OPEN_SPOTIFY:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_DELAY(200)) "spotify" SS_DELAY(300) SS_TAP(X_ENTER));
            }
            return false;
        case OPEN_STEAM:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_DELAY(200)) "steam" SS_DELAY(300) SS_TAP(X_ENTER));
            }
            return false;
        case OPEN_OPERAGX:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_DELAY(200)) "opera gx" SS_DELAY(400) SS_TAP(X_ENTER));
            }
            return false;
    }
    return true;
}