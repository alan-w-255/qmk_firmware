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

#define KEY_A LT(1, KC_A)
#define KEY_S LT(5, KC_S)
#define KEY_D LT(4, KC_D)
#define KEY_F LT(2, KC_F)

#define KEY_J LT(2, KC_J)
#define KEY_K LT(4, KC_K)
#define KEY_L LT(5, KC_L)
#define KEY_SCLN LT(1, KC_SCLN)

#define KEY_THUMB_L_1 LGUI_T(KC_BSPC)
#define KEY_THUMB_L_2 LCTL_T(KC_SPC)
#define KEY_THUMB_L_3 LALT_T(KC_LEFT)
#define KEY_THUMB_R_1 RGUI_T(KC_BSPC)
#define KEY_THUMB_R_2 RCTL_T(KC_SPC)
#define KEY_THUMB_R_3 RALT_T(KC_RGHT)

// quad function tab dance
typedef struct {
    bool is_press_action;
    int  state;
} tap;

enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5, // send two single taps
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7
};

// Tap dance enums
enum {
    TD_SPC_CTL = 0,
    TD_ALT_CTL = 1,
    TD_GUI_SFT = 2,
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KEY_THUMB_L_2:
            return 170;
        case KEY_THUMB_L_1:
            return 170;
        case KEY_THUMB_L_3:
            return 170;
        default:
            return TAPPING_TERM;
    }
}

int cur_dance(tap_dance_state_t *state);
int cur_dance_modifier(tap_dance_state_t *state);

// for the x tap dance. Put it here so it can be used in any keymap
void td_spc_ctl_finished(tap_dance_state_t *state, void *user_data);
void td_spc_ctl_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_ESC, KEY_A, KEY_S, KEY_D, KEY_F, KC_G, KC_H, KEY_J, KEY_K, KEY_L, KEY_SCLN, KC_ESC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KEY_THUMB_L_3, KEY_THUMB_L_2, KEY_THUMB_L_1, KEY_THUMB_R_1, KEY_THUMB_R_2, KEY_THUMB_R_3
        //`--------------------------'  `--------------------------'

        ),

    [1] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, TO(0), KC_1, KC_2, KC_3, KC_MINS, KC_MINS, KC_3, KC_2, KC_1, TO(0), _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_DOT, KC_4, KC_5, KC_6, KC_0, KC_0, KC_6, KC_5, KC_4, KC_DOT, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_COLN, KC_7, KC_8, KC_9, KC_PLUS, KC_PLUS, KC_9, KC_8, KC_7, KC_COLN, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______
        //`------------------------'  `--------------------------'
        ),

    [2] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, KC_EXLM, KC_LEFT, KC_RIGHT, KC_DLR, _______, _______, KC_DLR, KC_LEFT, KC_RIGHT, KC_EXLM, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_AT, KC_UP, KC_DOWN, _______, _______, _______, _______, KC_DOWN, KC_UP, KC_BSLS, KC_GRV,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_HASH, KC_LABK, KC_RABK, _______, _______, KC_UNDS, KC_PLUS, KC_LABK, KC_RABK, KC_HASH, KC_TILD,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, LCTL(KC_SPC), KC_DEL, KC_DEL, LCTL(KC_SPC), _______
        //`--------------------------'  `--------------------------'
        ),

    [3] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, TO(0), KC_F1, KC_F2, KC_F3, KC_F10, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, _______, KC_F4, KC_F5, KC_F6, KC_F11, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, _______, KC_F7, KC_F8, KC_F9, KC_F12, _______, _______, _______, _______, _______, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______
        //`------------------------'  `--------------------------'
        ),

    [4] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, _______, KC_PERC, _______, KC_LCBR, KC_RCBR, KC_RCBR, KC_LCBR, _______, KC_PERC, _______, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_GRV, KC_BSLS, _______, OSM(MOD_LSFT), CW_TOGG, CW_TOGG, OSM(MOD_LSFT), _______, KC_BSLS, KC_GRV, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, KC_QUOT, _______, _______, KC_QUOT, _______, _______, _______, _______,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, LCTL(KC_BSLS), _______, _______, LCTL(KC_BSLS), _______
        //`------------------------'  `--------------------------'
        ),

    // 多媒体控制
    [5] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, _______, _______, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, KC_VOLU, KC_VOLD, KC_MPLY, _______, _______, _______, _______, _______, _______,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        _______, LCTL(KC_BSLS), _______, _______, _______, _______
        //`------------------------'  `--------------------------'
        ),

};

