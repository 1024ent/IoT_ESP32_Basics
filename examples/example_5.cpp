/**
 * @file example_5.cpp
 * @brief Analog Input Example: 
 *        This program demonstrates how to read an analog input from an LDR (Light Dependent Resistor) sensor 
 *        and display the light intensity value on the Serial Monitor. 
 *        Additionally, it controls an LED based on the light intensity:
 *        - LED1 turns ON when the light intensity is below a specified threshold.
 *        - LED1 turns OFF when the light intensity is above or equal to the threshold.
 * 
 * @details
 *        - The program reads the analog value from the LDR and uses it to determine the light level.
 *        - The light level threshold is set to 300, but it can be adjusted as needed.
 *        - Serial communication is used to log the light intensity values for monitoring.
 *        - Constants are defined for delays and pin numbers to improve code readability and maintainability.
 *
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date
 **/
#include <Arduino.h>

// Function declarations
void handleAnalogInput();   // Handles analog input from LDR sensor

// Define constants for delays
#define SHORT_DELAY 1000
#define MID_DELAY   5000
#define LONG_DELAY  10000

// Define pin numbers for LEDs and LDR
constexpr int LED1_PIN = 13;  // Pin for LED 1
constexpr int LED2_PIN = 12;  // Pin for LED 2
constexpr int LDR1_PIN = 35;  // Pin for LDR input

void setup() {
    // Set pin modes for LEDs and LDR
    pinMode(LED1_PIN, OUTPUT);  // Set LED 1 pin as output
    pinMode(LED2_PIN, OUTPUT);  // Set LED 2 pin as output
    pinMode(LDR1_PIN, INPUT);   // Set LDR pin as input

    // Start serial communication
    Serial.begin(115200);
    delay(SHORT_DELAY);  // Short delay before starting
}

void loop() {
    // Continuously monitor the LDR and control LEDs
    handleAnalogInput();
}

// Function to handle analog input from the LDR (Light Dependent Resistor)
void handleAnalogInput() {
    // Read the LDR value (light intensity)
    int ldrValue = analogRead(LDR1_PIN);
    
    // Log the LDR value to the Serial Monitor
    Serial.print("LDR value: ");
    Serial.println(ldrValue);

    // Control LED 1 based on light intensity
    if (ldrValue < 300) {
        // If light intensity is low (below 300), turn on LED 1
        digitalWrite(LED1_PIN, HIGH);
    } else {
        // If light intensity is high (300 or more), turn off LED 1
        digitalWrite(LED1_PIN, LOW);
    }
}
