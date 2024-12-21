/**
 * @file example_1
 * @brief Digital output: Blinking an led changing the delay using serial monitor
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date
 **/
#include <Arduino.h>

// Define the function
void Serial_LED_Control();

// Define pin numbers 
static const int LED1 = 13;
static const int LED2 = 12;
static const int LED3 = 14;

// Define variable
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
        Serial.println("\nCommands:");
        Serial.println("To turn on an LED, type: A");
        Serial.println("To change the delay duration, type: B");

        String selection = Serial.readStringUntil('\n');

        if (selection.startsWith("A")) {
            Serial.println("Please enter the LED number (1-3) to turn on:");
            while (!Serial.available()); // Wait for input
            String ledInput = Serial.readStringUntil('\n');
            int ledNumber = ledInput.toInt();

            if (ledNumber == 1) pin = LED1;
            else if (ledNumber == 2) pin = LED2;
            else if (ledNumber == 3) pin = LED3;
            else {
                Serial.println("Invalid LED number. Please enter 1, 2, or 3.");
                return;
            }

            digitalWrite(pin, HIGH); // Turn on the selected LED
            Serial.print("LED ");
            Serial.print(ledNumber);
            Serial.println(" turned on.");
        } 
        else if (selection.startsWith("B")) {
            Serial.println("Please enter the delay duration (in milliseconds):");
            while (!Serial.available()); // Wait for input
            String delayInput = Serial.readStringUntil('\n');
            int delayDuration = delayInput.toInt();

            if (delayDuration <= 0) {
                Serial.println("Invalid delay duration. Please enter a positive number.");
                return;
            }

            Serial.print("Delay duration changed to ");
            Serial.print(delayDuration);
            Serial.println(" milliseconds.");

            // Blink the currently selected LED with the new delay
            if (pin != 0) { // Check if a valid LED is selected
                Serial.println("Blinking the selected LED with the new delay...");
                digitalWrite(pin, HIGH);
                delay(pdMS_TO_TICKS(delayDuration));
                digitalWrite(pin, LOW);
                delay(pdMS_TO_TICKS(delayDuration));
            } else {
                Serial.println("No LED selected for blinking.");
            }
        } 
        else {
            Serial.println("Invalid input. Please try again.");
        }
    }
}
