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
    CTRL_NAV,
    FUN,
    F_KEYS,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_61_ansi(
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,  KC_BSPC,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC, KC_BSLS,
        LT(CTRL_NAV,KC_ESC),   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,
        KC_LCTL,  KC_LALT, KC_LGUI,                               KC_SPC,                                 MT(MOD_RALT,KC_APP),KC_RCTL,TT(FUN),TT(F_KEYS)),

    [CTRL_NAV] = LAYOUT_61_ansi(
        C(KC_GRV),  C(KC_1),  C(KC_2),  C(KC_3),  C(KC_4),  C(KC_5),  C(S(KC_6)),  C(S(KC_7)),  KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   C(KC_BSPC),
        C(KC_TAB),  C(KC_Q),  C(KC_W),  C(KC_E),  C(KC_R),  C(KC_T),  KC_HOME,  KC_PGDN,  KC_PGUP,   KC_END,  C(KC_P),    C(KC_LBRC),  C(KC_RBRC),  C(KC_BSLS),
        _______,    C(KC_A),  C(KC_S),  C(KC_D),  C(KC_F),  C(KC_G),  KC_LEFT,  KC_DOWN,  KC_UP,   KC_RIGHT,  C(KC_SCLN),   C(KC_QUOT),      C(KC_ENT)        ,
        C(KC_LSFT), C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  C(KC_B),  C(KC_N),  C(KC_M),  C(KC_COMM),  C(KC_DOT),      C(KC_SLSH)     ,      C(KC_RSFT)       ,
        KC_LCTL,  C(KC_LALT), C(KC_LGUI),                               C(KC_SPC),                            _______,_______,_______,_______),


    [FUN] = LAYOUT_61_ansi(
        CW_TOGG,   KC_BRID,  KC_BRIU,  RGB_VAD,  RGB_VAI,  _______,  C(S(KC_6)),  C(S(KC_7)),  KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,
        _______,  _______,  KC_UP,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  _______,  _______,  _______,
        _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,  _______,  _______,  _______,  _______,  KC_UP,   _______,   _______,            _______,
        _______,  _______,  _______,  _______,   _______,  BAT_LVL,  _______,  _______,  KC_LEFT, KC_DOWN,  KC_RIGHT,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______),

    [F_KEYS] = LAYOUT_61_ansi(
        KC_CAPS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
        _______, RGB_RMOD,  RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,            QK_AUTO_SHIFT_TOGGLE,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______),


};

uint8_t mod_state;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        static bool delkey_registered;
        static bool mediapp_registered;
        if (record->event.pressed) {
			// Del
            if (mod_state & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                delkey_registered = true;
                set_mods(mod_state);
                return false;
            }
			// Play-Pause
			if (mod_state & MOD_MASK_ALT) {
				del_mods(MOD_MASK_ALT)
                register_code(KC_MPLY);
                mediapp_registered = true;
                set_mods(mod_state);
			}
        } else {
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                mediapp_registered = false;
                return false;
            }
        } 
    }
    return true;
}


