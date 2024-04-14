/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_1     , KC_2     , KC_3     , KC_4     , KC_5     , KC_6     ,                                  KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  , KC_EQL   , 
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_LBRC  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_GRV   , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B ,                   KC_B  , KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_BSLS  ,
    KC_LNG2  , KC_LNG1  , KC_LOPT  , KC_LOPT  , KC_LCMD  , KC_SPC   , MO(1),                 KC_RBRC , KC_ENT   , _______  , _______  , _______  , KC_RBRC  , KC_BSLS
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_F6    ,                                  KC_F7    , KC_F8    , KC_F9    , KC_F10   , _______  , KC_BSPC  ,
    KC_ESC   , _______  , _______  , KC_UP    , _______  , _______  ,                                  _______  , KC_BTN4  , KC_BTN3  , KC_BTN5  , _______  , KC_RBRC  ,
    _______  , _______  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,                                  _______  , KC_BTN1  , SCRL_MO  , KC_BTN2  , _______  , KC_BSLS  ,
    AML_TO   , AML_I50  , AML_D50  , SCRL_DVI , SCRL_DVD , _______  , _______               _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    KBC_SAVE , KBC_RST  , CPI_I100 , CPI_D100 , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

void keyboard_post_init_user() {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    set_auto_mouse_layer(1);
    set_auto_mouse_timeout(650);
    set_auto_mouse_enable(true);
#endif
    // 400CPI
    keyball_set_cpi(4);
    keyball_set_scroll_div(6);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
