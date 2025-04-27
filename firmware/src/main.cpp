#include <Arduino.h>
#include <Keyboard.h>

#define HAS_SPECIAL_KEY
// #define HAS_MODE_SWITCH

int macro_mode = 0;

#ifdef HAS_SPECIAL_KEY

#define SPECIAL_KEY_PIN PORTF7
#define SPECIAL_KEY_MAP KEY_F12

#define MACRO_KEY_CNT 13
const int MACRO_KEY_PINS[] = {PORTD1, PORTD0, PORTD4,         PORTC6, PORTD7,
                              PORTE6, PORTB4, PORTB5,         PORTB6, PORTB2,
                              PORTB3, PORTB1, SPECIAL_KEY_PIN};
const int MACRO_KEY_MAP[]{KEY_F13, KEY_F14, KEY_F15,        KEY_F16, KEY_F17,
                          KEY_F18, KEY_F19, KEY_F20,        KEY_F21, KEY_F22,
                          KEY_F23, KEY_F24, SPECIAL_KEY_MAP};

const int MACRO_KEY_MAP_SECONDARY[]{
    KEY_F1, KEY_F2, KEY_F3,  KEY_F4,  KEY_F5,  KEY_F6,         KEY_F7,
    KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, SPECIAL_KEY_MAP};

#else

#define MACRO_KEY_CNT 12
const int MACRO_KEY_PINS[] = {PORTD1, PORTD0, PORTD4, PORTC6, PORTD7, PORTE6,
                              PORTB4, PORTB5, PORTB6, PORTB2, PORTB3, PORTB1};
const int MACRO_KEY_MAP[]{KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18,
                          KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24};

const int MACRO_KEY_MAP_SECONDARY[]{KEY_F1, KEY_F2,  KEY_F3,  KEY_F4,
                                    KEY_F5, KEY_F6,  KEY_F7,  KEY_F8,
                                    KEY_F9, KEY_F10, KEY_F11, KEY_F12};

#endif

#ifdef HAS_MODE_SWITCH

#define MODE_SWITCH_PIN PORTF6

bool mode_switch_is_pressed = false;

#endif

void setup() {
  for (int pin = 0; pin < MACRO_KEY_CNT; pin++) {
    pinMode(MACRO_KEY_PINS[pin], INPUT_PULLUP);
  }

#ifdef HAS_MODE_SWITCH

  pinMode(MODE_SWITCH_PIN, INPUT_PULLUP);

#endif

  Keyboard.begin();
}

void loop() {
  const int *key_map =
      macro_mode == 0 ? MACRO_KEY_MAP : MACRO_KEY_MAP_SECONDARY;

  for (int pin = 0; pin < MACRO_KEY_CNT; pin++) {

    if (!digitalRead(MACRO_KEY_PINS[pin])) {
      Keyboard.release(key_map[pin]);
      continue;
    }

    Keyboard.press(key_map[pin]);
  }

#ifdef HAS_MODE_SWITCH

  if (!digitalRead(MODE_SWITCH_PIN)) {
    if (mode_switch_is_pressed == false) {
        macro_mode = !macro_mode;
    }
  } else {
    mode_switch_is_pressed = false;
  }

#endif
}

int main() {
  setup();

  while (true) {
    loop();
  }
}