/* combos */
enum combos {
    SDF_ENTER,
    JKL_ENTER,
    RG_TAB,
    UH_TAB,
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

    // right alphas combos
    UI_T,
    JI_E,
    LM_R,
    JK_F,
    LK_G,
    JO_Q,
    KDOT_D,
    JL_S,
    MCOMMA_X,
    JSCLN_A,
    ISCLN_Z,
    DOTCOMMA_C,
    OI_W,
    MN_B,
    MDOT_V,

    // 符号 combos
    DV_EQL,
    SE_UNDS,
    SR_MINS,
    AE_SCLN,
    AW_COLN,
    WR_PLUS,
    XC_COMMA,
    AF_DOT,
    DW_SLASH,
    RF_LPRN,
    TG_RPRN,
    FV_LBRC,
    GB_RBRC,
    FG_ASTR,
    TR_AMPR,
    BF_CIRC,

    // right symbol combos
    KM_EQL,
    LI_UNDS,
    LU_MINS,
    /* OSCLN_COLN, */
    OU_PLUS,
    UJ_LPRN,
    YH_RPRN,
    JM_LBRC,
    HN_RBRC,
    JH_ASTR,
    /* UY_AMPR, */
    /* NJ_CIRC, */

    // layer switch combos
    ASDF_LAYER,
    WSPS_LAYER,

