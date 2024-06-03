/* Copyright 2023 @ Keychron (https://www.keychron.com) *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    DEFAULT,
    NAV,
    MEDIA,
    F_KEYS,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_61_ansi(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,  KC_BSPC,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC, KC_BSLS,
        KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,
        KC_LCTL,  KC_LALT, KC_LGUI,                               KC_SPC,                                 MT(MOD_RALT,KC_APP),KC_RCTL,TT(MEDIA),TT(F_KEYS)),

    [NAV] = LAYOUT_61_ansi(
        _______,  _______,  _______, _______ ,_______,_______,_______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______,  _______,  _______, _______,  KC_HOME,  KC_PGDN, KC_PGUP, KC_END, _______, _______, _______,  _______,
        _______,  _______, _______,  _______,  _______, _______,  KC_LEFT,  KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,
        _______,  _______,  _______,                                _______,                               _______,_______,_______,_______),


    [MEDIA] = LAYOUT_61_ansi(
        KC_CAPS,   KC_BRID,  KC_BRIU,  RGB_VAD,  RGB_VAI,  _______,  KC_MPRV,  KC_MRWD,  KC_MFFD,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,
        _______,  _______,  KC_UP,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  _______,  _______,  _______,
        _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,  _______,  _______,  _______,  _______,  _______,  KC_UP,  _______,            _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  KC_LEFT, KC_DOWN,  KC_RIGHT,            _______,
        _______,  _______,  _______,                                KC_MPLY,                                _______,  _______,  _______,  _______),

    [F_KEYS] = LAYOUT_61_ansi(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
        _______, RGB_RMOD,  RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______),



};

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
//const key_override_t caps_shift = ko_make_basic(MOD_MASK_SHIFT, KC_GRV, KC_CAPS);
//const key_override_t arrow_l = ko_make_basic(MOD_BIT(KC_LCTL), KC_H, KC_LEFT);
//const key_override_t arrow_d = ko_make_basic(MOD_BIT(KC_LCTL), KC_J, KC_DOWN);
//const key_override_t arrow_u = ko_make_basic(MOD_BIT(KC_LCTL), KC_K, KC_UP);
//const key_override_t arrow_r = ko_make_basic(MOD_BIT(KC_LCTL), KC_L, KC_RIGHT);
//const key_override_t playpause = ko_make_basic(MOD_BIT(KC_LCTL), KC_SPC, KC_MPLY);

//const key_override_t layer_lock = ko_make_basic(MOD_BIT(KC_LCTL), KC_RSFT, TG(NAV));
//const key_override_t layer_lock2 = ko_make_basic(MOD_BIT(KC_RSFT), KC_SPC, TG(NAV));


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_ESC:
        if (record->event.pressed) {
            layer_on(NAV);
            return false;
        } else {
            layer_of(NAV);
        }
    }
    return true;
}



// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    //&caps_shift, 
    //&arrow_l,
    //&arrow_d,
    //&arrow_u,
    //&arrow_r,
    //&playpause,
    //&layer_lock,
    //&layer_lock2,
    NULL // Null terminate the array of overrides!
};

