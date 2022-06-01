/* Copyright 2022 Brian Low
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

enum sofle_layers {
    _QWERTZ,
    _NEOLV1,
    _NEOLV2,
    _NEOLV3,
};

enum custom_keycodes { KC_LOWER = SAFE_RANGE, KC_RAISE, KC_ADJUST, KC_PRVWD, KC_NXTWD, KC_LSTRT, KC_LEND, KC_DLINE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_BSLS, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Z, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Y, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, KC_LCTL, KC_RALT, KC_CAPS, KC_SPC, KC_ENT, KC_CAPS, KC_RALT, KC_RCTL, KC_RGUI)};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_CAPS:
            if (record->event.pressed) {
                layer_on(_NEOLV1);
                update_tri_layer(_NEOLV1, _NEOLV2, _NEOLV3);
            } else {
                layer_off(_NEOLV1);
                update_tri_layer(_NEOLV1, _NEOLV2, _NEOLV3);
            }
            return false;
        case KC_RALT:
            if (record->event.pressed) {
                layer_on(_NEOLV2);
                update_tri_layer(_NEOLV1, _NEOLV2, _NEOLV3);
            } else {
                layer_off(_NEOLV2);
                update_tri_layer(_NEOLV1, _NEOLV2, _NEOLV3);
            }
            return false;
        default:
            return true;
    }
}

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0, 254, 254, 102, 102, 230, 230, 24, 24, 0, 0,   248, 248, 102, 102, 102, 102, 248, 248, 0, 0, 254, 254, 102, 102, 102, 102, 24,  24, 0, 0, 0, 0, 7,   7,   0,   0,   1,   1,   6,   6, 0, 0,  7,   7,   0,   0,   0,   0,   7,   7,   0,  0,  7,  7,  0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,  0, 0, 0, 0,   240, 240, 255, 255, 240, 240, 0,   0, 0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0, 0, 0, 0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,   0,   0,   0,  0,  0,  0,  0,   0, 0, 0, 252, 252, 192, 192, 48,  48,  12,  12, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0,   0,  192, 192, 48, 48, 252, 252, 0,  0,   0,  0,   15,  15,  192, 192, 195, 195, 12,  12,  0,   0,
        0,  0, 255, 255, 255, 255, 255, 255, 0,  0,  0, 0,   3,   3,   195, 195, 207, 207, 3,   3,   0, 0, 51,  51,  204, 204, 204, 204, 51,  51, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 0,   0, 0, 0,  195, 195, 240, 240, 204, 204, 195, 195, 0,  0,  48, 48, 204, 204, 204, 204, 12, 12, 0,  0,  0,  0,  255, 255, 255, 255, 255, 255, 0,  0, 0, 0, 240, 240, 12,  12,  12,  12,  240, 240, 0, 0,  12, 12,  12, 12, 12, 12, 3,  3,   0,  0, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 3, 3,   12,  12,  12,  12,  3,   3, 0, 0, 0,   0,   0,   0,  0,  0,  0,  0,   0, 0, 0, 0,   255, 255, 255, 255, 255, 255, 0,  0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0, 0, 0,   0,  0,   0,   0,  0,  0,   0,   0,  48,  48, 252, 252, 207, 207, 128, 128, 207, 207, 252, 252, 48,
        48, 0, 0,   0,   0,   0,   0,   0,   0,  0,  0, 192, 192, 0,   0,   0,   0,   0,   0,   0,   0, 0, 0,   243, 243, 207, 207, 243, 243, 0,  0, 0, 0, 0, 0,   0,   0,   0,   0,   192, 192, 0, 0, 15, 15,  63,  63,  252, 252, 48,  48,  60,  60, 15, 15, 15, 15,  207, 207, 15,  15, 15, 15, 60, 60, 48, 48,  252, 252, 63,  63,  15,  15, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,   0, 15, 9,  251, 67, 67, 67, 67, 67, 249, 15, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0, 0, 0, 132, 255, 196, 68, 68, 68, 68, 255, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,  0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0, 0, 120, 72, 255, 48,  60, 60, 48,  240, 79, 120, 0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void write_int_ln(const char* prefix, uint8_t value) {
    oled_write_P(prefix, false);
    oled_write(get_u8_str(value, ' '), false);
}

static void print_status_narrow(void) {
    oled_write_ln_P(PSTR("SofleChoc _____\nRAPSN\n\n\n\n\n\n\n\n"), false);

    // Print current layer
    switch (get_highest_layer(layer_state)) {
        case _QWERTZ:
            oled_write_P(PSTR("Main "), false);
            break;
        case _NEOLV1:
            oled_write_P(PSTR("LVL 1"), false);
            break;
        case _NEOLV2:
            oled_write_P(PSTR("LVL 2"), false);
            break;
        default:
            oled_write_P(PSTR("???  "), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }

    return false;
}

#endif
