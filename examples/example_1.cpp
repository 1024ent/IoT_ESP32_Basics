/**
 * @file example_1
 * @brief Digital output: Blinking an led changing the delay using serial monitor
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 28/12/2024
 **/
#include <Arduino.h>

// Define the function
void Serial_LED_Control();

// Define pin numbers 
static const int LED1 = 13;
static const int LED2 = 12;
static const int LED3 = 14;

// Define variables
int pin = 0;                // Store the currently selected LED pin
int delayDuration = 1000;   // Default delay duration in milliseconds

void setup() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    Serial.begin(115200);
    Serial.println("System Initialized. Waiting for commands...");
}

void loop() {
    Serial_LED_Control();
}

// Function
void Serial_LED_Control() {
    if (Serial.available()) {
        // Prompt for LED number
        Serial.println("Please enter the LED number (1-3) to turn on:");
        while (!Serial.available()); // Wait for input
        String ledInput = Serial.readStringUntil('\n');
        int ledNumber = ledInput.toInt();

        // Validate LED number and set the pin
        if (ledNumber == 1) pin = LED1;
        else if (ledNumber == 2) pin = LED2;
        else if (ledNumber == 3) pin = LED3;
        else {
            Serial.println("Invalid LED number. Please enter 1, 2, or 3.");
            return;
        }

        // Turn on the selected LED
        digitalWrite(pin, HIGH);
        Serial.print("LED ");
        Serial.print(ledNumber);
        Serial.println(" turned on.");

        // Prompt for delay duration
        Serial.println("Please enter the delay duration (in milliseconds):");
        while (!Serial.available()); // Wait for input
        String delayInput = Serial.readStringUntil('\n');
        int newDelayDuration = delayInput.toInt();

        if (newDelayDuration <= 0) {
            Serial.println("Invalid delay duration. Please enter a positive number.");
            return;
        }

        // Update delay duration
        delayDuration = newDelayDuration;
        Serial.print("Delay duration changed to ");
        Serial.print(delayDuration);
        Serial.println(" milliseconds.");

        while(1){
            // Blink the LED
            Serial.println("Blinking the selected LED...");
            digitalWrite(pin, HIGH);
            delay(delayDuration);
            digitalWrite(pin, LOW);
            delay(delayDuration);            
        }
    }
}
