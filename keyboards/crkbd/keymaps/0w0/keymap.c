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
#include <stdio.h>

#define KEY_D LSFT_T(KC_D)
#define KEY_F LT(2, KC_F)
#define KEY_J LT(1, KC_J)
#define KEY_K LSFT_T(KC_K)
#define KEY_A LT(1, KC_A)
#define KEY_THUMB_L_1 RGUI_T(KC_BSPC)
#define KEY_THUMB_L_2 LCTL_T(KC_SPC)
#define KEY_THUMB_L_3 LALT_T(KC_LEFT)
#define KEY_THUMB_R_1 RGUI_T(KC_ENT)
#define KEY_THUMB_R_2 RCTL_T(KC_TAB)
#define KEY_THUMB_R_3 RALT_T(KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, KEY_A, KC_S, KEY_D, KEY_F, KC_G,   KC_H, KEY_J, KEY_K, KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
       KEY_THUMB_L_3, KEY_THUMB_L_2, KEY_THUMB_L_1, KEY_THUMB_R_1, KEY_THUMB_R_2, KEY_THUMB_R_3
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______,    KC_4,    KC_5,    KC_6, _______,                      _______, _______, _______, _______, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       _______, _______,   KC_1,    KC_2,    KC_3,    KC_0,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______,    KC_7,    KC_8,    KC_9, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3), KC_BSPC,     KC_ENT, _______, KC_RALT
                                      //`------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, _______, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT, _______, _______, LCTL(KC_LEFT), LCTL(KC_RIGHT), _______,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_BSPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

};

/* combos */
enum combos {
    SDF_ENTER,
    XCV_ESC,
    WER_TAB,
    SEF_CAPS_WORD,
    FE_I,
    SE_UNDS,
    SR_MINS,
    DF_J,
    SD_K,
    AF_P,
    AD_H,
    FS_L,
    WE_O,
    WR_U,
    RE_Y,
    CV_N,
    XV_M,
    XC_COMMA,
    AS_DOT,
    fw_slash,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM sdf_ent_combo[] = {KC_S, KEY_D, KEY_F, COMBO_END};
const uint16_t PROGMEM xcv_esc_combo[] = {KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM wer_tab[] = {KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM sef_caps_word_combo[] = {KC_S, KC_E, KEY_F, COMBO_END};
const uint16_t PROGMEM fe_i_combo[] = {KEY_F, KC_E, COMBO_END};
const uint16_t PROGMEM se_unds_combo[] = {KC_S, KC_E, COMBO_END};
const uint16_t PROGMEM sr_mins_combo[] = {KC_S, KC_R, COMBO_END};
const uint16_t PROGMEM df_j_combo[] = {KEY_D, KEY_F, COMBO_END};
const uint16_t PROGMEM sd_k_combo[] = {KC_S, KEY_D, COMBO_END};
const uint16_t PROGMEM af_p_combo[] = {KEY_A, KEY_F, COMBO_END};
const uint16_t PROGMEM ad_h_combo[] = {KEY_A, KEY_D, COMBO_END};
const uint16_t PROGMEM fs_l_combo[] = {KEY_F, KC_S, COMBO_END};
const uint16_t PROGMEM we_o_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM wr_u_combo[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM re_y_combo[] = {KC_R, KC_E, COMBO_END};
const uint16_t PROGMEM cv_n_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM xv_m_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM xc_comma_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM as_dot_combo[] = {KEY_A, KC_S, COMBO_END};
const uint16_t PROGMEM fw_slash_combo[] = {KEY_F, KC_W, COMBO_END};

combo_t key_combos[] = {
    [SDF_ENTER] = COMBO(sdf_ent_combo, KC_ENT),
    [XCV_ESC] = COMBO(xcv_esc_combo, KC_ESC),
    [WER_TAB] = COMBO(wer_tab, KC_TAB),
    [SEF_CAPS_WORD] = COMBO(sef_caps_word_combo, KC_NO),
    [FE_I] = COMBO(fe_i_combo, KC_I),
    [SE_UNDS] = COMBO(se_unds_combo, KC_UNDS),
    [SR_MINS] = COMBO(sr_mins_combo, KC_MINS),
    [DF_J] = COMBO(df_j_combo, KC_J),
    [SD_K] = COMBO(sd_k_combo, KC_K),
    [AF_P] = COMBO(af_p_combo, KC_P),
    [AD_H] = COMBO(ad_h_combo, KC_H),
    [FS_L] = COMBO(fs_l_combo, KC_L),
    [WE_O] = COMBO(we_o_combo, KC_O),
    [WR_U] = COMBO(wr_u_combo, KC_U),
    [RE_Y] = COMBO(re_y_combo, KC_Y),
    [CV_N] = COMBO(cv_n_combo, KC_N),
    [XV_M] = COMBO(xv_m_combo, KC_M),
    [XC_COMMA] = COMBO(xc_comma_combo, KC_COMM),
    [AS_DOT] = COMBO(as_dot_combo, KC_DOT),
    [fw_slash] = COMBO(fw_slash_combo, KC_SLSH),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
	case SEF_CAPS_WORD:
	    if (pressed) {
		caps_word_toggle();
            }
	    break;
    }
}
