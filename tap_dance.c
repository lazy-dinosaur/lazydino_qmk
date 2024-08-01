//tapdance
enum{
    TD_L,
    TD_D,
    TD_U,
    TD_R,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    if (!(
            process_record_num_word(keycode, record) &&
            true)) {
            return false;
        }


    mod_state = get_mods();
    switch (keycode) {
        case TD(TD_L): case TD(TD_D): case TD(TD_U): case TD(TD_R):// list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TD_L] = ACTION_TAP_DANCE_TAP_HOLD(KC_LEFT, KC_HOME),
    [TD_D] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOWN, TO_END),
    [TD_U] = ACTION_TAP_DANCE_TAP_HOLD(KC_UP, TO_STRT),
    [TD_R] = ACTION_TAP_DANCE_TAP_HOLD(KC_RIGHT, KC_END),
};
