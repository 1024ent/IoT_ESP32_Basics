/**
 * @file example_1
 * @brief main esp32doit-devkit-v1
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date - 
 **/
#include <Arduino.h>

// Function declarations
void handleAnalogInput();   // Handles analog input from LDR sensor

// Define constants for delays
#define SHORT_DELAY 1000
#define MID_DELAY   5000
#define LONG_DELAY  10000

// Define pin numbers for LEDs and LDR
constexpr int LED1_PIN = 14;  // Pin for LED 1
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
    if (ldrValue < 2000) {
        // If light intensity is low (below 300), turn on LED 1
        digitalWrite(LED1_PIN, HIGH);
    } else {
        // If light intensity is high (300 or more), turn off LED 1
        digitalWrite(LED1_PIN, LOW);
    }
}
