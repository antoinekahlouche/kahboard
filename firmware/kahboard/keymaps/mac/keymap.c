#include QMK_KEYBOARD_H

// DEFINE COLEMAK KC IN QWERTY -------------------------------------------------

#define CO_Q KC_Q
#define CO_W KC_W
#define CO_F KC_E
#define CO_P KC_R
#define CO_G KC_T
#define CO_J KC_Y
#define CO_L KC_U
#define CO_U KC_I
#define CO_Y KC_O
#define CO_SEMICOLON KC_P
#define CO_A KC_A
#define CO_R KC_S
#define CO_S KC_D
#define CO_T KC_F
#define CO_D KC_G
#define CO_H KC_H
#define CO_N KC_J
#define CO_E KC_K
#define CO_I KC_L
#define CO_O KC_SEMICOLON
#define CO_Z KC_Z
#define CO_X KC_X
#define CO_C KC_C
#define CO_V KC_V
#define CO_B KC_B
#define CO_K KC_N
#define CO_M KC_M

// MACROS ----------------------------------------------------------------------

bool is_gui_tab_active = false;
bool is_ctl_tab_active = false;
enum custom_keycodes {
    DEGREE = SAFE_RANGE,
    GUI_TAB,
    CTL_TAB,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEGREE:
            if (record->event.pressed) {
                clear_keyboard();
                SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P7) SS_TAP(X_P6)));
            }
            break;
        case GUI_TAB:
            if (record->event.pressed) {
                if (!is_gui_tab_active) {
                    is_gui_tab_active = true;
                    register_code(KC_LGUI);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case CTL_TAB:
            if (record->event.pressed) {
                if (!is_ctl_tab_active) {
                    is_ctl_tab_active = true;
                    register_code(KC_LCTL);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
};
void matrix_scan_user(void) {
    if (is_gui_tab_active) {
        if (!layer_state_is(2)) {
            unregister_code(KC_LGUI);
            is_gui_tab_active = false;
        }
    }
    if (is_ctl_tab_active) {
        if (!layer_state_is(2)) {
            unregister_code(KC_LCTL);
            is_ctl_tab_active = false;
        }
    }
}

// LAYERS ----------------------------------------------------------------------

enum kahboard_layers {
    _BASE,
    _SYM,
    _NAV,
    _NUM
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        CO_Q, CO_W, CO_F, CO_P, CO_G,                                           CO_J, CO_L, CO_U, CO_Y, KC_QUOT, 
        CO_A, CO_R, CO_S, CO_T, CO_D,                                           CO_H, CO_N, CO_E, CO_I, CO_O,
        CO_Z, LGUI_T(CO_X), LALT_T(CO_C), LCTL_T(CO_V), CO_B,                   CO_K, RCTL_T(CO_M), RALT_T(KC_COMM), RGUI_T(KC_DOT), S(KC_SLSH),
        LT(_SYM, KC_TAB), LSFT_T(KC_BSPC),                                      LT(_NAV, KC_SPC), LT(_NUM, KC_ENT)
    ),
    [_SYM] = LAYOUT(
        S(KC_2), S(KC_3), A(S(KC_2)), S(KC_4), S(KC_5),                         KC_BSLS, KC_EQL, KC_MINS, S(KC_EQL), KC_GRV,
        S(KC_COMM), S(KC_DOT), S(KC_9), S(KC_0), S(KC_7),                       S(KC_BSLS), S(KC_LBRC), S(KC_RBRC), KC_LBRC, KC_RBRC,
        A(CO_U), A(CO_I), A(CO_C), A(CO_E), A(KC_GRV),                          S(KC_GRV), S(KC_MINS), KC_SLSH, S(KC_8), A(S(KC_8)),
        KC_NO, KC_DEL,                                                          G(C(KC_SPC)), G(KC_SPC)
    ),
    [_NAV] = LAYOUT(
        KC_NO, KC_NO, KC_NO, G(S(KC_5)), A(G(KC_EJCT)),                         KC_VOLU, C(KC_LEFT), GUI_TAB, CTL_TAB, C(KC_RIGHT),
        KC_ESC, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,                               KC_VOLD, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        KC_NO, KC_LGUI, KC_LALT, KC_RCTL, KC_NO,                                KC_MUTE, A(KC_LEFT), KC_HOME, KC_END, A(KC_RIGHT),
        KC_NO, KC_LSFT,                                                         KC_NO, KC_NO
    ),
    [_NUM] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                      KC_NO, KC_1, KC_2, KC_3, KC_NO,
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                                     KC_0, KC_4, KC_5, KC_6, KC_NO,
        KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                                 KC_NO, KC_7, KC_8, KC_9, KC_NO,
        G(KC_SPC), KC_NO,                                                       KC_NO, KC_NO
    ),
};

// OVERRIDES -------------------------------------------------------------------

const key_override_t comm = ko_make_basic(MOD_MASK_SHIFT, RALT_T(KC_COMM), CO_SEMICOLON); // Shift , is ;
const key_override_t dot = ko_make_basic(MOD_MASK_SHIFT, RGUI_T(KC_DOT), S(CO_SEMICOLON)); // Shift . is :
const key_override_t ques = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, S(KC_1)); // Shift ? is !
const key_override_t** key_overrides = (const key_override_t*[]) {
    &comm,
    &dot,
    &ques,
    NULL
};
