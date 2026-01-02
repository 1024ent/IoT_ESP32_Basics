/**
 * @file example_3
 * @brief Demonstrates controlling LED brightness using DAC and PWM.
 * @details This program changing an LED brightness using two methods: 
 *          - **DAC (Digital-to-Analog Converter)** for true analog output,
 *          - **PWM (Pulse Width Modulation)** to simulate analog behavior by adjusting the duty cycle.
 * @copyright UMPSA ROBOTICS
 * @author Loo Hui Kie
 * @date 29/12/2024
 */
#include <Arduino.h>

// Pin definitions
static const int PWM_PIN = 12;   // PWM Pin (for simulated analog output)
static const int DAC_PIN = 25;   // DAC Pin (for true analog output)

// PWM settings
const int pwmChannel = 0;       // PWM channel (0-15)
const int pwmFrequency = 5000;  // Frequency in Hz
const int pwmResolution = 8;    // Resolution in bits (0-255)

// Brightness levels
const int BRIGHT_75 = 191;  // 75% of 255
const int BRIGHT_50 = 127;  // 50% of 255
const int BRIGHT_25 = 63;   // 25% of 255

// Function prototypes
void setBrightnessPWM(int brightness);
void setBrightnessDAC(int brightness);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  
  // Configure LED PWM functionality
  ledcSetup(pwmChannel, pwmFrequency, pwmResolution);
  ledcAttachPin(PWM_PIN, pwmChannel);
  ledcWrite(pwmChannel, 255);

  // Inform the user
  Serial.println("Enter 1, 2, or 3 to set LED brightness:");
  Serial.println("1 - 75%, 2 - 50%, 3 - 25%");
}

void loop() {
  if (Serial.available() > 0) {
      int brightnessLevel = Serial.parseInt();  // Read the user input
      
      if (brightnessLevel == 1) {
          // Set 75% brightness using PWM
          setBrightnessPWM(BRIGHT_75);
          setBrightnessDAC(BRIGHT_75);
          Serial.println("Brightness set to 75%");
      } 
      else if (brightnessLevel == 2) {
          // Set 50% brightness using PWM
          setBrightnessPWM(BRIGHT_50);
          setBrightnessDAC(BRIGHT_50);
          Serial.println("Brightness set to 50%");
      } 
      else if (brightnessLevel == 3) {
          // Set 25% brightness using PWM
          setBrightnessPWM(BRIGHT_25);
          setBrightnessDAC(BRIGHT_25);
          Serial.println("Brightness set to 25%");
      }
      else {
          Serial.println("Invalid input. Enter 1, 2, or 3.");
      }
  }
}

// Function to control brightness using PWM
void setBrightnessPWM(int brightness) {
  ledcWrite(pwmChannel, brightness);  // Set the PWM duty cycle
}

// Function to control brightness using DAC
void setBrightnessDAC(int brightness) {
  dacWrite(DAC_PIN, brightness);  // Write the value to the DAC pin
}

