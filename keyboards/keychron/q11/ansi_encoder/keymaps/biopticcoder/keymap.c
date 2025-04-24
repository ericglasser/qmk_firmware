#include QMK_KEYBOARD_H
#include "timer.h"  // For timing tap vs hold

// Define Mod-Tap keys for homerow mods
#define A_CTL LCTL_T(KC_A)
#define S_SFT LSFT_T(KC_S)
#define D_ALT LALT_T(KC_D)
#define F_GUI LGUI_T(KC_F)

#define J_GUI RGUI_T(KC_J)
#define K_ALT RALT_T(KC_K)
#define L_SFT RSFT_T(KC_L)
#define SCLN_CTL RCTL_T(KC_SCLN)

// Define Hyper and Meh keys
#define E_HYPER HYPR_T(KC_E)
#define R_MEH MEH_T(KC_R)
#define U_MEH MEH_T(KC_U)
#define I_HYPER HYPR_T(KC_I)

// One-shot modifier aliases (requires ONE_SHOT_ENABLE in rules.mk)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LGUI OSM(MOD_LGUI)
#define OSM_HYPER OSM(MOD_HYPR)
#define OSM_MEH   OSM(MOD_MEH)

// Custom keycodes for tap-hold mod+key behavior
enum custom_keycodes {
    ZCMD = SAFE_RANGE,
    XCMD,
    CCMD,
    VCMD,
    ZCTL,
    XCTL,
    CCTL,
    VCTL,
    M1,
    M2,
    M3,
    M4,
    M5,
    W1,
    W2,
    W3,
    W4,
    W5
};

// Timers for tap-hold detection
static uint16_t z_timer;
static uint16_t x_timer;
static uint16_t c_timer;
static uint16_t v_timer;

// Define Tap-Hold keys for Z, X, C, V via custom keycodes
#define Z_CMD ZCMD
#define X_CMD XCMD
#define C_CMD CCMD
#define V_CMD VCMD
#define Z_CTL ZCTL
#define X_CTL XCTL
#define C_CTL CCTL
#define V_CTL VCTL

