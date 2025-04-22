/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#include "rgb_matrix.h" // Include RGB Matrix header

// Define MEH and HYPER modifiers
#define MOD_MEH (MOD_LCTL | MOD_LSFT | MOD_LALT)

// Define complex macros
#define MAC_SS_AREA G(S(KC_4))       // Mac: Screenshot Area (Cmd+Shift+4)
#define MAC_SS_TOOL G(S(KC_5))       // Mac: Screenshot/Record Tool (Cmd+Shift+5)
#define MAC_LOCK C(G(KC_Q))          // Mac: Lock Screen (Ctrl+Cmd+Q)
#define MAC_FORCE_QUIT A(G(KC_ESC))  // Mac: Force Quit (Opt+Cmd+Esc)
#define MAC_APP_EXP C(KC_DOWN)       // Mac: App Exposé (Ctrl+Down)

#define WIN_SNIP LGUI(LSFT(KC_S))    // Win: Snipping Tool (Win+Shift+S)
#define NEW_VD LGUI(LCTL(KC_D))      // Win: New Virtual Desktop (Win+Ctrl+D)
#define CLS_VD LGUI(LCTL(KC_F4))     // Win: Close Virtual Desktop (Win+Ctrl+F4)
#define PREV_VD LGUI(LCTL(KC_LEFT))  // Win: Previous Virtual Desktop (Win+Ctrl+Left)
#define NEXT_VD LGUI(LCTL(KC_RGHT))  // Win: Next Virtual Desktop (Win+Ctrl+Right)

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

// Define custom keycodes using an enum for Mod-Tap keys
enum custom_keycodes {
    // Mac specific mods
    D_LOPT = SAFE_RANGE,
    F_LCMD,
    J_RCMD,
    K_ROPT,
    // Windows specific mods
    D_LALT,
    F_LGUI,
    J_RGUI,
    K_RALT,
    // Common mods/keys
    A_CTL,
    S_SFT,
    L_SFT,
    SC_CTL,
    E_HYPR,
    R_MEH,
    U_MEH,
    I_HYPR,
    // Custom Macro Keys
    MACRO_1,
    MACRO_2,
    MACRO_3,
    MACRO_4,
    MACRO_5
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_91_ansi(
        KC_MUTE,  KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_INS,   KC_DEL,   KC_MUTE,
        MACRO_1,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        MACRO_2,  KC_TAB,   KC_Q,     KC_W,     E_HYPR,   R_MEH,    KC_T,      KC_Y,     U_MEH,    I_HYPR,   KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        MACRO_3,  KC_CAPS,  A_CTL,    S_SFT,    D_LOPT,   F_LCMD,   KC_G,      KC_H,     J_RCMD,   K_ROPT,   L_SFT,    SC_CTL,   KC_QUOT,              KC_ENT,             KC_HOME,
        MACRO_4,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        MACRO_5,  KC_LCTL,  KC_LOPT,  KC_LCMD,  MO(MAC_FN),         KC_SPC,                        KC_SPC,             KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_91_ansi(
        RM_TOGG,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,  _______,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,   _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_91_ansi(
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_INS,   KC_DEL,   KC_MUTE,
        MACRO_1,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        MACRO_2,  KC_TAB,   KC_Q,     KC_W,     E_HYPR,   R_MEH,    KC_T,      KC_Y,     U_MEH,    I_HYPR,   KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        MACRO_3,  KC_CAPS,  A_CTL,    S_SFT,    D_LALT,   F_LGUI,   KC_G,      KC_H,     J_RGUI,   K_RALT,   L_SFT,    SC_CTL,   KC_QUOT,              KC_ENT,             KC_HOME,
        MACRO_4,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        MACRO_5,  KC_LCTL,  KC_LWIN,  KC_LALT,  MO(WIN_FN),         KC_SPC,                        KC_SPC,             KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_91_ansi(
        RM_TOGG,  _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,   _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  _______,  _______,  _______),
};

// Add process_record_user function to handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t layer = get_highest_layer(layer_state);
        switch (keycode) {
            case MACRO_1:
                if (layer == MAC_BASE) {
                    tap_code16(MAC_SS_AREA); // Use tap_code16 for key combinations
                } else if (layer == WIN_BASE) {
                    tap_code16(WIN_SNIP);    // Use tap_code16 for key combinations
                }
                return false; // Skip default processing
            case MACRO_2:
                if (layer == MAC_BASE) {
                    tap_code16(MAC_SS_TOOL);
                } else if (layer == WIN_BASE) {
                    tap_code16(NEW_VD);
                }
                return false;
            case MACRO_3:
                if (layer == MAC_BASE) {
                    tap_code16(MAC_LOCK);
                } else if (layer == WIN_BASE) {
                    tap_code16(CLS_VD);
                }
                return false;
            case MACRO_4:
                if (layer == MAC_BASE) {
                    tap_code16(MAC_FORCE_QUIT);
                } else if (layer == WIN_BASE) {
                    tap_code16(PREV_VD);
                }
                return false;
            case MACRO_5:
                if (layer == MAC_BASE) {
                    tap_code16(MAC_APP_EXP);
                } else if (layer == WIN_BASE) {
                    tap_code16(NEXT_VD);
                }
                return false;
        }
    }
    return true; // Process other keycodes normally
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};
#endif // ENCODER_MAP_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Define LED indices for F and J keys (based on LAYOUT_91_ansi and info.json led_map)
#define F_LED_INDEX 56
#define J_LED_INDEX 59
// Define LED indices for the 5 macro keys in the first column
#define MACRO_KEY_1_LED 17
#define MACRO_KEY_2_LED 34
#define MACRO_KEY_3_LED 51
#define MACRO_KEY_4_LED 68
#define MACRO_KEY_5_LED 85

// Define colors (Using HSV format for easier color definition)
#define LIGHT_BLUE 170, 255, 255 // HSV(Hue, Sat, Val)
#define DARK_GREEN 85, 255, 128 // HSV(Hue, Sat, Val)
#define RED 0, 255, 255         // HSV(Hue, Sat, Val)

// Change return type to bool
bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case MAC_BASE:
            // Set all keys to light blue using the defined HSV values
            rgb_matrix_set_color_all(LIGHT_BLUE);
            // Set F and J keys to red using the defined HSV values
            rgb_matrix_set_color(F_LED_INDEX, RED);
            rgb_matrix_set_color(J_LED_INDEX, RED);
            break;
        case WIN_BASE:
            // Set all keys to dark green using the defined HSV values
            rgb_matrix_set_color_all(DARK_GREEN);
            // Set F and J keys to red using the defined HSV values
            rgb_matrix_set_color(F_LED_INDEX, RED);
            rgb_matrix_set_color(J_LED_INDEX, RED);
            break;
        default:
            // Optional: Handle other layers or do nothing to keep the base layer color
            break;
    }

    // Set the 5 macro keys to red regardless of the layer (Mac or Win)
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == MAC_BASE || layer == WIN_BASE) {
        rgb_matrix_set_color(MACRO_KEY_1_LED, RED);
        rgb_matrix_set_color(MACRO_KEY_2_LED, RED);
        rgb_matrix_set_color(MACRO_KEY_3_LED, RED);
        rgb_matrix_set_color(MACRO_KEY_4_LED, RED);
        rgb_matrix_set_color(MACRO_KEY_5_LED, RED);
    }

    // Return false to allow the default QMK indicators to work if needed
    return false;
}
#endif // RGB_MATRIX_ENABLE
