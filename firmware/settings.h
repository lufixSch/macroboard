#ifndef SETTINGS_H
#define SETTINGS_H

#include <Keyboard.h>

// Define whether the special key is present
#define HAS_SPECIAL_KEY
#define SPECIAL_KEY_MODE 0 // 0 = NO, 1 = NC

// Define whether mode switch functionality is present
// #define HAS_MODE_SWITCH

// Keyboard Configuration
#define MACRO_KEY_CNT 12 // Number of macro keys without the special key
const int MACRO_KEY_PINS[] = {PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7,
                              PIN_8, PIN_9, PIN_10, PIN_16, PIN_14, PIN_15};

#define SPECIAL_KEY_PIN PIN_A0

// Key Mappings
const int MACRO_KEY_MAP[] = {KEY_F13, KEY_F14, KEY_F15, KEY_F16,
                             KEY_F17, KEY_F18, KEY_F19, KEY_F20,
                             KEY_F21, KEY_F22, KEY_F23, KEY_F24};


#define SPECIAL_KEY KEY_F12

// Alt Key Mappings (Only used if mode switching is enabled)
const int MACRO_KEY_MAP_ALT[] = {KEY_F1, KEY_F2,  KEY_F3,  KEY_F4,
                                 KEY_F5, KEY_F6,  KEY_F7,  KEY_F8,
                                 KEY_F9, KEY_F10, KEY_F11, KEY_F12};

#define SPECIAL_KEY_ALT KEY_F12

#endif
