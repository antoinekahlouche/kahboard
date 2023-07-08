#include QMK_KEYBOARD_H

// MACROS ----------------------------------------------------------------------

enum custom_keycodes {
    DEGREE = SAFE_RANGE,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DEGREE:
        if (record->event.pressed) {
            clear_keyboard();
            SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P7) SS_TAP(X_P6)));
        }
        break;
    }
    return true;
};

// LAYERS ----------------------------------------------------------------------

enum kahboard_layers {
  _MAC_QWERTY,
  _MAC_SYMBOLS,
  _MAC_NAVIGATION,
  _MAC_NUMBERS,
  _WIN_QWERTY,
  _WIN_SYMBOLS,
  _WIN_NAVIGATION,
  _WIN_NUMBERS
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC_QWERTY] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                                           KC_Y, KC_U, KC_I, KC_O, KC_QUOT, 
        KC_A, KC_S, KC_D, KC_F, KC_G,                                           KC_H, KC_J, KC_K, KC_L, KC_SCLN,
        KC_Z, LGUI_T(KC_X), LALT_T(KC_C), LCTL_T(KC_V), KC_B,                   KC_N, RCTL_T(KC_M), RALT_T(KC_COMM), RGUI_T(KC_DOT), S(KC_SLSH),
        LT(1, KC_TAB), LSFT_T(KC_BSPC),                                         LT(2, KC_SPC), LT(3, KC_ENT)
    ),
    [_MAC_SYMBOLS] = LAYOUT(
        S(KC_2), S(KC_3), A(S(KC_2)), S(KC_4), S(KC_5),                         KC_NO, KC_EQL, KC_MINS, S(KC_EQL), KC_GRV,
        S(KC_COMM), S(KC_DOT), S(KC_9), S(KC_0), S(KC_7),                       S(KC_BSLS), S(KC_LBRC), S(KC_RBRC), KC_LBRC, KC_RBRC,
        A(KC_I), A(KC_L), A(KC_C), A(KC_K), A(KC_GRV),                          S(KC_GRV), S(KC_MINS), KC_SLSH, S(KC_8), A(S(KC_8)),
        KC_NO, KC_DEL,                                                          G(C(KC_SPC)), G(KC_SPC)
    ),
    [_MAC_NAVIGATION] = LAYOUT(
        G(S(KC_S)), KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,                           KC_NO, C(KC_LEFT), G(KC_TAB), C(KC_TAB), C(KC_RIGHT),
        KC_ESC, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,                               KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        A(G(KC_EJCT)), KC_LGUI, KC_LALT, KC_RCTL, DF(4),                        KC_NO, G(KC_LEFT), A(KC_LEFT), A(KC_RIGHT), G(KC_RIGHT),
        KC_NO, KC_LSFT,                                                         KC_NO, KC_NO
    ),
    [_MAC_NUMBERS] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                      KC_NO, KC_P1, KC_P2, KC_P3, KC_NO,
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                                     KC_P0, KC_P4, KC_P5, KC_P6, KC_NO,
        KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                                 KC_NO, KC_P7, KC_P8, KC_P9, KC_NO,
        G(KC_SPC), KC_NO,                                                       KC_NO, KC_NO
    ),
    [_WIN_QWERTY] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                                           KC_Y, KC_U, KC_I, KC_O, KC_QUOT, 
        KC_A, KC_S, KC_D, KC_F, KC_G,                                           KC_H, KC_J, KC_K, KC_L, KC_SCLN,
        KC_Z, LCTL_T(KC_X), LALT_T(KC_C), LGUI_T(KC_V), KC_B,                   KC_N, RGUI_T(KC_M), RALT_T(KC_COMM), RCTL_T(KC_DOT), S(KC_SLSH),
        LT(5, KC_TAB), LSFT_T(KC_BSPC),                                         LT(6, KC_SPC), LT(7, KC_ENT)
    ),
    [_WIN_SYMBOLS] = LAYOUT(
        S(KC_2), S(KC_3), ALGR(KC_5), S(KC_4), S(KC_5),                         KC_NO, KC_EQL, KC_MINS, S(KC_EQL), KC_GRV,
        S(KC_COMM), S(KC_DOT), S(KC_9), S(KC_0), S(KC_7),                       S(KC_BSLS), S(KC_LBRC), S(KC_RBRC), KC_LBRC, KC_RBRC,
        ALGR(KC_G), ALGR(KC_X), ALGR(KC_C), ALGR(KC_F), ALGR(KC_S),             S(KC_GRV), S(KC_MINS), KC_SLSH, S(KC_8), DEGREE,
        KC_NO, KC_DEL,                                                          G(KC_DOT), A(KC_SPC)
    ),
    [_WIN_NAVIGATION] = LAYOUT(
        KC_PSCR, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,                              KC_NO, C(G(KC_LEFT)), A(KC_TAB), C(KC_TAB), C(G(KC_RIGHT)),
        KC_ESC, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,                               KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        KC_PWR, KC_RCTL, KC_LALT, KC_LGUI, DF(0),                               KC_NO, KC_HOME, C(KC_LEFT), C(KC_RIGHT), KC_END,
        KC_NO, KC_LSFT,                                                         KC_NO, KC_NO
    ),
    [_WIN_NUMBERS] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                      KC_NO, KC_P1, KC_P2, KC_P3, KC_NO,
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                                     KC_P0, KC_P4, KC_P5, KC_P6, KC_NO,
        KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                                 KC_NO, KC_P7, KC_P8, KC_P9, KC_NO,
        A(KC_SPC), KC_NO,                                                       KC_NO, KC_NO
    )
};

// OVERRIDES -------------------------------------------------------------------

const key_override_t comm = ko_make_basic(MOD_MASK_SHIFT, RALT_T(KC_COMM), KC_P); // Shift , is ;
const key_override_t macDot = ko_make_basic(MOD_MASK_SHIFT, RGUI_T(KC_DOT), S(KC_P)); // Shift . is :
const key_override_t winDot = ko_make_basic(MOD_MASK_SHIFT, RCTL_T(KC_DOT), S(KC_P)); // Shift . is :
const key_override_t ques = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, S(KC_1)); // Shift ? is !
const key_override_t** key_overrides = (const key_override_t*[]) {
    &comm,
    &macDot,
    &winDot,
    &ques,
    NULL
};
