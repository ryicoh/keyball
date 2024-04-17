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

enum keymap_layers {
    _BS,  // Base
    _MO,  // Mouse1
    _MO2, // Mouse2
    _SET, // Setting
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT_universal(
    KC_1     , KC_2     , KC_3     , KC_4     , KC_5     , KC_6     ,                                  KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  , KC_EQL   , 
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_LBRC  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_GRV   , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B ,                   KC_B  , KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_BSLS  ,
    KC_LNG2  , KC_LNG1  , KC_LOPT  , KC_LOPT  , KC_LCMD  , KC_SPC   , MO(_MO),              KC_RBRC , KC_ENT   , _______  , _______  , _______  , KC_RBRC  , KC_BSLS
  ),

  [_MO] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_F6    ,                                  KC_F7    , KC_F8    , KC_F9    , KC_F10   , _______  , _______  ,
    _______  , _______  , _______  , KC_UP    , _______  , _______  ,                                  KC_BTN3  , KC_BTN4  , KC_BTN2  , KC_BTN5  , _______  , _______  ,
    _______  , _______  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,                                  _______  , KC_BTN1  , SCRL_MO  , _______  , MO(_MO2) , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            MO(_SET) , _______  , _______  , _______  , _______  , _______  , _______
  ),

  // マウス2レイヤー (DPIを半分にする)
  [_MO2] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_F6    ,                                  KC_F7    , KC_F8    , KC_F9    , KC_F10   , _______  , _______  ,
    _______  , _______  , _______  , KC_UP    , _______  , _______  ,                                  KC_BTN3  , KC_BTN4  , KC_BTN2  , KC_BTN5  , _______  , _______  ,
    _______  , _______  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,                                  _______  , KC_BTN1  , SCRL_MO  , _______  , MO(_MO2) , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            MO(_SET) , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [_SET] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    AML_TO   , AML_I50  , AML_D50  , SCRL_DVI , SCRL_DVD , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    KBC_SAVE , KBC_RST  , CPI_I100 , CPI_D100 , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

int base_cpi = 8;
int low_cpi = 3;

void set_cpi(int cpi) {
    int cur = keyball_get_cpi();
    if (cur == cpi) {
        return;
    }

    keyball_set_cpi(cpi);
}

void keyboard_post_init_user() {
    // Enable auto mouse
    set_auto_mouse_layer(_MO);
    set_auto_mouse_timeout(700);
    set_auto_mouse_enable(true);

    set_cpi(base_cpi);
    keyball_set_scroll_div(6);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // マウス2の場合はDIPを下げる
    switch(get_highest_layer(state)) {
        case _MO2:
            set_cpi(low_cpi);
            break;
        default:
            set_cpi(base_cpi);
            break;
    }
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
