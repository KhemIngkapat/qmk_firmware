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
    // Set cursor position
    oled_set_cursor(0, 1);

    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("Caps") : PSTR("    "),false);


    return false;
}

#endif


const uint16_t PROGMEM combo_tab[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_gui[] = {KC_W, KC_E, KC_R, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_tab,KC_TAB),
    COMBO(combo_esc,KC_ESC),
    COMBO(combo_bspc,KC_BSPC),
    COMBO(combo_ent,KC_ENT),
    COMBO(combo_gui,KC_LGUI),
};

enum {
    TD_SFT_CAPS
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
KC_Q,         KC_W, KC_E, KC_R, KC_T,        KC_Y, KC_U, KC_I, KC_O, KC_P,
LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G,        KC_H, KC_J, KC_K, KC_L, RSFT_T(KC_SEMICOLON),
LCTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,        KC_N, KC_M, KC_COMMA, KC_DOT, RCTL_T(KC_SLASH),
                          MO(2), KC_LALT,    TD(TD_SFT_CAPS), LT(1,KC_SPC)
    ),

    [1] = LAYOUT(

KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                           KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT(

KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_MINS, KC_EQL, KC_LPRN, KC_LBRC,  KC_LCBR,
KC_TRNS, KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_QUOT,
KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_UNDS, KC_PLUS, KC_RPRN, KC_RBRC,  KC_RCBR,
                           KC_TRNS, KC_TRNS,    KC_TRNS, QK_REP
    )
};
