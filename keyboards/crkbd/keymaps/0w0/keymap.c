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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G,   KC_H, RCTL_T(KC_J), RSFT_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
       MO(1),  LT(2, KC_SPC),  KC_BSPC,    KC_ENT, LT(1, KC_TAB), MO(1)
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL, XXXXXXX,   KC_1,    KC_2,    KC_3,    KC_0,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3), KC_BSPC,     KC_ENT, _______, KC_RALT
                                      //`------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_BSPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE

/* combos */
enum combos {
    SDF_ENTER,
    XCV_ESC,
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
    ER_U,
    RE_Y,
    CV_N,
    XV_M,
    XC_COMMA,
    AS_DOT,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM sdf_ent_combo[] = {LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM xcv_esc_combo[] = {LALT_T(KC_X), LCTL_T(KC_C), COMBO_END};
const uint16_t PROGMEM sef_caps_word_combo[] = {LALT_T(KC_S), KC_E, LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM fe_i_combo[] = {LCTL_T(KC_F), KC_E, COMBO_END};
const uint16_t PROGMEM se_unds_combo[] = {LALT_T(KC_S), KC_E, COMBO_END};
const uint16_t PROGMEM sr_mins_combo[] = {LALT_T(KC_S), KC_R, COMBO_END};
const uint16_t PROGMEM df_j_combo[] = {LSFT_T(KC_D), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM sd_k_combo[] = {LALT_T(KC_S), LSFT_T(KC_D), COMBO_END};
const uint16_t PROGMEM af_p_combo[] = {LGUI_T(KC_A), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM ad_h_combo[] = {LGUI_T(KC_A), LSFT_T(KC_D), COMBO_END};
const uint16_t PROGMEM fs_l_combo[] = {LCTL_T(KC_F), LALT_T(KC_S), COMBO_END};
const uint16_t PROGMEM we_o_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM er_u_combo[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM cv_n_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM xv_m_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM xc_comma_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM as_dot_combo[] = {LGUI_T(KC_A), LALT_T(KC_S), COMBO_END};

combo_t key_combos[] = {
    [SDF_ENTER] = COMBO(sdf_ent_combo, KC_ENT),
    [XCV_ESC] = COMBO(xcv_esc_combo, KC_ESC),
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
    [ER_U] = COMBO(er_u_combo, KC_U),
    [RE_Y] = COMBO(cv_n_combo, KC_Y),
    [CV_N] = COMBO(cv_n_combo, KC_N),
    [XV_M] = COMBO(xv_m_combo, KC_M),
    [XC_COMMA] = COMBO(xc_comma_combo, KC_COMM),
    [AS_DOT] = COMBO(as_dot_combo, KC_DOT),
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
