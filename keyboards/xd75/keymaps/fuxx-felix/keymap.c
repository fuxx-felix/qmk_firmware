/* Copyright 2017 Wunder
 *
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
#include "keymap_uk.h"

// Keyboard timeout in min
#define IDLE 5
#define RGB_DEFAULT_MODE 1
#define RGB_DEFAULT_COLOUR HSV_ORANGE
#define RGB_IDLE_MODE 22
#define RGB_IDLE_COLOUR HSV_GREEN
#define RGB_FN_COLOUR HSV_RED

// Layer shorthand
#define _QW 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | HOME   | DEL    | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | FN     | LALT   | LGUI   | SPACE  | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | SPACE  |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    UK_ESC,  UK_1,    UK_2,    UK_3,    UK_4,    UK_5,    UK_MINS, UK_GRV,  UK_EQL,  UK_6,    UK_7,    UK_8,    UK_9,    UK_0,    UK_BSPC,
    UK_TAB,  UK_Q,    UK_W,    UK_E,    UK_R,    UK_T,    UK_LBRC, UK_BSLS, UK_RBRC, UK_Y,    UK_U,    UK_I,    UK_O,    UK_P,    UK_QUOT,
    KC_CAPS, UK_A,    UK_S,    UK_D,    UK_F,    UK_G,    UK_HOME, UK_DEL,  UK_PGUP, UK_H,    UK_J,    UK_K,    UK_L,    UK_SCLN, UK_ENT,
    UK_LSFT, UK_Z,    UK_X,    UK_C,    UK_V,    UK_B,    UK_END,  UK_UP,   UK_PGDN, UK_N,    UK_M,    UK_COMM, UK_DOT,  UK_SLSH, UK_RSFT,
    UK_LCTL, MO(_FN), UK_LALT, UK_LGUI, UK_SPC,  UK_SPC,  UK_LEFT, UK_DOWN, UK_RGHT, UK_SPC,  UK_SPC,  MO(_FN), UK_HASH, _______, _______
  ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | NUM LK | P/     | P*     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | P7     | P8     | P9     | -      |        |        | PR SCR | SCR LK | PAUSE  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | P4     | P5     | P6     | +      |        | RESET  |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | P1     | P2     | P3     | PENT   |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | FN     | LALT   | RGB TGL|        |        | P0     |        | P.     | PENT   |        | FN     |        |        | MUTE   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    UK_F1,   UK_F2,   UK_F3,   UK_F4,   UK_F5,   UK_F6,   KC_NLCK, UK_SLSH, UK_ASTR, UK_F7,   UK_F8,   UK_F9,   UK_F10,  UK_F11,  UK_F12,
    _______, _______, _______, RGB_M_R, _______, _______, UK_P7,   UK_P8,   UK_P9,   UK_MINS, _______, _______, UK_PSCR, UK_SLCK, UK_PAUS,
    _______, _______, _______, RGB_M_K, _______, _______, UK_P4,   UK_P5,   UK_P6,   UK_PLUS, _______, RESET,   _______, _______, _______,
    _______, _______, _______, RGB_M_P, _______, _______, UK_P1,   UK_P2,   UK_P3,   UK_PENT, _______, _______, _______, _______, _______,
    _______, MO(_FN), UK_LALT, RGB_TOG, RGB_M_T, _______, UK_P0,   _______, UK_PDOT, UK_PENT, _______, MO(_FN), _______, _______, KC_MUTE
  )
};

static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool standby = false;
static uint8_t rgb_mode = RGB_DEFAULT_MODE;
static uint8_t rgb_colour[3] = {RGB_DEFAULT_COLOUR};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  idle_timer = timer_read();
  if(standby == true) {
    standby = false;
    halfmin_counter = 0;
    rgblight_mode(rgb_mode);
    rgblight_sethsv(rgb_colour[0], rgb_colour[1], rgb_colour[2]);
  }
  return true;
}

void matrix_scan_user(void) {
  if (standby == false) {
    if (timer_elapsed(idle_timer) > 30000) {
      halfmin_counter++;
      idle_timer = timer_read();
    }

    // Note: Half min counter required to prevent integer overflow
    if (halfmin_counter >= IDLE * 2) {
      rgb_mode = rgblight_get_mode();
      rgb_colour[0] = rgblight_get_hue();
      rgb_colour[1] = rgblight_get_sat();
      rgb_colour[2] = rgblight_get_val();
      standby = true;
      rgblight_mode(RGB_IDLE_MODE);
      rgblight_sethsv(RGB_IDLE_COLOUR);
    }
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  switch(biton32(state)) {
  case _QW:
    rgblight_sethsv(RGB_DEFAULT_COLOUR);
    break;
  case _FN:
    rgblight_sethsv(RGB_FN_COLOUR);
    break;
  default:
    rgblight_sethsv(RGB_DEFAULT_COLOUR);
    break;
  }

  return state;
}