    // function combos
    ARROW_LR_PGUP,
    ARROW_UD_PGDN,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM sdf_ent_combo[]       = {KEY_S, KEY_D, KEY_F, COMBO_END};
const uint16_t PROGMEM jkl_ent_combo[]       = {KEY_J, KEY_K, KEY_L, COMBO_END};
const uint16_t PROGMEM rg_tab_combo[]        = {KC_R, KC_G, COMBO_END};
const uint16_t PROGMEM uh_tab_combo[]        = {KC_U, KC_H, COMBO_END};
const uint16_t PROGMEM fe_i_combo[]          = {KEY_F, KC_E, COMBO_END};
const uint16_t PROGMEM se_unds_combo[]       = {KEY_S, KC_E, COMBO_END};
const uint16_t PROGMEM sr_mins_combo[]       = {KEY_S, KC_R, COMBO_END};
const uint16_t PROGMEM sv_u_combo[]          = {KEY_S, KC_V, COMBO_END};
const uint16_t PROGMEM ae_scln_combo[]       = {KEY_A, KC_E, COMBO_END};
const uint16_t PROGMEM aw_coln_combo[]       = {KEY_A, KC_W, COMBO_END};
const uint16_t PROGMEM df_j_combo[]          = {KEY_D, KEY_F, COMBO_END};
const uint16_t PROGMEM dv_eql_combo[]        = {KEY_D, KC_V, COMBO_END};
const uint16_t PROGMEM sd_k_combo[]          = {KEY_S, KEY_D, COMBO_END};
const uint16_t PROGMEM fw_p_combo[]          = {KEY_F, KC_W, COMBO_END};
const uint16_t PROGMEM fs_l_combo[]          = {KEY_F, KEY_S, COMBO_END};
const uint16_t PROGMEM dx_h_combo[]          = {KEY_D, KC_X, COMBO_END};
const uint16_t PROGMEM we_o_combo[]          = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM wr_plus_combo[]       = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM re_y_combo[]          = {KC_R, KC_E, COMBO_END};
const uint16_t PROGMEM cv_n_combo[]          = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM xv_m_combo[]          = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM xc_comma_combo[]      = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM af_dot_combo[]        = {KEY_A, KEY_F, COMBO_END};
const uint16_t PROGMEM dw_slash_combo[]      = {KEY_D, KC_W, COMBO_END};
const uint16_t PROGMEM rf_lprn_combo[]       = {KC_R, KEY_F, COMBO_END};
const uint16_t PROGMEM tg_rprn_combo[]       = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM yh_rprn_combo[]       = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM uj_lprn_combo[]       = {KC_U, KEY_J, COMBO_END};
const uint16_t PROGMEM fv_lbrc_combo[]       = {KEY_F, KC_V, COMBO_END};
const uint16_t PROGMEM gb_rbrc_combo[]       = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM fg_astr_combo[]       = {KEY_F, KC_G, COMBO_END};
const uint16_t PROGMEM tr_ampr_combo[]       = {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM bf_circ_combo[]       = {KC_B, KEY_F, COMBO_END};
const uint16_t PROGMEM arrow_lr_pgup_combo[] = {KC_LEFT, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM arrow_ud_pgdn_combo[] = {KC_UP, KC_DOWN, COMBO_END};
const uint16_t PROGMEM asdf_layer_combo[]    = {KEY_A, KEY_S, KEY_D, KEY_F, COMBO_END};
const uint16_t PROGMEM wsps_layer_combo[]    = {KC_W, KEY_THUMB_L_2, COMBO_END};
const uint16_t PROGMEM ji_e_combo[]          = {KEY_J, KC_I, COMBO_END};
const uint16_t PROGMEM lm_r_combo[]          = {KEY_L, KC_M, COMBO_END};
const uint16_t PROGMEM jk_f_combo[]          = {KEY_J, KEY_K, COMBO_END};
const uint16_t PROGMEM lk_g_combo[]          = {KEY_L, KEY_K, COMBO_END};
const uint16_t PROGMEM jo_q_combo[]          = {KEY_J, KC_O, COMBO_END};
const uint16_t PROGMEM kdot_d_combo[]        = {KEY_K, KC_DOT, COMBO_END};
const uint16_t PROGMEM jl_s_combo[]          = {KEY_J, KEY_L, COMBO_END};
const uint16_t PROGMEM mcomma_x_combo[]      = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM jscln_a_combo[]       = {KEY_J, KEY_SCLN, COMBO_END};
const uint16_t PROGMEM iscln_z_combo[]       = {KC_I, KEY_SCLN, COMBO_END};
const uint16_t PROGMEM dotcomma_c_combo[]    = {KC_DOT, KC_COMM, COMBO_END};
const uint16_t PROGMEM oi_w_combo[]          = {KC_O, KC_I, COMBO_END};
const uint16_t PROGMEM ui_t_combo[]          = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM mn_b_combo[]          = {KC_M, KC_N, COMBO_END};
const uint16_t PROGMEM mdot_b_combo[]        = {KC_M, KC_DOT, COMBO_END};
const uint16_t PROGMEM km_eql_combo[]        = {KEY_K, KC_M, COMBO_END};
const uint16_t PROGMEM li_unds_combo[]       = {KEY_L, KC_I, COMBO_END};
const uint16_t PROGMEM lu_mins_combo[]       = {KEY_L, KC_U, COMBO_END};
const uint16_t PROGMEM ou_plus_combo[]       = {KC_O, KC_U, COMBO_END};
const uint16_t PROGMEM jm_lbrc_combo[]       = {KEY_J, KC_M, COMBO_END};
const uint16_t PROGMEM hn_rbrc_combo[]       = {KC_H, KC_N, COMBO_END};
const uint16_t PROGMEM jh_astr_combo[]       = {KEY_J, KC_H, COMBO_END};

combo_t key_combos[] = {
    [SDF_ENTER]     = COMBO(sdf_ent_combo, KC_ENT),
    [JKL_ENTER]     = COMBO(jkl_ent_combo, KC_ENT),
    [RG_TAB]        = COMBO(rg_tab_combo, KC_TAB),
    [UH_TAB]        = COMBO(uh_tab_combo, KC_TAB),
    [FE_I]          = COMBO(fe_i_combo, KC_I),
    [SE_UNDS]       = COMBO(se_unds_combo, KC_UNDS),
    [SR_MINS]       = COMBO(sr_mins_combo, KC_MINS),
    [SV_U]          = COMBO(sv_u_combo, KC_U),
    [AE_SCLN]       = COMBO(ae_scln_combo, KC_SCLN),
    [AW_COLN]       = COMBO(aw_coln_combo, KC_COLN),
    [DF_J]          = COMBO(df_j_combo, KC_J),
    [DV_EQL]        = COMBO(dv_eql_combo, KC_EQL),
    [SD_K]          = COMBO(sd_k_combo, KC_K),
    [FW_P]          = COMBO(fw_p_combo, KC_P),
    [FS_L]          = COMBO(fs_l_combo, KC_L),
    [DX_H]          = COMBO(dx_h_combo, KC_H),
    [WE_O]          = COMBO(we_o_combo, KC_O),
    [WR_PLUS]       = COMBO(wr_plus_combo, KC_PLUS),
    [RE_Y]          = COMBO(re_y_combo, KC_Y),
    [CV_N]          = COMBO(cv_n_combo, KC_N),
    [XV_M]          = COMBO(xv_m_combo, KC_M),
    [XC_COMMA]      = COMBO(xc_comma_combo, KC_COMM),
    [AF_DOT]        = COMBO(af_dot_combo, KC_DOT),
    [DW_SLASH]      = COMBO(dw_slash_combo, KC_SLSH),
    [RF_LPRN]       = COMBO(rf_lprn_combo, KC_LPRN),
    [TG_RPRN]       = COMBO(tg_rprn_combo, KC_RPRN),
    [YH_RPRN]       = COMBO(yh_rprn_combo, KC_RPRN),
    [UJ_LPRN]       = COMBO(uj_lprn_combo, KC_LPRN),
    [FV_LBRC]       = COMBO(fv_lbrc_combo, KC_LBRC),
    [GB_RBRC]       = COMBO(gb_rbrc_combo, KC_RBRC),
    [FG_ASTR]       = COMBO(fg_astr_combo, KC_ASTR),
    [TR_AMPR]       = COMBO(tr_ampr_combo, KC_AMPR),
    [BF_CIRC]       = COMBO(bf_circ_combo, KC_CIRC),
    [ASDF_LAYER]    = COMBO(asdf_layer_combo, TO(3)),
    [WSPS_LAYER]    = COMBO(wsps_layer_combo, TO(1)),
    [ARROW_LR_PGUP] = COMBO(arrow_lr_pgup_combo, KC_PGUP),
    [ARROW_UD_PGDN] = COMBO(arrow_ud_pgdn_combo, KC_PGDN),
    [JK_F]          = COMBO(jk_f_combo, KC_F),
    [UI_T]          = COMBO(ui_t_combo, KC_T),
    [JI_E]          = COMBO(ji_e_combo, KC_E),
    [LM_R]          = COMBO(lm_r_combo, KC_R),
    [LK_G]          = COMBO(lk_g_combo, KC_G),
    [JO_Q]          = COMBO(jo_q_combo, KC_Q),
    [KDOT_D]        = COMBO(kdot_d_combo, KC_D),
    [JL_S]          = COMBO(jl_s_combo, KC_S),
    [MCOMMA_X]      = COMBO(mcomma_x_combo, KC_X),
    [JSCLN_A]       = COMBO(jscln_a_combo, KC_A),
    [ISCLN_Z]       = COMBO(iscln_z_combo, KC_Z),
    [DOTCOMMA_C]    = COMBO(dotcomma_c_combo, KC_C),
    [OI_W]          = COMBO(oi_w_combo, KC_W),
    [MN_B]          = COMBO(mn_b_combo, KC_B),
    [MDOT_V]        = COMBO(mdot_b_combo, KC_V),
    [KM_EQL]        = COMBO(km_eql_combo, KC_EQL),
    [LI_UNDS]       = COMBO(li_unds_combo, KC_UNDS),
    [LU_MINS]       = COMBO(lu_mins_combo, KC_MINS),
    [OU_PLUS]       = COMBO(ou_plus_combo, KC_PLUS),
    [JM_LBRC]       = COMBO(jm_lbrc_combo, KC_LBRC),
    [HN_RBRC]       = COMBO(hn_rbrc_combo, KC_RBRC),
    [JH_ASTR]       = COMBO(jh_astr_combo, KC_ASTR),
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8; // magic number. At some point this method will expand to work for more presses
}

// modifier 意味着 state->interrupted 的时候更应该表现为修饰符。而不是多次输入
int cur_dance_modifier(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (!state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8; // magic number. At some point this method will expand to work for more presses
}

// instanalize an instance of 'tap' for the 'x' tap dance.
static tap spc_ctl_tap_state = {.is_press_action = true, .state = 0};

void td_spc_ctl_finished(tap_dance_state_t *state, void *user_data) {
    spc_ctl_tap_state.state = cur_dance_modifier(state);
    switch (spc_ctl_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_SPC);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTL);
            break;
        case DOUBLE_TAP:
            register_code(KC_SPC);
            unregister_code(KC_SPC);
            register_code(KC_SPC);
            break;
        case DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            break;
        default:
            register_code(KC_SPC);
            for (int i = 1; i < state->count; i++) {
                unregister_code(KC_SPC);
                register_code(KC_SPC);
            }
            break;
    }
}

void td_spc_ctl_reset(tap_dance_state_t *state, void *user_data) {
    switch (spc_ctl_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_SPC);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LCTL);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_SPC);
            break;
        case DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            break;
        default:
            unregister_code(KC_SPC);
            break;
    }
    spc_ctl_tap_state.state = 0;
}

