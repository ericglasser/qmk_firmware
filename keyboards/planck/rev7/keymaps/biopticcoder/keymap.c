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
#include <stdint.h>
#include <stdbool.h>

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _FN_KEYS,
    _MEDIA    // New Media and System Controls layer
};

enum planck_keycodes {
    BACKLIT = QK_KB,
    CUT_KEY,
    COPY_KEY,
    PASTE_KEY,
    UNDO_KEY,
    WIN_LEFT,   // Window to left half
    WIN_RIGHT,  // Window to right half
    APP_SWITCH, // App switcher
    MISSION     // Mission Control/Task View
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNC MO(_FN_KEYS)  // One-shot layer toggle for Fn layer
#define MEDIA MO(_MEDIA)  // One-shot layer toggle for Media layer

bool is_mac = false;  // Track if we're connected to a Mac/iOS device

// Custom mod-tap macro that sends both modifier and key when held
#define CUSTOM_MT(key, mod) \
    (QK_MOD_TAP | (((mod) & 0xF) << 8) | ((key) & 0xFF))

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | GESC |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  -   |Undo-Z|Cut-X |Copy-C|Pst-V |   B  |   N  |   M  |   ,  |   .  |   /  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Rep  |WinL  |WinR  |  [   |Enter |    Space    | Bksp |  ]   |AppSw |Mission| Rep |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,   KC_Q,         KC_W,         HYPR_T(KC_E), MEH_T(KC_R),       KC_T,             KC_Y,              MEH_T(KC_U),        HYPR_T(KC_I), KC_O,         KC_P,            KC_BACKSLASH,
    QK_GESC,  LCTL_T(KC_A), LSFT_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),      KC_G,             KC_H,              RGUI_T(KC_J),       LALT_T(KC_K), LSFT_T(KC_L), LCTL_T(KC_SCLN), KC_QUOT,
    KC_MINUS, UNDO_KEY,     CUT_KEY,      COPY_KEY,     PASTE_KEY,         KC_B,             KC_N,              KC_M,               KC_COMM,      KC_DOT,       KC_SLSH,         KC_EQUAL,
    QK_REP,   WIN_LEFT,     WIN_RIGHT,    KC_LBRC,      LT(LOWER, KC_ENT), LT(FUNC, KC_SPC), LT(MEDIA, KC_SPC), LT(RAISE, KC_BSPC), KC_RBRC,      APP_SWITCH,   MISSION,         QK_REP
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |   /  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Lock |             |   .  |   0  |   =  |   +  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______,       _______, _______, KC_7,    KC_8,    KC_9,    KC_SLSH, KC_DEL,
    _______, _______, _______, _______, _______,       _______, _______, KC_4,    KC_5,    KC_6,    KC_ASTR, _______,
    _______, _______, _______, _______, _______,       _______, _______, KC_1,    KC_2,    KC_3,    KC_MINS, _______,
    _______, _______, _______, _______, QK_LAYER_LOCK, _______, _______, KC_DOT,  KC_0,    KC_EQL,  KC_PLUS, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, UG_TOGG, UG_NEXT, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_SPDU, UG_SPDD, KC_DEL ,
    _______, EE_CLR,  MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* lower
 * ,-----------------------------------------------------------------------------------.
 * |      | PgUp | Home |  Up  | End  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | PgDn | Left | Down |Right |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Tab  | Bksp | Del  | Enter|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______, _______, _______, _______, _______, _______,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_TAB,  KC_BSPC, KC_DEL,  KC_ENT,  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Function Key Layer
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN_KEYS] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Media and System Control Layer
 * ,-----------------------------------------------------------------------------------.
 * |Sleep | Wake |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Prev | Play | Next | Stop |      |      |VolDn |VolUp | Mute |BrightD|BrightU|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] = LAYOUT_planck_grid(
    KC_SLEP, KC_WAKE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_BRID, KC_BRIU,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

};

#ifdef ENCODER_MAP_ENABLE
/* Rotary Encoders
 */
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    /* Qwerty
     *    v- (index) Clockwise / Counter Clockwise                        v- (index) Clockwise / Counter Clockwise
     * ,---------------------------------------------------------------------------------------.
     * | (0) Vol-    / Vol+    |   |   |   |   |   |   |   |   |   |   | (4) Vol-    / Vol+    |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (1) KC_MNXT / KC_MPRV |   |   |   |   |   |   |   |   |   |   | (5) KC_MNXT / KC_MPRV |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (2) KC_WBAK / KC_WFWD |   |   |   |   |   |   |   |   |   |   | (6) KC_SPC  / KC_ENT  |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (3) KC_LEFT / KC_RGHT |   |   |   |   |       |   |   |   |   | (7) KC_DOWN / KC_UP   |
     * `---------------------------------------------------------------------------------------'
     */
    [_QWERTY] = {
        // LEFT SIDE (index 0 to 3)
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_MNXT, KC_MPRV),
        ENCODER_CCW_CW(KC_WBAK, KC_WFWD),
        ENCODER_CCW_CW(KC_LEFT, KC_RGHT),
        // RIGHT SIDE (index 4 to 7)
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_MNXT, KC_MPRV),
        ENCODER_CCW_CW(KC_SPC,  KC_ENT),
        ENCODER_CCW_CW(KC_DOWN, KC_UP)
    },

    /* Adjust (Lower + Raise)
     *    v- (index) Clockwise / Counter Clockwise                        v- (index) Clockwise / Counter Clockwise
     * ,---------------------------------------------------------------------------------------.
     * | (0) _______ / _______ |   |   |   |   |   |   |   |   |   |   | (4) _______ / _______ |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (1) _______ / _______ |   |   |   |   |   |   |   |   |   |   | (5) _______ / _______ |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (2) UG_NEXT / UG_PREV |   |   |   |   |   |   |   |   |   |   | (6) SAT- / SAT+       |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (3) UG_VALD / UG_VALU |   |   |   |   |       |   |   |   |   | (7) HUE- / HUE+       |
     * `---------------------------------------------------------------------------------------'
     */
    [_ADJUST] = {
        // LEFT SIDE (index 0 to 3)
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(UG_NEXT, UG_PREV),
        ENCODER_CCW_CW(UG_VALD, UG_VALU),
        // RIGHT SIDE (index 4 to 7)
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(UG_SATD,  UG_SATU),
        ENCODER_CCW_CW(UG_HUEU,  UG_HUED)
    }
};
#endif
/* clang-format on */

