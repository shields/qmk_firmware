#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
    EPRM = SAFE_RANGE,
    VRSN,
    RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer */
    [BASE] = LAYOUT_ergodox(
	// left hand
	KC_ESC,          KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_BRID,
	KC_DEL,          KC_Q,        KC_G,          KC_M,    KC_L,    KC_W,    KC_LOPT,
	LCTL_T(KC_ESC),  KC_D,        KC_S,          KC_T,    KC_N,    KC_R,
	KC_LSPO,         KC_Z,        KC_X,          KC_C,    KC_V,    KC_J,    KC_LCMD,
	KC_GRV,          TG(2),       KC_CAPS,       KC_LEFT, KC_RGHT,
	KC_PAUSE, KC_LCBR,
	KC_HOME,
	KC_BSPC, KC_TAB, KC_END,

	// right hand
	KC_BRIU,      KC_6,    KC_7,    KC_8,    KC_9,              KC_0,           KC_MINS,
	KC_ROPT,      KC_Y,    KC_F,    KC_U,    KC_B,              KC_SCLN,        KC_EQL,
	KC_I,         KC_A,    KC_E,    KC_O,    KC_H,              RCTL_T(KC_QUOT),
	KC_RCMD,      KC_K,    KC_P,    KC_COMM, KC_DOT,            KC_SLSH,        KC_RSPC,
	KC_DOWN,      KC_UP,   KC_LBRC, KC_RBRC, TG(1),
	KC_RCBR, KC_BSLS,
	KC_PGUP,
	KC_PGDN, KC_ENT, KC_SPC
	),
/* Keymap 1: Symbol Layer */
[SYMB] = LAYOUT_ergodox(
    // left hand
    VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
    KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,
    KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
    KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,
    EPRM,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    RGB_MOD, KC_TRNS,
    KC_TRNS,
    RGB_VAD, RGB_VAI, KC_TRNS,
    // right hand
    KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
    KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
    KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
    KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
    RGB_TOG, RGB_SLD,
    KC_TRNS,
    KC_TRNS, RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys */
[MDIA] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                    KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_WBAK
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
    }
  }
  return true;
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off(); // red
  ergodox_right_led_2_off(); // green
  ergodox_right_led_3_off(); // blue

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
  case 0:
      break;
  case 1:
      ergodox_right_led_1_on();
      break;
  case 2:
      ergodox_right_led_2_on();
      break;
  case 3:
      ergodox_right_led_3_on();
      break;
  case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
  case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
  case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
  case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
  default:
      break;
  }

  return state;
};

void eeconfig_init_user(void) {
    set_unicode_input_mode(UC_MAC);
}
