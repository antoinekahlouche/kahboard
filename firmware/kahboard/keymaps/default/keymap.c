#include QMK_KEYBOARD_H
#include "os_detection.h"

enum kahboard_layers {
    MAC_BASE,
    MAC_SYM,
    MAC_NAV,
    MAC_NUM,
    WIN_BASE,
    WIN_SYM,
    WIN_NAV,
    WIN_NUM
};

// MACROS ----------------------------------------------------------------------

bool is_gui_tab_active = false;
bool is_alt_tab_active = false;
bool is_ctl_tab_active = false;

enum custom_keycodes {
    BACKTICK = SAFE_RANGE,
    TILDE,
    A_GRAVE,
    U_GRAVE,
    E_AIGUE,
    E_GRAVE,
    GUI_TAB,
    ALT_TAB,
    CTL_TAB,
    TOGGLE_OS,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
        case TOGGLE_OS:
            if (record->event.pressed) {
            } else {
                if (layer_state_is(MAC_NAV)) {
                    layer_move(WIN_BASE);
                }
                if (layer_state_is(WIN_NAV)) {
                    layer_move(MAC_BASE);
                }
            }
            break;
    }
    return true;
};

void matrix_scan_user(void) {
    if (is_gui_tab_active) {
        if (!layer_state_is(MAC_NAV)) {
            unregister_code(KC_LGUI);
            is_gui_tab_active = false;
        }
    }
    if (is_alt_tab_active) {
        if (!layer_state_is(WIN_NAV)) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    if (is_ctl_tab_active) {
        if (!layer_state_is(MAC_NAV) && !layer_state_is(WIN_NAV)) {
            unregister_code(KC_LCTL);
            is_ctl_tab_active = false;
        }
    }
}

// LAYERS ----------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // MAC OS ------------------------------------------------------------------
    [MAC_BASE] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                                           KC_Y, KC_U, KC_I, KC_O, KC_QUOT, 
        KC_A, KC_S, KC_D, KC_F, KC_G,                                           KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON,
        KC_Z, LGUI_T(KC_X), LALT_T(KC_C), LCTL_T(KC_V), KC_B,                   KC_N, KC_M, KC_COMM, KC_DOT, S(KC_SLSH),
        LT(MAC_SYM, KC_TAB), LSFT_T(KC_BSPC),                                   LT(MAC_NAV, KC_SPC), LT(MAC_NUM, KC_ENT)
    ),
    [MAC_SYM] = LAYOUT(
        S(KC_2), S(KC_3), A(KC_L), A(KC_I), S(KC_5),                            KC_BSLS, KC_EQL, KC_MINS, S(KC_EQL), KC_GRV,
        S(KC_COMM), S(KC_DOT), S(KC_9), S(KC_0), S(KC_7),                       S(KC_BSLS), S(KC_LBRC), S(KC_RBRC), KC_LBRC, KC_RBRC,
        A_GRAVE, U_GRAVE, A(KC_C), E_AIGUE, E_GRAVE,                            S(KC_GRV), S(KC_MINS), KC_SLSH, S(KC_8), G(C(KC_SPC)),
        KC_NO, KC_DEL,                                                          KC_NO, G(KC_SPC)
    ),
    [MAC_NAV] = LAYOUT(
        DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, DM_RSTP,                            KC_VOLU, C(KC_LEFT), GUI_TAB, CTL_TAB, C(KC_RIGHT),
        KC_ESC, KC_MPRV, KC_MPLY, KC_MNXT, G(S(KC_5)),                          KC_VOLD, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        A(G(KC_EJCT)), KC_LGUI, KC_LALT, KC_RCTL, TOGGLE_OS,                    KC_MUTE, A(KC_LEFT), KC_HOME, KC_END, A(KC_RIGHT),
        KC_NO, KC_LSFT,                                                         KC_NO, KC_NO
    ),
    [MAC_NUM] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                      KC_NO, KC_7, KC_8, KC_9, S(KC_4),
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                                     KC_0, KC_4, KC_5, KC_6, A(S(KC_2)),
        KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                                 A(S(KC_8)), KC_1, KC_2, KC_3, KC_NO,
        G(KC_SPC), KC_NO,                                                       KC_NO, KC_NO
    ),
    // WINDOWS -----------------------------------------------------------------
    [WIN_BASE] = LAYOUT(
        KC_A, KC_Z, KC_F, KC_P, KC_G,                                           KC_J, KC_L, KC_U, KC_Y, KC_4, 
        KC_Q, KC_R, KC_S, KC_T, KC_D,                                           KC_H, KC_N, KC_E, KC_I, KC_O,
        KC_W, LCTL_T(KC_X), LALT_T(KC_C), LGUI_T(KC_V), KC_B,                   KC_K, KC_SEMICOLON, KC_M, S(KC_COMMA), S(KC_M),
        LT(WIN_SYM, KC_TAB), LSFT_T(KC_BSPC),                                   LT(WIN_NAV, KC_SPC), LT(WIN_NUM, KC_ENT)
    ),
    [WIN_SYM] = LAYOUT(
        ALGR(KC_0), ALGR(KC_3), KC_LBRC, S(KC_LBRC), S(KC_QUOT),                ALGR(KC_8), KC_EQL, KC_6, S(KC_EQL), BACKTICK,
        KC_NUBS, S(KC_NUBS), KC_5, KC_MINUS, KC_1,                              ALGR(KC_6), ALGR(KC_4), ALGR(KC_EQL), ALGR(KC_5), ALGR(KC_MINUS),
        KC_0, KC_QUOTE, KC_9, KC_2, KC_7,                                       TILDE, KC_8, S(KC_DOT), KC_BSLS, G(KC_COMMA),
        KC_NO, KC_DEL,                                                          KC_NO, KC_LWIN
    ),
    [WIN_NAV] = LAYOUT(
        DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, DM_RSTP,                            KC_VOLU, C(G(KC_LEFT)), ALT_TAB, CTL_TAB, C(G(KC_RIGHT)),
        KC_ESC, KC_MPRV, KC_MPLY, KC_MNXT, KC_PSCR,                             KC_VOLD, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        KC_PWR, KC_RCTL, KC_LALT, KC_LGUI, TOGGLE_OS,                           KC_MUTE, C(KC_LEFT), KC_HOME, KC_END, C(KC_RIGHT),
        KC_NO, KC_LSFT,                                                         KC_NO, KC_NO
    ),
    [WIN_NUM] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                      KC_NO, S(KC_7), S(KC_8), S(KC_9), KC_RBRC,
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                                     S(KC_0), S(KC_4), S(KC_5), S(KC_6), ALGR(KC_E),
        KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                                 S(KC_MINUS), S(KC_1), S(KC_2), S(KC_3), KC_NO,
        KC_LWIN, KC_NO,                                                         KC_NO, KC_NO
    ),
};

