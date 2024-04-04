#include QMK_KEYBOARD_H

// MACROS ----------------------------------------------------------------------

bool is_gui_tab_active = false;
bool is_ctl_tab_active = false;
enum custom_keycodes {
    DEGREE = SAFE_RANGE,
    A_GRAVE,
    U_GRAVE,
    E_AIGUE,
    E_GRAVE,
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
        case A_GRAVE:
            if (record->event.pressed) {
                clear_keyboard();
                SEND_STRING(SS_LALT(SS_TAP(X_GRV)) SS_TAP(X_A));
            }
            break;
        case U_GRAVE:
            if (record->event.pressed) {
                clear_keyboard();
                SEND_STRING(SS_LALT(SS_TAP(X_GRV)) SS_TAP(X_I));
            }
            break;
        case E_AIGUE:
            if (record->event.pressed) {
                clear_keyboard();
                SEND_STRING(SS_LALT(SS_TAP(X_K)) SS_TAP(X_K));
            }
            break;
        case E_GRAVE:
            if (record->event.pressed) {
                clear_keyboard();
                SEND_STRING(SS_LALT(SS_TAP(X_GRV)) SS_TAP(X_K));
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
        KC_Q, KC_W, KC_E, KC_R, KC_T,                                           KC_Y, KC_U, KC_I, KC_O, KC_QUOT, 
        KC_A, KC_S, KC_D, KC_F, KC_G,                                           KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON,
        KC_Z, LGUI_T(KC_X), LALT_T(KC_C), LCTL_T(KC_V), KC_B,                   KC_N, KC_M, KC_COMM, KC_DOT, S(KC_SLSH),
        LT(_SYM, KC_TAB), LSFT_T(KC_BSPC),                                      LT(_NAV, KC_SPC), LT(_NUM, KC_ENT)
    ),
    [_SYM] = LAYOUT(
        S(KC_2), S(KC_3), A(KC_L), A(KC_I), S(KC_5),                            KC_BSLS, KC_EQL, KC_MINS, S(KC_EQL), KC_GRV,
        S(KC_COMM), S(KC_DOT), S(KC_9), S(KC_0), S(KC_7),                       S(KC_BSLS), S(KC_LBRC), S(KC_RBRC), KC_LBRC, KC_RBRC,
        A_GRAVE, U_GRAVE, A(KC_C), E_AIGUE, E_GRAVE,                            S(KC_GRV), S(KC_MINS), KC_SLSH, S(KC_8), G(C(KC_SPC)),
        KC_NO, KC_DEL,                                                          KC_NO, G(KC_SPC)
    ),
    [_NAV] = LAYOUT(
        DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, DM_RSTP,                            KC_VOLU, C(KC_LEFT), GUI_TAB, CTL_TAB, C(KC_RIGHT),
        KC_ESC, KC_MPRV, KC_MPLY, KC_MNXT, G(S(KC_5)),                          KC_VOLD, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        A(G(KC_EJCT)), KC_LGUI, KC_LALT, KC_RCTL, KC_NO,                        KC_MUTE, A(KC_LEFT), KC_HOME, KC_END, A(KC_RIGHT),
        KC_NO, KC_LSFT,                                                         KC_NO, KC_NO
    ),
    [_NUM] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                      KC_NO, KC_1, KC_2, KC_3, S(KC_4),
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                                     KC_0, KC_4, KC_5, KC_6, A(S(KC_2)),
        KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                                 A(S(KC_8)), KC_7, KC_8, KC_9, KC_NO,
        G(KC_SPC), KC_NO,                                                       KC_NO, KC_NO
    ),
};

// OVERRIDES -------------------------------------------------------------------

const key_override_t comm = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_P); // Shift , is ;
const key_override_t dot = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_P)); // Shift . is :
const key_override_t ques = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, S(KC_1)); // Shift ? is !
const key_override_t** key_overrides = (const key_override_t*[]) {
    &comm,
    &dot,
    &ques,
    NULL
};
