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
 * @date
 **/
#include <Arduino.h>

// Function declarations
void handleDigitalInput(); // Handles digital input for LED control

// Define constants for delays
#define SHORT_DELAY 1000
#define MID_DELAY   5000
#define LONG_DELAY  10000

// Define pin numbers for LEDs and switch
constexpr int LED1_PIN = 13;  // Pin for LED 1
constexpr int LED2_PIN = 12;  // Pin for LED 2
constexpr int SW1_PIN = 35;   // Pin for switch input

// Global variable to store the switch state
int switchState = 0;

void setup() {
    // Configure pin modes
    pinMode(LED1_PIN, OUTPUT);  // Set LED 1 pin as output
    pinMode(LED2_PIN, OUTPUT);  // Set LED 2 pin as output
    pinMode(SW1_PIN, INPUT);    // Set switch pin as input

    // Initialize serial communication
    Serial.begin(115200);
    delay(SHORT_DELAY); // Allow time for setup stabilization
}

void loop() {
    // Continuously check and handle digital input
    handleDigitalInput();
}

// Function to control LEDs based on the switch state
void handleDigitalInput() {
    // Read the state of the switch
    switchState = digitalRead(SW1_PIN);

    if (switchState == HIGH) {
        // If the switch is pressed, turn on LED 1 and turn off LED 2
        Serial.println("Switch is toggled ON!");
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, LOW);
    } else {
        // If the switch is not pressed, turn off LED 1 and turn on LED 2
        Serial.println("Switch is toggled OFF!");
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, HIGH);
    }
}

