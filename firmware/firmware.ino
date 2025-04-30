#include <Keyboard.h>

// Define whether the special key is present
#define HAS_SPECIAL_KEY
#define SPECIAL_KEY_MODE 0 // 0 = NO, 1 = NC
// Define whether mode switch functionality is present
// #define HAS_MODE_SWITCH

// Variable to keep track of the current macro mode
int macro_mode = 0;

#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10

#define PIN_14 14
#define PIN_15 15
#define PIN_16 16

// Number of macro keys and their pin mappings without the special key
#define MACRO_KEY_CNT 12
const int MACRO_KEY_PINS[] = {PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7,
                              PIN_8, PIN_9, PIN_10, PIN_16, PIN_14, PIN_15};

// Key mappings for the macro keys in primary mode without the special key
const int MACRO_KEY_MAP[] = {KEY_F13, KEY_F14, KEY_F15, KEY_F16,
                             KEY_F17, KEY_F18, KEY_F19, KEY_F20,
                             KEY_F21, KEY_F22, KEY_F23, KEY_F24};

// Key mappings for the macro keys in secondary mode without the special key
const int MACRO_KEY_MAP_SECONDARY[] = {KEY_F1, KEY_F2,  KEY_F3,  KEY_F4,
                                       KEY_F5, KEY_F6,  KEY_F7,  KEY_F8,
                                       KEY_F9, KEY_F10, KEY_F11, KEY_F12};

// Array to store the previous state of each key
bool prev_key_states[MACRO_KEY_CNT];

#ifdef HAS_SPECIAL_KEY

// Pin and key mapping for the special key
#define SPECIAL_KEY_PIN PIN_A0
#define SPECIAL_KEY_MAP KEY_F12

bool prev_special_key_state;

#endif


#ifdef HAS_MODE_SWITCH

// Pin for the mode switch
#define MODE_SWITCH_PIN PF6

// Variable to track if the mode switch is currently pressed
bool mode_switch_is_pressed = false;

#endif


// Setup function to initialize pins and start keyboard communication
void setup() {

  // Set each macro key pin as an input with a pull-up resistor
  for (int pin = 0; pin < MACRO_KEY_CNT; pin++) {
    pinMode(MACRO_KEY_PINS[pin], INPUT_PULLUP);
    prev_key_states[pin] = digitalRead(MACRO_KEY_PINS[pin]); // Initialize previous states
  }

#ifdef HAS_SPECIAL_KEY

  // Set the special key pin as an input with a pull-up resistor
  pinMode(SPECIAL_KEY_PIN, INPUT_PULLUP);
  prev_special_key_state = digitalRead(SPECIAL_KEY_PIN);

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
      macro_mode == 0 ? MACRO_KEY_MAP : MACRO_KEY_MAP_SECONDARY;

  // Check each macro key for a press or release
  for (int pin = 0; pin < MACRO_KEY_CNT; pin++) {
    bool current_state = digitalRead(MACRO_KEY_PINS[pin]);

    pressKey(!prev_key_states[pin], !current_state, key_map[pin]);

    // Update the previous state of the key
    prev_key_states[pin] = current_state;
  }

#ifdef HAS_SPECIAL_KEY

    bool current_state = digitalRead(SPECIAL_KEY_PIN);

    pressKey(prev_special_key_state ^ SPECIAL_KEY_MODE, current_state ^ SPECIAL_KEY_MODE, SPECIAL_KEY_MAP);

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
