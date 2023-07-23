// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE

// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// Draw to OLED
bool oled_task_user() {

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("DEF\n"),false);
            break;
        case 1:
            oled_write_P(PSTR("ACC\n"),false);
            break;
        case 2:
            oled_write_P(PSTR("FNC\n"),false);
            break;
        case 3:
            oled_write_P(PSTR("NUM\n"),false);
            break;
        case 4:
            oled_write_P(PSTR("SYM\n"),false);
            break;
        default:
            oled_write_ln_P(PSTR("UND"),false);
    }

    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "),false);



    return false;
}

#endif

const uint16_t PROGMEM combo_tab[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_gui[] = {KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_caps[] = {KC_AT, KC_HASH, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_tab,KC_TAB),
    COMBO(combo_esc,KC_ESC),
    COMBO(combo_bspc,KC_BSPC),
    COMBO(combo_ent,KC_ENT),
    COMBO(combo_gui,KC_LGUI),
    COMBO(combo_caps,KC_CAPS),
};

typedef enum {
    TD_NONE,
    TD_UNKNOW,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_LY4
};

td_state_t cur_dance(tap_dance_state_t *state);

void ly4_finished(tap_dance_state_t *state, void *user_data);
void ly4_reset(tap_dance_state_t *state, void *user_data);



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
KC_Q,         KC_W, KC_E, KC_R, KC_T,               KC_Y, KC_U, KC_I, KC_O, KC_P,
LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G,               KC_H, KC_J, KC_K, KC_L, RSFT_T(KC_SEMICOLON),
LCTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,               KC_N, KC_M, KC_COMMA, KC_DOT, RCTL_T(KC_SLASH),
                          TD(TD_LY4), KC_LALT,      TG(3), LT(1,KC_SPC)
    ),

    [1] = LAYOUT(

KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                           KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT(

KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_QUOT,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
                           KC_TRNS, OSL(4),    KC_BSLS, QK_REP
    ),

    [3] = LAYOUT(

KC_NO, KC_1, KC_2, KC_3, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO, KC_4, KC_5, KC_6, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO, KC_7, KC_8, KC_9, KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                   KC_TRNS, KC_0,     KC_TRNS, KC_NO
    ),

    [4] = LAYOUT(
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_MINS, KC_EQL,  KC_LPRN, KC_LBRC,  KC_LCBR,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_QUOT,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_UNDS, KC_PLUS, KC_RPRN, KC_RBRC,  KC_RCBR,
                           KC_TRNS, KC_TRNS,    KC_BSLS, QK_REP



    ),
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    /* } else if (state->count == 2) { */
    /*     return TD_DOUBLE_TAP; */
    } else return TD_UNKNOW;
}

static td_tap_t ly4tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void ly4_finished(tap_dance_state_t *state, void *user_data) {
    ly4tap_state.state = cur_dance(state);
    switch (ly4tap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(4,ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case TD_SINGLE_HOLD: layer_on(2); break;
        default: break;
        }
}

void ly4_reset(tap_dance_state_t *state, void *user_data) {
    if(ly4tap_state.state == TD_SINGLE_HOLD) {
        layer_off(2);
    }
    ly4tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LY4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ly4_finished, ly4_reset)
};
