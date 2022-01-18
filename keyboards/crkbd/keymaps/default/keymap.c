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
//#ifdef OLED_DRIVER_ENABLE
//#include <stdio.h>
//char wpm_str[4]; //bongo
//#include "oled.c"
//#endif
/*typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;*/

//typedef struct {
//    bool is_press_action;
//    td_state_t state;
//} td_tap_t;

// Tap dance enums
//enum {
//    CT_DOTSPACE //mine
//};

//td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
//void x_finished(qk_tap_dance_state_t *state, void *user_data);
//void x_reset(qk_tap_dance_state_t *state, void *user_data);

enum custom_keycodes {
    PASSWORD = SAFE_RANGE,
};

 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //   if (record->event.pressed) {
        //oled_timer = timer_read();
    //    extern uint32_t tap_timer;
      //  tap_timer = timer_read32();
    //}
    switch (keycode) {
    case PASSWORD:
        if (record->event.pressed) {
            // when keycode PASSWORD is pressed
            send_string_with_delay(secrets[keycode - PASSWORD], 1);
            //SEND_STRING(secret);
        } 
        else {
            // when keycode PASSWORD is released
        }
        break;
    }
    return true;
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





void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {         //https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix#callbacks-id-callbacks
    for (uint8_t i = led_min; i <= led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 1:
                rgb_matrix_set_color(9, RGB_GREEN);//Save
                rgb_matrix_set_color(11, RGB_WHITE);//gui
                rgb_matrix_set_color(0, RGB_CYAN);//screenshot button
                break;
            case 2:
                rgb_matrix_set_color(34, RGB_WHITE);//up
                rgb_matrix_set_color(35, RGB_GREEN);//home
                rgb_matrix_set_color(33, RGB_GREEN);//end
                rgb_matrix_set_color(24, RGB_WHITE);//left
                rgb_matrix_set_color(25, RGB_WHITE);//down
                rgb_matrix_set_color(26, RGB_WHITE);//right
                break;
            case 3:
                rgb_matrix_set_color(51, RGB_WHITE);//volup
                rgb_matrix_set_color(50, RGB_WHITE);//voldown
                rgb_matrix_set_color(22, RGB_RED); //reset button
                rgb_matrix_set_color(6, RGB_WHITE);//alt
                rgb_matrix_set_color(7, RGB_WHITE);//tab
                rgb_matrix_set_color(17, RGB_ORANGE);//ctrl alt
                rgb_matrix_set_color(16, RGB_ORANGE);//del
                break;
            default:
                break;
        }
    }
}

/*void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {         //https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix#callbacks-id-callbacks
    for (uint8_t i = led_min; i <= led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 1:
                rgb_matrix_set_color(1, RGB_GREEN);//Save
 //               rgb_matrix_set_color(11, RGB_WHITE);//gui
                rgb_matrix_set_color(33, RGB_CYAN);//screenshot button

                
                rgb_matrix_set_color(9, RGB_RED);
                rgb_matrix_set_color(10, RGB_GREEN);
                rgb_matrix_set_color(17, RGB_BLUE);
                rgb_matrix_set_color(18, RGB_RED);
                rgb_matrix_set_color(23, RGB_WHITE);
                break;
            case 2:
                rgb_matrix_set_color(12, RGB_WHITE);//up
                rgb_matrix_set_color(35, RGB_GREEN);//home
               // rgb_matrix_set_color(33, RGB_GREEN);//end
               // rgb_matrix_set_color(24, RGB_WHITE);//left
               // rgb_matrix_set_color(25, RGB_WHITE);//down
             //   rgb_matrix_set_color(26, RGB_WHITE);//right
                break;
            case 3:
                rgb_matrix_set_color(34, RGB_WHITE);//volup
                rgb_matrix_set_color(35, RGB_WHITE);//voldown
                rgb_matrix_set_color(22, RGB_RED); //reset button
                rgb_matrix_set_color(6, RGB_WHITE);//alt
                rgb_matrix_set_color(7, RGB_WHITE);//tab
                rgb_matrix_set_color(17, RGB_ORANGE);//ctrl alt
                rgb_matrix_set_color(16, RGB_ORANGE);//del
                break; 
            default:
                break;
        }
    }
}*/


/*void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SPC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: unregister_code (KC_DOT); unregister_code (KC_SPC); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LCTL);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_SPC);
        default: break;
    }
    xtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_DOTSPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
}*/;