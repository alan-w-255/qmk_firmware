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
       KC_ESC,    KEY_A,   KC_S,    KEY_D,   KEY_F,   KC_G,                         KC_H,    KEY_J,   KEY_K,   KC_L,   KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
			KEY_THUMB_L_3, KEY_THUMB_L_2, KEY_THUMB_L_1, KEY_THUMB_R_1, KEY_THUMB_R_2, KEY_THUMB_R_3
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  TO(0),    KC_1,    KC_2,    KC_3, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_DOT,   KC_4,    KC_5,    KC_6,    KC_0,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_COLN,    KC_7,    KC_8,    KC_9, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					_______, _______, _______,     _______, _______, _______
                                      //`------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       _______, KC_EXLM, KC_LEFT, KC_RIGHT,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_AT, KC_UP, KC_DOWN, _______, _______,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_HASH, KC_LABK, KC_RABK, _______, _______,                     KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
				    _______, LCTL(KC_SPC),  _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  TO(0),   KC_F1,   KC_F2,   KC_F3,  KC_F10,                        KC_F13, KC_F14, KC_F15, KC_F16,   KC_F17, KC_F18,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______,   KC_F4,    KC_F5,    KC_F6, KC_F11,                      KC_F19, KC_F20, KC_F21, KC_F22,   KC_F23, KC_F24,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______,    KC_F7,    KC_F8,    KC_F9, KC_F12,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					_______, _______, _______,     _______, _______, _______
                                      //`------------------------'  `--------------------------'
  ),

};

/* combos */
enum combos {
    SDF_ENTER,
    XCV_ESC,
    WER_TAB,
    SEF_CAPS_WORD,
    FWE_OS_SHIFT,

    // alphas combos
    FE_I,
    SV_U,
    DF_J,
    SD_K,
    FW_P,
    DX_H,
    FS_L,
    WE_O,
    RE_Y,
    CV_N,
    XV_M,

    // 符号 combos
    DV_EQL,
    SE_UNDS,
    SR_MINS,
    AE_SCLN,
    AR_QUOT,
    AW_COLN,
    FQ_GRV,
    WR_PLUS,
    XC_COMMA,
    AF_DOT,
    DW_SLASH,
    QW_BSLASH,
    RF_LPRN,
    TG_RPRN,
    FV_LBRC,
    GB_RBRC,
    WS_LCBR,
    ED_RCBR,
    FG_ASTR,
    RG_AMPR,
    BF_CIRC,

    // layer switch combos
    ASDF_LAYER,
    WSPS_LAYER,

