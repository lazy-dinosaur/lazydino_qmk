#pragma once
#include QMK_KEYBOARD_H

// morph_settings
const key_override_t comma_inner_morph = ko_make_basic(MOD_MASK_CS, KC_COMM, KC_LABK);
const key_override_t dot_inner_morph   = ko_make_basic(MOD_MASK_CS, KC_DOT, KC_RABK);

const key_override_t comma_morph = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t dot_morph   = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);

const key_override_t qexcl = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);

const key_override_t lpar_lt = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LABK);
const key_override_t rpar_rt = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RABK);
const key_override_t bs_del  = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &comma_inner_morph,
    &dot_inner_morph,
    &comma_morph,
    &dot_morph,
    &qexcl,
    &lpar_lt,
    &rpar_rt,
    NULL // Null terminate the array of overrides!
};
