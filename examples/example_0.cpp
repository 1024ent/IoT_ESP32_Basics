/**
 * @file example_0
 * @brief Digital output: Blinking an led
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 28/12/2024
 **/
#include <Arduino.h>

// Define the function
void blinking_led_1();
void blinking_led_2();
void blinking_led_3();

// Define pin numbers 
static const int LED1 = 13;
static const int LED2 = 12;
static const int LED3 = 14;

// Define constant
#define short_delay 1000    // Removed semicolon
#define long_delay 2000     // Removed semicolon

void setup() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    blinking_led_3();
}

// Function
void blinking_led_1() {
    for (int count = 0; count < 10; count++) { // Local variable for loop
        Serial.print("Blink count: ");
        Serial.println(count + 1); // Display the current blink count (1 to 10)

        digitalWrite(LED1, HIGH);
        delay(short_delay);
        digitalWrite(LED1, LOW);
        delay(short_delay);
    }
    while(1){

    }
}

void blinking_led_2() {
    int count = 0; // Local variable
    do {
        Serial.print("Blink count: ");
        Serial.println(count + 1); // Display the current blink count (1 to 5)

        digitalWrite(LED2, HIGH);
        delay(long_delay);
        digitalWrite(LED2, LOW);
        delay(long_delay);

        count++; // Increment count
    } while (count < 5);
    while(1){

    }
}

void blinking_led_3() {
    int count = 0; // Local variable
    while (count < 10) {
        Serial.print("Blink count: ");
        Serial.println(count + 1); // Display the current blink count (1 to 10)

        digitalWrite(LED3, HIGH);
        delay(short_delay);
        digitalWrite(LED3, LOW);
        delay(short_delay);

        count++; // Increment count
    }
    while(1){

    }
}