    // function combos
    ARROW_LR_PGUP,
    ARROW_UD_PGDN,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM sdf_ent_combo[] = {KC_S, KEY_D, KEY_F, COMBO_END};
const uint16_t PROGMEM xcv_esc_combo[] = {KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM wer_tab[] = {KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM sef_caps_word_combo[] = {KC_S, KC_E, KEY_F, COMBO_END};
const uint16_t PROGMEM fwe_os_shift_combo[] = {KEY_F, KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM fe_i_combo[] = {KEY_F, KC_E, COMBO_END};
const uint16_t PROGMEM se_unds_combo[] = {KC_S, KC_E, COMBO_END};
const uint16_t PROGMEM sr_mins_combo[] = {KC_S, KC_R, COMBO_END};
const uint16_t PROGMEM sv_u_combo[] = {KC_S, KC_V, COMBO_END};
const uint16_t PROGMEM ae_scln_combo[] = {KEY_A, KC_E, COMBO_END};
const uint16_t PROGMEM ar_quot_combo[] = {KEY_A, KC_R, COMBO_END};
const uint16_t PROGMEM aw_coln_combo[] = {KEY_A, KC_W, COMBO_END};
const uint16_t PROGMEM fq_grv_combo[] = {KEY_F, KC_Q, COMBO_END};
const uint16_t PROGMEM df_j_combo[] = {KEY_D, KEY_F, COMBO_END};
const uint16_t PROGMEM dv_eql_combo[] = {KEY_D, KC_V, COMBO_END};
const uint16_t PROGMEM sd_k_combo[] = {KC_S, KEY_D, COMBO_END};
const uint16_t PROGMEM fw_p_combo[] = {KEY_F, KC_W, COMBO_END};
const uint16_t PROGMEM fs_l_combo[] = {KEY_F, KC_S, COMBO_END};
const uint16_t PROGMEM dx_h_combo[] = {KEY_D, KC_X, COMBO_END};
const uint16_t PROGMEM we_o_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM wr_plus_combo[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM re_y_combo[] = {KC_R, KC_E, COMBO_END};
const uint16_t PROGMEM cv_n_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM xv_m_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM xc_comma_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM af_dot_combo[] = {KEY_A, KEY_F, COMBO_END};
const uint16_t PROGMEM dw_slash_combo[] = {KEY_D, KC_W, COMBO_END};
const uint16_t PROGMEM qw_bslash_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM rf_lprn_combo[] = {KC_R, KEY_F, COMBO_END};
const uint16_t PROGMEM tg_rprn_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM fv_lbrc_combo[] = {KEY_F, KC_V, COMBO_END};
const uint16_t PROGMEM gb_rbrc_combo[] = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM ws_lcbr_combo[] = {KC_W, KC_S, COMBO_END};
const uint16_t PROGMEM ed_rcbr_combo[] = {KC_E, KEY_D, COMBO_END};
const uint16_t PROGMEM fg_astr_combo[] = {KEY_F, KC_G, COMBO_END};
const uint16_t PROGMEM rg_ampr_combo[] = {KC_R, KC_G, COMBO_END};
const uint16_t PROGMEM bf_circ_combo[] = {KC_B, KEY_F, COMBO_END};
const uint16_t PROGMEM arrow_lr_pgup_combo[] = {KC_LEFT, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM arrow_ud_pgdn_combo[] = {KC_UP, KC_DOWN, COMBO_END};
const uint16_t PROGMEM asdf_layer_combo[] = {KEY_A, KC_S, KEY_D, KEY_F, COMBO_END};
const uint16_t PROGMEM wsps_layer_combo[] = {KC_W, KEY_THUMB_L_2, COMBO_END};

combo_t key_combos[] = {
    [SDF_ENTER] = COMBO(sdf_ent_combo, KC_ENT),
    [XCV_ESC] = COMBO(xcv_esc_combo, KC_ESC),
    [WER_TAB] = COMBO(wer_tab, KC_TAB),
    [SEF_CAPS_WORD] = COMBO(sef_caps_word_combo, KC_NO),
    [FWE_OS_SHIFT] = COMBO(fwe_os_shift_combo, OSM(MOD_LSFT)),
    [FE_I] = COMBO(fe_i_combo, KC_I),
    [SE_UNDS] = COMBO(se_unds_combo, KC_UNDS),
    [SR_MINS] = COMBO(sr_mins_combo, KC_MINS),
    [SV_U] = COMBO(sv_u_combo, KC_U),
    [AE_SCLN] = COMBO(ae_scln_combo, KC_SCLN),
    [AR_QUOT] = COMBO(ar_quot_combo, KC_QUOT),
    [AW_COLN] = COMBO(aw_coln_combo, KC_COLN),
    [FQ_GRV] = COMBO(fq_grv_combo, KC_GRV),
    [DF_J] = COMBO(df_j_combo, KC_J),
    [DV_EQL] = COMBO(dv_eql_combo, KC_EQL),
    [SD_K] = COMBO(sd_k_combo, KC_K),
    [FW_P] = COMBO(fw_p_combo, KC_P),
    [FS_L] = COMBO(fs_l_combo, KC_L),
    [DX_H] = COMBO(dx_h_combo, KC_H),
    [WE_O] = COMBO(we_o_combo, KC_O),
    [WR_PLUS] = COMBO(wr_plus_combo, KC_PLUS),
    [RE_Y] = COMBO(re_y_combo, KC_Y),
    [CV_N] = COMBO(cv_n_combo, KC_N),
    [XV_M] = COMBO(xv_m_combo, KC_M),
    [XC_COMMA] = COMBO(xc_comma_combo, KC_COMM),
    [AF_DOT] = COMBO(af_dot_combo, KC_DOT),
    [DW_SLASH] = COMBO(dw_slash_combo, KC_SLSH),
    [QW_BSLASH] = COMBO(qw_bslash_combo, KC_BSLS),
    [RF_LPRN] = COMBO(rf_lprn_combo, KC_LPRN),
    [TG_RPRN] = COMBO(tg_rprn_combo, KC_RPRN),
    [FV_LBRC] = COMBO(fv_lbrc_combo, KC_LBRC),
    [GB_RBRC] = COMBO(gb_rbrc_combo, KC_RBRC),
    [WS_LCBR] = COMBO(ws_lcbr_combo, KC_LCBR),
    [ED_RCBR] = COMBO(ed_rcbr_combo, KC_RCBR),
    [FG_ASTR] = COMBO(fg_astr_combo, KC_ASTR),
    [RG_AMPR] = COMBO(rg_ampr_combo, KC_AMPR),
    [BF_CIRC] = COMBO(bf_circ_combo, KC_CIRC),
    [ASDF_LAYER] = COMBO(asdf_layer_combo, TO(3)),
    [WSPS_LAYER] = COMBO(wsps_layer_combo, TO(1)),
    [ARROW_LR_PGUP] = COMBO(arrow_lr_pgup_combo, KC_PGUP),
    [ARROW_UD_PGDN] = COMBO(arrow_ud_pgdn_combo, KC_PGDN),
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
