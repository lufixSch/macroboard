#include <Keyboard.h>

#include "gpio.h"
#include "settings.h"

// Variable to keep track of the current macro mode
int macro_mode = 0;

// Array to store the previous state of each key
bool prev_key_states[MACRO_KEY_CNT];

#ifdef HAS_SPECIAL_KEY

bool prev_special_key_state;

int special_key_polarity = 0;
int special_key_polarity_mode = 0;
int special_key_mode = 0;

#endif


#ifdef HAS_MODE_SWITCH

// Variable to track if the mode switch is currently pressed
bool mode_switch_is_pressed = false;

#endif


// Setup function to initialize pins and start keyboard communication
void setup() {
  delay(100); // Ensure stable states

  // Set each macro key pin as an input with a pull-up resistor
  for (int pin = 0; pin < MACRO_KEY_CNT; pin++) {
    pinMode(MACRO_KEY_PINS[pin], INPUT_PULLUP);
    prev_key_states[pin] = digitalRead(MACRO_KEY_PINS[pin]); // Initialize previous states
  }

#ifdef HAS_SPECIAL_KEY

  // Set the special key pin as an input with a pull-up resistor
  pinMode(SPECIAL_KEY_PIN, INPUT_PULLUP);
  prev_special_key_state = digitalRead(SPECIAL_KEY_PIN);

  special_key_polarity = SPECIAL_KEY_POLARITY >= 0 ? SPECIAL_KEY_POLARITY : prev_special_key_state;

  pinMode(SPECIAL_KEY_POLARITY_SWITCH_PIN, INPUT_PULLUP);
  special_key_polarity_mode = !digitalRead(SPECIAL_KEY_POLARITY_SWITCH_PIN);

  pinMode(SPECIAL_KEY_MODE_SWITCH_PIN, INPUT_PULLUP);
  special_key_mode = !digitalRead(SPECIAL_KEY_MODE_SWITCH_PIN);
#endif


#ifdef HAS_MODE_SWITCH

  // Set the mode switch pin as an input with a pull-up resistor
  pinMode(MODE_SWITCH_PIN, INPUT_PULLUP);

#endif

  // Start keyboard communication
  Keyboard.begin();
}

// Detect rising edge and press corresponding key
void pressKey(bool prev_state, bool curr_state, int key) {
  if (curr_state && !prev_state) {
    // Key was pressed
    Keyboard.press(key);
    // Serial.print("Press: ");
    // Serial.println(key);
  } else if (!curr_state && prev_state) {
    // Key was released
    Keyboard.release(key);
    // Serial.print("Release: ");
    // Serial.println(key);
  }
}



// Main loop to handle key presses and macro modes
void loop() {
  // Select the appropriate key mapping based on the current macro mode
  const int *key_map =
      macro_mode == 0 ? MACRO_KEY_MAP : MACRO_KEY_MAP_ALT;

  // Check each macro key for a press or release
  for (int pin = 0; pin < MACRO_KEY_CNT; pin++) {
    bool current_state = digitalRead(MACRO_KEY_PINS[pin]);

    pressKey(!prev_key_states[pin], !current_state, key_map[pin]);

    // Update the previous state of the key
    prev_key_states[pin] = current_state;
  }

#ifdef HAS_SPECIAL_KEY

  special_key_polarity_mode = !digitalRead(SPECIAL_KEY_POLARITY_SWITCH_PIN);
  special_key_mode = !digitalRead(SPECIAL_KEY_MODE_SWITCH_PIN);

  bool current_state = digitalRead(SPECIAL_KEY_PIN);
  bool polarity = special_key_polarity ^ special_key_polarity_mode;

  pressKey(
    prev_special_key_state ^ polarity, 
    current_state ^ polarity, 
    special_key_mode == 0 ? SPECIAL_KEY : SPECIAL_KEY_ALT
  );

  // Update the previous state of the key
  prev_special_key_state = current_state;

#endif

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

  delay(10); // Small delay to debounce the keys
}