// OVERRIDES -------------------------------------------------------------------

// Shift , is ;
const key_override_t comm_mac = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_P, 1 << 0);
const key_override_t comm_win = ko_make_with_layers(MOD_MASK_SHIFT, KC_M, KC_COMMA, 1 << 4);
// Shift . is :
const key_override_t dot_mac = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT, S(KC_P), 1 << 0);
const key_override_t dot_win = ko_make_with_layers(MOD_MASK_SHIFT, S(KC_COMMA), KC_DOT, 1 << 4);
// Shift ? is !
const key_override_t ques_mac = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUES, S(KC_1), 1 << 0);
const key_override_t ques_win = ko_make_with_layers(MOD_MASK_SHIFT, S(KC_M), KC_SLASH, 1 << 4);
// Shift ' is "
const key_override_t four_win = ko_make_with_layers(MOD_MASK_SHIFT, KC_4, KC_3, 1 << 4);

const key_override_t** key_overrides = (const key_override_t*[]) {
    &comm_mac,
    &comm_win,
    &dot_mac,
    &dot_win,
    &ques_mac,
    &ques_win,
    &four_win,
    NULL
};

// OS DETECTION ----------------------------------------------------------------

void keyboard_post_init_user(void) {
    wait_ms(400);
    os_variant_t detected_os = detected_host_os();
    switch (detected_os) {
        case OS_MACOS:
            layer_move(MAC_BASE);
            break;
        case OS_IOS:
        case OS_WINDOWS:
        case OS_LINUX:
        case OS_UNSURE:
        default:
            layer_move(WIN_BASE);
            break;
    }
}