/**
 * @file example_1
 * @brief Digital output: Blinking an led changing the delay using serial monitor
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 28/12/2024
 **/
#include <Arduino.h>

// Function Declarations
void readSerialCommand();
void blinkLED();

// ===== LED PINS =====
const int LED1 = 13;
const int LED2 = 12;
const int LED3 = 14;

// ===== VARIABLES =====
int selectedPin = -1;        // Selected LED pin
int blinkDelay = 1000;       // Blink delay in milliseconds
bool blinking = false;       // Are we blinking?

unsigned long lastTime = 0;
bool ledState = LOW;

int blinkCount = 0;          // Counts LED toggles
const int MAX_BLINKS = 10;   // 5 blinks = ON + OFF = 10 toggles

// ===== SETUP =====
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  Serial.begin(115200);

  Serial.println("=== Serial LED Control ===");
  Serial.println("Enter LED number (1, 2, or 3):");
}

// ===== LOOP =====
void loop() {
  readSerialCommand();
  blinkLED();
}

// ===== READ SERIAL INPUT =====
void readSerialCommand() {
  if (!Serial.available()) return;

  int value = Serial.parseInt();

  // STEP 1: SELECT LED
  if (selectedPin == -1) {
    if (value == 1) selectedPin = LED1;
    else if (value == 2) selectedPin = LED2;
    else if (value == 3) selectedPin = LED3;
    else {
        Serial.println("Invalid LED. Enter 1, 2, or 3:");
        return;
    }

    Serial.println("LED selected.");
    Serial.println("Enter blink delay (ms):");
    Serial.read();
    return;
  }

  // STEP 2: SET DELAY AND START BLINKING
  if (value <= 0) {
      Serial.println("Delay must be positive.");
      return;
  }

  // Valid delay
  blinkDelay = value;
  blinking = true;
  blinkCount = 0;

  ledState = LOW;
  digitalWrite(selectedPin, LOW);

  lastTime = millis();

  // Clear any remaining serial characters (newline)
  while (Serial.available()) {
      Serial.read();
  }

  Serial.println("Blinking 5 times...");

  Serial.read();
}

// ===== BLINK LOGIC (NON-BLOCKING) =====
void blinkLED() {
  if (!blinking) return;

  unsigned long currentTime = millis();

  if (currentTime - lastTime >= blinkDelay) {
    lastTime = currentTime;

    ledState = !ledState;
    digitalWrite(selectedPin, ledState);
    blinkCount++;

    // STOP AFTER 5 BLINKS
    if (blinkCount >= MAX_BLINKS) {
      blinking = false;
      digitalWrite(selectedPin, LOW);
      selectedPin = -1;

      Serial.println("Done.");
      Serial.println("Enter LED number (1, 2, or 3):");
    }
  }
}
