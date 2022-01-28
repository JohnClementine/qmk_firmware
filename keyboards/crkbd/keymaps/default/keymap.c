/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "secrets.h"
#include <stdio.h>
//extern rgblight_config_t rgblight_config;
#define NUM_LEDS_PER_SIDE 27
#define NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE 27

enum custom_keycodes {
    PASSWORD = SAFE_RANGE,
    CTRL
};
void set_color_split(uint8_t key_code, uint8_t r, uint8_t g, uint8_t b) {
    // When using defines for MASTER_LEFT and MASTER_RIGHT, is_keyboard_left()
    // will be inaccurate. For example, (is_keyboard_left() &&
    // !is_keyboard_master()) can NEVER be true.
#ifdef MASTER_LEFT
    bool is_left = true;
#endif
#ifdef MASTER_RIGHT
    bool is_left = false;
#endif

    bool left_is_master = (is_keyboard_master() && is_left) || (!is_keyboard_master() && !is_left);

    // Note on constants: 23 is the number of LEDs on each side (24) minus 1.
    // 27 is the number of LEDs that the Corne normally has with six columns.

    // Rule #1: you must set the LED based on what the master's range is. So if
    // the USB cable is in the left half, then the range is 0-23, otherwise it's
    // 27-50.

    // Rule #2: each half of the keyboard can only set its own LEDs, it's just
    // that the codes change according to Rule #1.

    // Rule #2
    if ((is_left && key_code >= NUM_LEDS_PER_SIDE) || (!is_left && key_code < NUM_LEDS_PER_SIDE)) {
        return;
    }

    // Rule #1
    if (left_is_master && key_code >= NUM_LEDS_PER_SIDE)
        key_code -= NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE;
    else if (!left_is_master && key_code < NUM_LEDS_PER_SIDE)
        key_code += NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE;
    rgb_matrix_set_color(key_code, r, g, b);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) { //https://docs.qmk.fm/#/custom_quantum_functions?id=programming-the-behavior-of-any-keycode
    switch (keycode) {
    case PASSWORD:
        if (record->event.pressed) {
        // Do something when pressed
            send_string_with_delay(secrets[keycode - PASSWORD], 1);
        }
        else {
        // Do something else when release
        }
        return false; // Skip all further processing of this key
     //   break;
   /* case CTRL: // Could not get this to work, was trying to change RGBs when ctrl was held down, flashes white for a millisecond when held down even though it keeps the registered code
//        static rgblight_config_t rgb_config_TEMP;
        if (record->event.pressed) {
            register_code(KC_LCTL);
            //rgb_config_TEMP = rgblight_config;
            //rgb_matrix_set_color_all(RGB_BLACK);
            rgb_matrix_set_color(5, RGB_WHITE);
            rgb_matrix_set_color(4, RGB_WHITE);
            rgb_matrix_set_color(10, RGB_WHITE);
            rgb_matrix_set_color(22, RGB_WHITE);
            rgb_matrix_set_color(20, RGB_WHITE);
            rgb_matrix_set_color(3, RGB_WHITE);
            //set_color_split(5, RGB_WHITE);
            //set_color_split(4, RGB_WHITE);
            //set_color_split(3, RGB_WHITE);
            //set_color_split(2, RGB_WHITE);
            //set_color_split(1, RGB_WHITE);
        } else {                                // When button is released
            unregister_code(KC_LCTL);
          //  rgblight_config = rgb_config_TEMP;
        } */
      //  break;
    return true;
    default:
      return true; // Process all other keycodes normally
    }
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    LT(1,KC_TAB),LCTL_T(KC_BSPC), LSFT_T(KC_SPACE),     LSFT_T(KC_SPACE), RCTL_T(KC_BSPC), LT(2,KC_TAB)
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       SGUI(KC_S),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, _______, _______, _______, _______, _______,                      _______, _______,   _______,_______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______, _______,  _______,     _______,   KC_DEL, LT(3,KC_TAB)
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, KC_1,   KC_2, KC_3,  KC_4, KC_5,                      KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_RCTL, _______, _______, _______, _______, _______,                      KC_HOME,  KC_UP, KC_END, _______, _______,  KC_BSLASH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_LEFT, KC_DOWN, KC_RIGHT, KC_LBRC, KC_RBRC, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        LT(3,KC_TAB),KC_DEL,_______,     _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        PASSWORD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                            KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, KC_LALT, KC_TAB,                      KC_VOLD, KC_VOLU, KC_MPLY, _______, _______, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,LCTL(KC_LALT), KC_DEL,                  KC_INSERT, LCTL(KC_LALT), _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,     _______, RESET, _______
                                      //`--------------------------'  `--------------------------'
  )
};


