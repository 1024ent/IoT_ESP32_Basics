/**
 * @file example_4.cpp
 * @brief Digital Input Example: 
 *        This program demonstrates how to read a digital input from a slide switch and display the state 
 *        on the Serial Monitor. Additionally, it controls two LEDs based on the switch's position.
 *        - LED1 turns ON when the slide switch is toggled ON.
 *        - LED2 turns ON when the slide switch is toggled OFF.
 * 
 * @details
 *        - The program continuously reads the state of the switch and updates the LEDs accordingly.
 *        - Serial communication is used to log the switch state.
 *        - Constants are defined for delays and pin numbers for better readability and maintainability.
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 29/12/2024
 **/
#include <Arduino.h>

// Function declarations
void digital_input_example();  // Handles digital input for LED control

// Define constants for delays
#define short_delay pdMS_TO_TICKS(1000)
#define mid_delay pdMS_TO_TICKS(5000)
#define long_delay pdMS_TO_TICKS(10000)

// Define pin numbers for LEDs, switch, and LDR
constexpr int led1_pin = 13;  // LED 1 pin
constexpr int led2_pin = 12;  // LED 2 pin
constexpr int switch_pin = 33; // Switch input pin

// Define variables
int switch_state = 0;  // Variable to store the state of the switch

void setup() {
    // Set pin modes for LEDs, switch, and LDR
    pinMode(led1_pin, OUTPUT);   // Set LED 1 as output
    pinMode(led2_pin, OUTPUT);   // Set LED 2 as output
    pinMode(switch_pin, INPUT);  // Set switch pin as input

    // Start serial communication
    Serial.begin(115200);
}

void loop() {
    // Continuously check for user input
    digital_input_example(); 
}

// Function to handle digital input and control LEDs based on the switch state
void digital_input_example() {
    // Read the state of the switch pin
    switch_state = digitalRead(switch_pin);

    // If the switch is pressed (HIGH), turn on LED 1 and off LED 2
    if (switch_state == HIGH) {
        digitalWrite(led1_pin, HIGH);
        digitalWrite(led2_pin, LOW);
    } else {
        // If the switch is not pressed (LOW), turn off LED 1 and turn on LED 2
        digitalWrite(led1_pin, LOW);
        digitalWrite(led2_pin, HIGH);
    }
}
