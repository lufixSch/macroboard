#include <Arduino.h>
#include <Keyboard.h>

// Define whether the special key is present
#define HAS_SPECIAL_KEY
// Define wether mode switch functionality is present
#define HAS_MODE_SWITCH

// Variable to keep track of the current macro mode
int macro_mode = 0;

#ifdef HAS_SPECIAL_KEY

// Pin and key mapping for the special key
#define SPECIAL_KEY_PIN PORTF7
#define SPECIAL_KEY_MAP KEY_F12

// Number of macro keys and their pin mappings
#define MACRO_KEY_CNT 13
const int MACRO_KEY_PINS[] = {PORTD1, PORTD0, PORTD4,         PORTC6, PORTD7,
                              PORTE6, PORTB4, PORTB5,         PORTB6, PORTB2,
                              PORTB3, PORTB1, SPECIAL_KEY_PIN};
// Key mappings for the macro keys in primary mode
const int MACRO_KEY_MAP[] = {KEY_F13, KEY_F14, KEY_F15,        KEY_F16, KEY_F17,
                             KEY_F18, KEY_F19, KEY_F20,        KEY_F21, KEY_F22,
                             KEY_F23, KEY_F24, SPECIAL_KEY_MAP};

// Key mappings for the macro keys in secondary mode
const int MACRO_KEY_MAP_SECONDARY[] = {
    KEY_F1, KEY_F2, KEY_F3,  KEY_F4,  KEY_F5,  KEY_F6,         KEY_F7,
    KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, SPECIAL_KEY_MAP};

#else

// Number of macro keys and their pin mappings without the special key
#define MACRO_KEY_CNT 12
const int MACRO_KEY_PINS[] = {PORTD1, PORTD0, PORTD4, PORTC6, PORTD7, PORTE6,
                              PORTB4, PORTB5, PORTB6, PORTB2, PORTB3, PORTB1};
// Key mappings for the macro keys in primary mode without the special key
const int MACRO_KEY_MAP[] = {KEY_F13, KEY_F14, KEY_F15, KEY_F16,
                             KEY_F17, KEY_F18, KEY_F19, KEY_F20,
                             KEY_F21, KEY_F22, KEY_F23, KEY_F24};

// Key mappings for the macro keys in secondary mode without the special key
const int MACRO_KEY_MAP_SECONDARY[] = {KEY_F1, KEY_F2,  KEY_F3,  KEY_F4,
                                       KEY_F5, KEY_F6,  KEY_F7,  KEY_F8,
                                       KEY_F9, KEY_F10, KEY_F11, KEY_F12};

#endif

#ifdef HAS_MODE_SWITCH

// Pin for the mode switch
#define MODE_SWITCH_PIN PORTF6

// Variable to track if the mode switch is currently pressed
bool mode_switch_is_pressed = false;

#endif

// Setup function to initialize pins and start keyboard communication
void setup() {
  // Set each macro key pin as an input with a pull-up resistor
  for (int pin = 0; pin < MACRO_KEY_CNT; pin++) {
    pinMode(MACRO_KEY_PINS[pin], INPUT_PULLUP);
  }

#ifdef HAS_MODE_SWITCH

  // Set the mode switch pin as an input with a pull-up resistor
  pinMode(MODE_SWITCH_PIN, INPUT_PULLUP);

#endif

  // Start keyboard communication
  Keyboard.begin();
}

// Main loop to handle key presses and macro modes
void loop() {
  // Select the appropriate key mapping based on the current macro mode
  const int *key_map =
      macro_mode == 0 ? MACRO_KEY_MAP : MACRO_KEY_MAP_SECONDARY;

  // Check each macro key for a press or release
  for (int pin = 0; pin < MACRO_KEY_CNT; pin++) {
    if (!digitalRead(MACRO_KEY_PINS[pin])) {
      // Release the key if it is not pressed
      Keyboard.release(key_map[pin]);
    } else {
      // Press the key if it is pressed
      Keyboard.press(key_map[pin]);
    }
  }

#ifdef HAS_MODE_SWITCH

  // Check if the mode switch is pressed
  if (!digitalRead(MODE_SWITCH_PIN)) {
    if (mode_switch_is_pressed == false) {
      // Toggle the macro mode if the switch is not already considered pressed
      macro_mode = !macro_mode;
      // Mark the mode switch as pressed
      mode_switch_is_pressed = true;
    }
  } else {
    // Reset the mode switch press state when it is released
    mode_switch_is_pressed = false;
  }

#endif
}

// Main function to start the setup and loop functions
int main() {
  setup();

  while (true) {
    loop();
  }
}
