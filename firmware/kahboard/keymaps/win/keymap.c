#include QMK_KEYBOARD_H

// DEFINE COLEMAK KC IN AZERTY -------------------------------------------------

#define CO_Q KC_A
#define CO_W KC_Z
#define CO_F KC_F
#define CO_P KC_P
#define CO_G KC_G
#define CO_J KC_J
#define CO_L KC_L
#define CO_U KC_U
#define CO_Y KC_Y
#define CO_SEMICOLON KC_M
#define CO_A KC_Q
#define CO_R KC_R
#define CO_S KC_S
#define CO_T KC_T
#define CO_D KC_D
#define CO_H KC_H
#define CO_N KC_N
#define CO_E KC_E
#define CO_I KC_I
#define CO_O KC_O
#define CO_Z KC_W
#define CO_X KC_X
#define CO_C KC_C
#define CO_V KC_V
#define CO_B KC_B
#define CO_K KC_K
#define CO_M KC_SEMICOLON

// MACROS ----------------------------------------------------------------------

bool is_alt_tab_active = false;
bool is_ctl_tab_active = false;
enum custom_keycodes {
    BACKTICK = SAFE_RANGE,
    TILDE,
    ALT_TAB,
    CTL_TAB,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BACKTICK:
            if (record->event.pressed) {
                clear_keyboard();
                SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P9) SS_TAP(X_P6)));
            }
            break;
        case TILDE:
            if (record->event.pressed) {
                clear_keyboard();
                SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P2) SS_TAP(X_P6)));
            }
            break;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
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
    if (is_alt_tab_active) {
        if (!layer_state_is(2)) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
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
        CO_Q, CO_W, CO_F, CO_P, CO_G,                                           CO_J, CO_L, CO_U, CO_Y, KC_4, 
        CO_A, CO_R, CO_S, CO_T, CO_D,                                           CO_H, CO_N, CO_E, CO_I, CO_O,
        CO_Z, LCTL_T(CO_X), LALT_T(CO_C), LGUI_T(CO_V), CO_B,                   CO_K, CO_M, CO_SEMICOLON, S(KC_COMMA), S(CO_SEMICOLON),
        LT(_SYM, KC_TAB), LSFT_T(KC_BSPC),                                      LT(_NAV, KC_SPC), LT(_NUM, KC_ENT)
    ),
    [_SYM] = LAYOUT(
        ALGR(KC_0), ALGR(KC_3), KC_LBRC, S(KC_LBRC), S(KC_QUOT),                ALGR(KC_8), KC_EQL, KC_6, S(KC_EQL), BACKTICK,
        KC_NUBS, S(KC_NUBS), KC_5, KC_MINUS, KC_1,                              ALGR(KC_6), ALGR(KC_4), ALGR(KC_EQL), ALGR(KC_5), ALGR(KC_MINUS),
        KC_0, KC_QUOTE, KC_9, KC_2, KC_7,                                       TILDE, KC_8, S(KC_DOT), KC_BSLS, G(KC_COMMA),
        KC_NO, KC_DEL,                                                          KC_NO, A(KC_SPC)
    ),
    [_NAV] = LAYOUT(
        DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, DM_RSTP,                                      KC_VOLU, C(G(KC_LEFT)), ALT_TAB, CTL_TAB, C(G(KC_RIGHT)),
        KC_ESC, KC_MPRV, KC_MPLY, KC_MNXT, KC_PSCR,                             KC_VOLD, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        KC_PWR, KC_RCTL, KC_LALT, KC_LGUI, KC_NO,                               KC_MUTE, C(KC_LEFT), KC_HOME, KC_END, C(KC_RIGHT),
        KC_NO, KC_LSFT,                                                         KC_NO, KC_NO
    ),
    [_NUM] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                      KC_NO, S(KC_1), S(KC_2), S(KC_3), KC_RBRC,
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                                     S(KC_0), S(KC_4), S(KC_5), S(KC_6), ALGR(CO_E),
        KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                                 S(KC_MINUS), S(KC_7), S(KC_8), S(KC_9), KC_NO,
        A(KC_SPC), KC_NO,                                                       KC_NO, KC_NO
    )
};

// OVERRIDES -------------------------------------------------------------------

const key_override_t four = ko_make_basic(MOD_MASK_SHIFT, KC_4, KC_3); // Shift ' is "
const key_override_t comm = ko_make_basic(MOD_MASK_SHIFT, CO_SEMICOLON, KC_COMMA); // Shift , is ;
const key_override_t dot = ko_make_basic(MOD_MASK_SHIFT, S(KC_COMMA), KC_DOT); // Shift . is :
const key_override_t ques = ko_make_basic(MOD_MASK_SHIFT, S(CO_SEMICOLON), KC_SLASH); // Shift ? is !
const key_override_t** key_overrides = (const key_override_t*[]) {
    &four,
    &comm,
    &dot,
    &ques,
    NULL
};
