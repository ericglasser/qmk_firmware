/* Copyright 2015-2023 Jack Humbert
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
#include "quantum.h"
#include "achordion.h"
#include <stdint.h>
#include <stdbool.h>

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _FUNC,
    _FAST
};

enum tap_dance_codes {
    TD_UNDO,
    TD_CUT,
    TD_COPY,
    TD_PASTE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNC MO(_FUNC) // One-shot layer toggle for Fn layer

bool is_mac = false; // Track if we're connected to a Mac/iOS device

// Custom mod-tap macro that sends both modifier and key when held
#define CUSTOM_MT(key, mod) (QK_MOD_TAP | (((mod) & 0xF) << 8) | ((key) & 0xFF))

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | GESC |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  -   |Undo-Z|Cut-X |Copy-C|Pst-V |   B  |   N  |   M  |   ,  |   .  |   /  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps | Prev | Play | Next |Lower | Space| Fast |Func | Vol- | Vol+ | Mute | Rep  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    QK_GESC,  KC_Q,         KC_W,         HYPR_T(KC_E), MEH_T(KC_R),        KC_T,              KC_Y,              MEH_T(KC_U),        HYPR_T(KC_I), KC_O,         KC_P,            KC_BACKSLASH,
    KC_TAB,   LCTL_T(KC_A), LSFT_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),       KC_G,              KC_H,              RGUI_T(KC_J),       LALT_T(KC_K), LSFT_T(KC_L), LCTL_T(KC_SCLN), KC_QUOT,
    KC_MINUS, TD(TD_UNDO),  TD(TD_CUT),   TD(TD_COPY),  TD(TD_PASTE),       KC_B,              KC_N,              KC_M,               KC_COMM,      KC_DOT,       KC_SLSH,         KC_EQUAL,
    KC_CAPS,  KC_MPRV,      KC_MPLY,      KC_MNXT,      LT(_LOWER, KC_ENT), LT(_FAST, KC_SPC), LT(_FAST, KC_SPC), LT(_FUNC, KC_BSPC), KC_VOLD,      KC_VOLU,      KC_MUTE,         QK_REP
),

/* Raise (Num/Sym)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |   0  |   0  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_0,    KC_DOT,  _______, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|CapsWd|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, UG_TOGG, UG_NEXT, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_SPDU, UG_SPDD, CW_TOGG ,
    _______, EE_CLR,  MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower (Nav/Mouse)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | PgUp | Home |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | PgDn | End  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_END,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Function/Media Layer (Sequential on Left Hand)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  F1  |  F2  |  F3  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  F4  |  F5  |  F6  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  F10 |  F11 |  F12 |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_planck_grid(
    _______, _______, KC_F1,   KC_F2,   KC_F3,   _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_F7,   KC_F8,   KC_F9,   _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______
),

/* Fast Number/Symbol Layer
 * ,-----------------------------------------------------------------------------------.
 * |   -  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   [  |      |      |      |      |   \  |   `  |      |      |      |      |   ]  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   _  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   +  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FAST] = LAYOUT_planck_grid(
    KC_MINUS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0 , KC_EQL,
    KC_LBRC, _______, _______, _______, _______, KC_BSLS, KC_GRV, _______, _______, _______, _______, KC_RCBR,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


};

/* clang-format on */

enum combos {
  QW_ESC,
  OP_BSPC,
  ENT_BSPC_COMBO
};

const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM ent_bspc_combo[] = {LT(_LOWER, KC_ENT), LT(_FUNC, KC_BSPC), COMBO_END};

combo_t key_combos[] = {
  [QW_ESC] = COMBO(qw_combo, KC_ESC),
  [OP_BSPC] = COMBO(op_combo, KC_BSPC),
  [ENT_BSPC_COMBO] = COMBO(ent_bspc_combo, OSL(_FUNC)),
};

// Tap Dance Logic
typedef struct {
    bool is_press_action;
    int state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, //send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7,
    MULTI_TAP = 8
};

int cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else {
        // For any other number of taps, if not held, treat as multi-tap
        if (!state->pressed) return MULTI_TAP;
        else return SINGLE_HOLD; // Treat hold as hold regardless of count? Or maybe just ignore?
        // Let's stick to: Hold = Shortcut, Tap(s) = Letter(s)
    }
}

static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_Z); break;
        case SINGLE_HOLD: register_code(KC_LCTL); register_code(KC_Z); break;
        case MULTI_TAP:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_Z);
            }
            break;
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_Z); break;
        case SINGLE_HOLD: unregister_code(KC_Z); unregister_code(KC_LCTL); break;
        case MULTI_TAP: break; // tap_code handles register/unregister
    }
    xtap_state.state = 0;
}

void c_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_X); break;
        case SINGLE_HOLD: register_code(KC_LCTL); register_code(KC_X); break;
        case MULTI_TAP:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_X);
            }
            break;
    }
}

void c_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_X); break;
        case SINGLE_HOLD: unregister_code(KC_X); unregister_code(KC_LCTL); break;
        case MULTI_TAP: break;
    }
    xtap_state.state = 0;
}

void v_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_C); break;
        case SINGLE_HOLD: register_code(KC_LCTL); register_code(KC_C); break;
        case MULTI_TAP:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_C);
            }
            break;
    }
}

void v_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_C); break;
        case SINGLE_HOLD: unregister_code(KC_C); unregister_code(KC_LCTL); break;
        case MULTI_TAP: break;
    }
    xtap_state.state = 0;
}

void b_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_V); break;
        case SINGLE_HOLD: register_code(KC_LCTL); register_code(KC_V); break;
        case MULTI_TAP:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_V);
            }
            break;
    }
}

void b_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_V); break;
        case SINGLE_HOLD: unregister_code(KC_V); unregister_code(KC_LCTL); break;
        case MULTI_TAP: break;
    }
    xtap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [TD_CUT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, c_finished, c_reset),
    [TD_COPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, v_finished, v_reset),
    [TD_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, b_finished, b_reset),
};

void matrix_scan_user(void) {
  achordion_task();
}



bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
  return achordion_opposite_hands(tap_hold_record, other_record);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    switch (get_highest_layer(state)) {
        case _LOWER:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(85, 255, 255); // Green
            break;
        case _RAISE:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(170, 255, 255); // Blue
            break;
        case _ADJUST:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(0, 255, 255); // Red
            break;
        case _FAST:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(30, 255, 255); // Gold
            break;
        case _FUNC:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(191, 255, 255); // Purple
            break;
        default:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(0, 0, 0); // Off (Black)
            break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                // Toggle between Mac and other OS modes
                is_mac = !is_mac;
                if (is_mac) {
                    // Swap Ctrl and GUI for Mac
                    keymap_config.swap_lctl_lgui = true;
                    keymap_config.swap_rctl_rgui = true;
                } else {
                    // Normal Ctrl/GUI positions for other OS
                    keymap_config.swap_lctl_lgui = false;
                    keymap_config.swap_rctl_rgui = false;
                }
                eeconfig_update_keymap(&keymap_config);
            }
            break;
    }
    return true;
}

// Add this to detect OS changes via bootmagic or via command
void keyboard_post_init_user(void) {
#ifdef BOOTMAGIC_ENABLE
    // Check if we're connected to a Mac/iOS device
    is_mac = keymap_config.swap_lctl_lgui;
#endif
}
