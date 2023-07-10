// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM combo_esc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {LSFT_T(KC_A), KC_Q, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_gui[] = {KC_W, KC_E, KC_R, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_tab,KC_TAB),
    COMBO(combo_bspc,KC_BSPC),
    COMBO(combo_ent,KC_ENT),
    COMBO(combo_gui,KC_LGUI),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(

KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y, KC_U, KC_I, KC_O, KC_P,
LSFT_T(KC_A), KC_S, KC_D, KC_F, KC_G,        KC_H, KC_J, KC_K, KC_L, RSFT_T(KC_SEMICOLON),
LCTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,        KC_N, KC_M, KC_COMMA, KC_DOT, RCTL_T(KC_SLASH),
                    MO(2), KC_LALT,          MO(1), KC_SPC
    ),

    [1] = LAYOUT(

KC_1, KC_2, KC_3, KC_4, KC_5,                   KC_6, KC_7, KC_8, KC_9, KC_0,
KC_TRNS, KC_TRNS, KC_GRV, KC_QUOT, KC_MINS,     KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC,    KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                            KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT(

KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                            KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
    )
};