// This is a thin wrapper around rgb_matrix_set_color which allows you to put
// the same firmware on both halves of the keyboard (other than a #define for
// `MASTER_LEFT` or `MASTER_RIGHT`) and still have the correct LEDs light up
// regardless of which half has the USB cable in it.
//
// This complexity behind this logic is explained in the comments within the
// function itself.
//STOLE FROM HERE

    // Diagram of underglow LEDs on the both sides when viewed from above:
    //
    //
    // (LED 0 is underneath the "R" key on a QWERTY keyboard)
    // (LED 29 is underneath the "P" key on a QWERTY keyboard)
    //
    //          2   1   0            27  28  29
    //          3   4   5            32  31  30
    //
    // Diagram of per-key LEDs on the both sides when viewed from above:
    // 24 23  18  17  10  9         36  37  44  45  50  51
    // 25 22  19  16  11  8         35  38  43  46  49  52
    // 26 21  20  15  12  7         34  39  42  47  48  53
    //            14  13  6         33  40  41

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {         //https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix#callbacks-id-callbacks

        uint8_t mod_state = get_mods();
        if(mod_state & MOD_MASK_CTRL) {
                set_color_split(19, RGB_GREEN); //SAVE
                set_color_split(15, RGB_WHITE); //COPY
                set_color_split(12, RGB_RED); //PASTE
                set_color_split(20, RGB_ORANGE); //CUT
                set_color_split(21, RGB_RED); //UNDO
        }

    for (uint8_t i = led_min; i <= led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 1:
                set_color_split(0, RGB_WHITE);
                set_color_split(1, RGB_WHITE);
                set_color_split(2, RGB_WHITE);
                set_color_split(3, RGB_WHITE);
                set_color_split(4, RGB_WHITE);
                set_color_split(5, RGB_WHITE);
                set_color_split(24, RGB_RED);//screenshot button
                set_color_split(25, RGB_ORANGE);//gui
                break;
            case 2:
                set_color_split(27, RGB_WHITE);
                set_color_split(28, RGB_WHITE);
                set_color_split(29, RGB_WHITE);
                set_color_split(30, RGB_WHITE);
                set_color_split(31, RGB_WHITE);
                set_color_split(32, RGB_WHITE);
                set_color_split(38, RGB_WHITE);//up
                set_color_split(35, RGB_GREEN);//home
                set_color_split(43, RGB_GREEN);//end
                set_color_split(34, RGB_WHITE);//left
                set_color_split(39, RGB_WHITE);//down
                set_color_split(42, RGB_WHITE);//right
                break;
            case 3:
                set_color_split(0, RGB_WHITE);
                set_color_split(1, RGB_WHITE);
                set_color_split(2, RGB_WHITE);
                set_color_split(3, RGB_WHITE);
                set_color_split(4, RGB_WHITE);
                set_color_split(5, RGB_WHITE);
                set_color_split(27, RGB_WHITE);
                set_color_split(28, RGB_WHITE);
                set_color_split(29, RGB_WHITE);
                set_color_split(30, RGB_WHITE);
                set_color_split(31, RGB_WHITE);
                set_color_split(32, RGB_WHITE);
                set_color_split(35, RGB_WHITE);//volup
                set_color_split(38, RGB_WHITE);//voldown
                set_color_split(40, RGB_RED); //reset button
                set_color_split(11, RGB_WHITE);//alt
                set_color_split(8, RGB_WHITE);//tab
                set_color_split(12, RGB_ORANGE);//ctrl alt
                set_color_split(7, RGB_ORANGE);//del
                break;
            default:
                break;
        }
    }
}