// Space key: tap for space, hold to activate NAV layer
#define SPC_NAV LT(NAV, KC_SPC)

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    NAV,
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_91_ansi(
        KC_MUTE,  KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_INS,   KC_DEL,   KC_MUTE,
        M1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        M2,       KC_TAB,   KC_Q,     KC_W,     E_HYPER,  R_MEH,    KC_T,      KC_Y,     U_MEH,    I_HYPER,  KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        M3,       KC_CAPS,  A_CTL,    S_SFT,    D_ALT,    F_GUI,    KC_G,      KC_H,     J_GUI,    K_ALT,    L_SFT,    SCLN_CTL, KC_QUOT,              KC_ENT,             KC_HOME,
        M4,       KC_LSFT,            Z_CMD,    X_CMD,    C_CMD,    V_CMD,    KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        M5,       KC_LCTL,  KC_LOPT,  KC_LCMD,  MO(MAC_FN),         SPC_NAV,                        KC_SPC,             KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_91_ansi(
        RM_TOGG,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,  _______,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,   _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_91_ansi(
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_INS,   KC_DEL,   KC_MUTE,
        W1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        W2,       KC_TAB,   KC_Q,     KC_W,     E_HYPER,  R_MEH,    KC_T,      KC_Y,     U_MEH,    I_HYPER,  KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        W3,       KC_CAPS,  A_CTL,    S_SFT,    D_ALT,    F_GUI,    KC_G,      KC_H,     J_GUI,    K_ALT,    L_SFT,    SCLN_CTL, KC_QUOT,              KC_ENT,             KC_HOME,
        W4,       KC_LSFT,            Z_CTL,    X_CTL,    C_CTL,    V_CTL,    KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        W5,       KC_LCTL,  KC_LWIN,  KC_LALT,  MO(WIN_FN),         SPC_NAV,                        KC_SPC,             KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_91_ansi(
        RM_TOGG,  _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,   _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,  _______,  _______,            _______,                       _______,            _______,  _______,    _______,  _______,  _______,  _______),

    [NAV] = LAYOUT_91_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______, _______, _______, _______, OSM_HYPER, OSM_MEH, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______, _______, OSM_LCTL, OSM_LSFT, OSM_LALT, OSM_LGUI, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,              _______,            _______,
        _______, _______,            _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______, _______,              _______, _______,
        _______, _______, _______, _______, _______,            _______,                      _______,            _______, _______,  _______, _______, _______, _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [NAV]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif // ENCODER_MAP_ENABLE

// DIP switch handler: switch between MAC_BASE and WIN_BASE
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        uint8_t target_layer = active ? WIN_BASE : MAC_BASE;
        layer_move(target_layer); // Switch current layer
        default_layer_set(1UL << target_layer); // Set default layer for startup
    }
    return true;
}

// Handle tap vs hold for custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ZCMD:
            if (record->event.pressed) {
                z_timer = timer_read();
            } else {
                if (timer_elapsed(z_timer) > TAPPING_TERM) {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_Z);
                    unregister_mods(MOD_BIT(KC_LGUI));
                } else {
                    tap_code(KC_Z);
                }
            }
            return false;
        case XCMD:
            if (record->event.pressed) {
                x_timer = timer_read();
            } else {
                if (timer_elapsed(x_timer) > TAPPING_TERM) {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_X);
                    unregister_mods(MOD_BIT(KC_LGUI));
                } else {
                    tap_code(KC_X);
                }
            }
            return false;
        case CCMD:
            if (record->event.pressed) {
                c_timer = timer_read();
            } else {
                if (timer_elapsed(c_timer) > TAPPING_TERM) {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_C);
                    unregister_mods(MOD_BIT(KC_LGUI));
                } else {
                    tap_code(KC_C);
                }
            }
            return false;
        case VCMD:
            if (record->event.pressed) {
                v_timer = timer_read();
            } else {
                if (timer_elapsed(v_timer) > TAPPING_TERM) {
                    register_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_V);
                    unregister_mods(MOD_BIT(KC_LGUI));
                } else {
                    tap_code(KC_V);
                }
            }
            return false;
        case ZCTL:
            if (record->event.pressed) {
                z_timer = timer_read();
            } else {
                if (timer_elapsed(z_timer) > TAPPING_TERM) {
                    register_mods(MOD_BIT(KC_LCTL));
                    tap_code(KC_Z);
                    unregister_mods(MOD_BIT(KC_LCTL));
                } else {
                    tap_code(KC_Z);
                }
            }
            return false;
        case XCTL:
            if (record->event.pressed) {
                x_timer = timer_read();
            } else {
                if (timer_elapsed(x_timer) > TAPPING_TERM) {
                    register_mods(MOD_BIT(KC_LCTL));
                    tap_code(KC_X);
                    unregister_mods(MOD_BIT(KC_LCTL));
                } else {
                    tap_code(KC_X);
                }
            }
            return false;
        case CCTL:
            if (record->event.pressed) {
                c_timer = timer_read();
            } else {
                if (timer_elapsed(c_timer) > TAPPING_TERM) {
                    register_mods(MOD_BIT(KC_LCTL));
                    tap_code(KC_C);
                    unregister_mods(MOD_BIT(KC_LCTL));
                } else {
                    tap_code(KC_C);
                }
            }
            return false;
        case VCTL:
            if (record->event.pressed) {
                v_timer = timer_read();
            } else {
                if (timer_elapsed(v_timer) > TAPPING_TERM) {
                    register_mods(MOD_BIT(KC_LCTL));
                    tap_code(KC_V);
                    unregister_mods(MOD_BIT(KC_LCTL));
                } else {
                    tap_code(KC_V);
                }
            }
            return false;
        // Mac macros
        case M1:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                tap_code(KC_SPC);
                unregister_mods(MOD_BIT(KC_LALT));
            }
            return false;
        case M2:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL));
                tap_code(KC_SPC);
                unregister_mods(MOD_BIT(KC_LCTL));
            }
            return false;
        case M3:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                tap_code(KC_ESC);
                unregister_mods(MOD_BIT(KC_LALT));
            }
            return false;
        case M4:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_F5);
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case M5:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI));
                tap_code(KC_K);
                unregister_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI));
            }
            return false;
        // Windows powertoys
        case W1:
            if (record->event.pressed) {
                // Win+Shift+S: Snip & Sketch
                register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
                tap_code(KC_S);
                unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            }
            return false;
        case W2:
            if (record->event.pressed) {
                // Win+G: Game Bar
                register_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_G);
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case W3:
            if (record->event.pressed) {
                // Win+; : Emoji panel
                register_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_SCLN);
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case W4:
            if (record->event.pressed) {
                // Win+H: Voice typing / Clipboard history
                register_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_H);
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
        case W5:
            if (record->event.pressed) {
                // Win+Z: FancyZones layout chooser
                register_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_Z);
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            return false;
    }
    return true;
}