static tap alt_ctl_tap_state = {.is_press_action = true, .state = 0};

void td_alt_ctl_finished(tap_dance_state_t *state, void *user_data) {
    alt_ctl_tap_state.state = cur_dance_modifier(state);
    switch (alt_ctl_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LEFT);
            break;
        case SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        case DOUBLE_TAP:
            register_code(KC_LEFT);
            unregister_code(KC_LEFT);
            register_code(KC_LEFT);
            break;
        case DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LALT);
            break;
        default:
            register_code(KC_LEFT);
            for (int i = 1; i < state->count; i++) {
                unregister_code(KC_LEFT);
                register_code(KC_LEFT);
            }
            break;
    }
}

void td_alt_ctl_reset(tap_dance_state_t *state, void *user_data) {
    switch (alt_ctl_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_LEFT);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_LEFT);
            break;
        case DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            break;
        default:
            unregister_code(KC_LEFT);
            break;
    }
    alt_ctl_tap_state.state = 0;
}

static tap super_shift_tap_state = {.is_press_action = true, .state = 0};

void td_super_shift_finished(tap_dance_state_t *state, void *user_data) {
    super_shift_tap_state.state = cur_dance_modifier(state);
    switch (super_shift_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_BSPC);
            break;
        case SINGLE_HOLD:
            register_code(KC_LGUI);
            break;
        case DOUBLE_TAP:
            register_code(KC_BSPC);
            unregister_code(KC_BSPC);
            register_code(KC_BSPC);
            break;
        case DOUBLE_HOLD:
            register_code(KC_LSFT);
            break;
        default:
            register_code(KC_BSPC);
            for (int i = 1; i < state->count; i++) {
                unregister_code(KC_BSPC);
                register_code(KC_BSPC);
            }
            break;
    }
}

void td_super_shift_reset(tap_dance_state_t *state, void *user_data) {
    switch (super_shift_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_BSPC);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LGUI);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_BSPC);
            break;
        case DOUBLE_HOLD:
            unregister_code(KC_LSFT);
            break;
        default:
            unregister_code(KC_BSPC);
            break;
    }
    super_shift_tap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SPC_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_spc_ctl_finished, td_spc_ctl_reset),
    [TD_ALT_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_alt_ctl_finished, td_alt_ctl_reset),
    [TD_GUI_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_super_shift_finished, td_super_shift_reset),
};
