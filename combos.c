#pragma once
#include QMK_KEYBOARD_H

enum combos {
    CB_COPY,
    CB_PASTE,
    CB_LPAR,
    CB_RPAR,
    CB_LBTK,
    CB_RBTK,
    CB_AT,
    CB_HASH,
    CB_DLLR,
    CB_PRCNT,
    CB_GRAVE,
    CB_BSLS,
    CB_EQL,
    CB_TILD,
    CB_CIRC,
    CB_PLUS,
    CB_ASTR,
    CB_AMPR,
    CB_UNDS,
    CB_MINS,
    CB_SLSH,
    CB_PIPE,
    CB_KC_B,
};

/* Horizontal combos - left hand */
const uint16_t PROGMEM copy_combo[]  = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_V, COMBO_END};

/* Horizontal combos - right hand */
const uint16_t PROGMEM lpar_combo[] = {HOME_J, HOME_K, COMBO_END};
const uint16_t PROGMEM rpar_combo[] = {HOME_K, HOME_L, COMBO_END};
const uint16_t PROGMEM lbtk_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM rbtk_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM b_combo[] = {KC_N, KC_M, COMBO_END};

/* Vertical combos - let hand */
const uint16_t PROGMEM at_combo[]    = {KC_W, HOME_S, COMBO_END};
const uint16_t PROGMEM hash_combo[]  = {KC_E, HOME_D, COMBO_END};
const uint16_t PROGMEM dllr_combo[]  = {KC_R, HOME_F, COMBO_END};
const uint16_t PROGMEM prcnt_combo[] = {KC_T, KC_G, COMBO_END};

const uint16_t PROGMEM grave_combo[] = {HOME_S, KC_X, COMBO_END};
const uint16_t PROGMEM bsls_combo[]  = {HOME_D, KC_C, COMBO_END};
const uint16_t PROGMEM eql_combo[]   = {HOME_F, KC_V, COMBO_END};
const uint16_t PROGMEM tild_combo[]  = {KC_G, KC_B, COMBO_END};

/* Vertical right hand */
const uint16_t PROGMEM circ_combo[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM plus_combo[] = {KC_U, HOME_J, COMBO_END};
const uint16_t PROGMEM astr_combo[] = {KC_I, HOME_K, COMBO_END};
const uint16_t PROGMEM ampr_combo[] = {KC_O, HOME_L, COMBO_END};

const uint16_t PROGMEM unds_combo[] = {KC_H, KC_N, COMBO_END};
const uint16_t PROGMEM mins_combo[] = {HOME_J, KC_M, COMBO_END};
const uint16_t PROGMEM slsh_combo[] = {HOME_K, KC_COMM, COMBO_END};
const uint16_t PROGMEM pipe_combo[] = {HOME_L, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    [CB_COPY] = COMBO(copy_combo, C(KC_INS)),
    [CB_PASTE] = COMBO(paste_combo, S(KC_INS)),
    [CB_LPAR] = COMBO(lpar_combo, KC_LPRN),
    [CB_RPAR] = COMBO(rpar_combo, KC_RPRN),
    [CB_LBTK] = COMBO(lbtk_combo, KC_LBRC),
    [CB_RBTK] = COMBO(rbtk_combo, KC_RBRC),
    [CB_AT] = COMBO(at_combo, KC_AT),
    [CB_HASH] = COMBO(hash_combo, KC_HASH),
    [CB_DLLR] = COMBO(dllr_combo, KC_DLR),
    [CB_PRCNT] = COMBO(prcnt_combo, KC_PERC),
    [CB_GRAVE] = COMBO(grave_combo, KC_GRAVE),
    [CB_BSLS] = COMBO(bsls_combo, KC_BSLS),
    [CB_EQL] = COMBO(eql_combo, KC_EQL),
    [CB_TILD] = COMBO(tild_combo, KC_TILD),
    [CB_CIRC] = COMBO(circ_combo, KC_CIRC),
    [CB_PLUS] = COMBO(plus_combo, KC_PLUS),
    [CB_ASTR] = COMBO(astr_combo, KC_ASTR),
    [CB_AMPR] = COMBO(ampr_combo, KC_AMPR),
    [CB_UNDS] COMBO(unds_combo, KC_UNDS),
    [CB_MINS] COMBO(mins_combo, KC_MINS),
    [CB_SLSH] COMBO(slsh_combo, KC_SLSH),
    [CB_PIPE] COMBO(pipe_combo, KC_PIPE),
    [CB_KC_B] COMBO(b_combo, KC_B),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Disable combo `SOME_COMBO` on layer `_LAYER_A` */
    switch (combo_index) {
        case CB_LPAR: case CB_RPAR: case CB_RBTK: case CB_LBTK:
            if (layer_state_is(LAYER_NAV)) {
                return false;
            }
    }

    return true;
};

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    // If you want all combos to be tap-only, just uncomment the next line
    // return true

    // If you want *all* combos, that have Mod-Tap/Layer-Tap/Momentary keys in its chord, to be tap-only, this is for you:
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;

}