bool play_encoder_melody(uint8_t index, bool clockwise);

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ENCODER_MAP_ENABLE
    if (IS_ENCODEREVENT(record->event) && record->event.pressed) {
        play_encoder_melody(record->event.key.col, record->event.type == ENCODER_CCW_EVENT);
    }
#endif

    uint16_t mod_key = is_mac ? KC_LGUI : KC_LCTL;
    
    switch (keycode) {
        case UNDO_KEY:
            if (record->event.pressed) {
                if (record->tap.count && !record->tap.interrupted) {
                    register_code16(KC_Z);
                } else {
                    register_code(mod_key);
                    register_code(KC_Z);
                }
            } else {
                unregister_code16(KC_Z);
                unregister_code(mod_key);
            }
            return false;
        case CUT_KEY:
            if (record->event.pressed) {
                if (record->tap.count && !record->tap.interrupted) {
                    register_code16(KC_X);
                } else {
                    register_code(mod_key);
                    register_code(KC_X);
                }
            } else {
                unregister_code16(KC_X);
                unregister_code(mod_key);
            }
            return false;
        case COPY_KEY:
            if (record->event.pressed) {
                if (record->tap.count && !record->tap.interrupted) {
                    register_code16(KC_C);
                } else {
                    register_code(mod_key);
                    register_code(KC_C);
                }
            } else {
                unregister_code16(KC_C);
                unregister_code(mod_key);
            }
            return false;
        case PASTE_KEY:
            if (record->event.pressed) {
                if (record->tap.count && !record->tap.interrupted) {
                    register_code16(KC_V);
                } else {
                    register_code(mod_key);
                    register_code(KC_V);
                }
            } else {
                unregister_code16(KC_V);
                unregister_code(mod_key);
            }
            return false;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
        case WIN_LEFT:
            if (record->event.pressed) {
                if (is_mac) {
                    register_code(KC_LCTL);
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_LCTL);
                    register_code(KC_LGUI);
                    register_code(KC_LEFT);
                }
            } else {
                if (is_mac) {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LEFT);
                }
            }
            return false;
        case WIN_RIGHT:
            if (record->event.pressed) {
                if (is_mac) {
                    register_code(KC_LCTL);
                    register_code(KC_RGHT);
                } else {
                    register_code(KC_LCTL);
                    register_code(KC_LGUI);
                    register_code(KC_RGHT);
                }
            } else {
                if (is_mac) {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_RGHT);
                } else {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_RGHT);
                }
            }
            return false;
        case APP_SWITCH:
            if (record->event.pressed) {
                if (is_mac) {
                    register_code(KC_LGUI);
                    register_code(KC_TAB);
                } else {
                    register_code(KC_LALT);
                    register_code(KC_TAB);
                }
            } else {
                if (is_mac) {
                    unregister_code(KC_LGUI);
                    unregister_code(KC_TAB);
                } else {
                    unregister_code(KC_LALT);
                    unregister_code(KC_TAB);
                }
            }
            return false;
        case MISSION:
            if (record->event.pressed) {
                if (is_mac) {
                    register_code(KC_LCTL);
                    register_code(KC_UP);
                } else {
                    register_code(KC_LGUI);
                    register_code(KC_TAB);
                }
            } else {
                if (is_mac) {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_UP);
                } else {
                    unregister_code(KC_LGUI);
                    unregister_code(KC_TAB);
                }
            }
            return false;
    }
    return true;
}

/* clang-format off */
float melody[8][2][2] = {
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
};
/* clang-format on */

#define JUST_MINOR_THIRD 1.2
#define JUST_MAJOR_THIRD 1.25
#define JUST_PERFECT_FOURTH 1.33333333
#define JUST_TRITONE 1.42222222
#define JUST_PERFECT_FIFTH 1.33333333

#define ET12_MINOR_SECOND 1.059463
#define ET12_MAJOR_SECOND 1.122462
#define ET12_MINOR_THIRD 1.189207
#define ET12_MAJOR_THIRD 1.259921
#define ET12_PERFECT_FOURTH 1.33484
#define ET12_TRITONE 1.414214
#define ET12_PERFECT_FIFTH 1.498307

deferred_token tokens[8];

uint32_t reset_note(uint32_t trigger_time, void *note) {
    *(float*)note = 440.0f;
    return 0;
}

bool play_encoder_melody(uint8_t index, bool clockwise) {
    cancel_deferred_exec(tokens[index]);
    if (clockwise) {
        melody[index][1][0] = melody[index][1][0] * ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] / ET12_PERFECT_FIFTH;
        audio_play_melody(&melody[index], 2, false);
    } else {
        melody[index][1][0] = melody[index][1][0] / ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] * ET12_TRITONE;
        audio_play_melody(&melody[index], 2, false);
    }
    tokens[index] = defer_exec(1000, reset_note, &melody[index][1][0]);
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    return play_encoder_melody(index, clockwise);
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
                eeconfig_update_keymap(keymap_config.raw);
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
