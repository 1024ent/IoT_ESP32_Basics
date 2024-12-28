/**
 * @file example_2
 * @brief Demonstrates controlling LED brightness using DAC and PWM.
 * @details This program fades an LED in and out using two methods: 
 *          - **DAC (Digital-to-Analog Converter)** for true analog output,
 *          - **PWM (Pulse Width Modulation)** to simulate analog behavior by adjusting the duty cycle.
 * @copyright UMPSA ROBOTICS
 * @author Loo Hui Kie
 * @date 28/12/2024
 */
#include <Arduino.h>

// Define pin numbers
constexpr int DAC_PIN = 25; // GPIO for DAC
constexpr int PWM_PIN = 12; // GPIO for PWM

// Define PWM properties
constexpr int pwmChannel = 0;       // PWM channel (0-15)
constexpr int pwmFrequency = 5000;  // Frequency in Hz
constexpr int pwmResolution = 8;    // Resolution in bits (8 = 0-255)

// Define delays in milliseconds
constexpr int SHORT_DELAY = 10;  // Small delay for fade effect
constexpr int LONG_DELAY = 1000; // Longer delay between functions

// Function prototypes
void Fade_LED_DAC();
void Fade_LED_PWM();
void Smooth_Fade_LED_PWM();

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(115200);

    // Configure LED PWM functionality
    ledcSetup(pwmChannel, pwmFrequency, pwmResolution);

    // Attach the LED pin to the PWM channel
    ledcAttachPin(PWM_PIN, pwmChannel);

    Serial.println("...Starting Your Program...");
}

void loop() {
    Smooth_Fade_LED_PWM();  // Fade using 
}

// Function for fading LED using DAC
void Fade_LED_DAC() {
    Serial.println("Starting LED fade using DAC...");

    // Gradually increase the LED brightness
    for (int i = 0; i <= 255; i++) {
        dacWrite(DAC_PIN, i);       // Write the value to DAC pin
        delay(SHORT_DELAY);         // Small delay to see the fade effect
    }

    // Gradually decrease the LED brightness
    for (int i = 255; i >= 0; i--) {
        dacWrite(DAC_PIN, i);       // Write the value to DAC pin
        delay(SHORT_DELAY);         // Small delay to see the fade effect
    }
}

// Function for fading LED using PWM
void Fade_LED_PWM() {
    Serial.println("Starting LED fade using PWM...");

    // Gradually increase the LED brightness
    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
        ledcWrite(pwmChannel, dutyCycle); // Set PWM duty cycle
        delay(SHORT_DELAY);               // Small delay for fade effect
    }

    // Gradually decrease the LED brightness
    for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
        ledcWrite(pwmChannel, dutyCycle); // Set PWM duty cycle
        delay(SHORT_DELAY);               // Small delay for fade effect
    }
}

// Gamma Correct Function
int gammaCorrect(int value) {
    float gamma = 2.2; // Common gamma value
    return pow((float)value / 255.0, gamma) * 255.0;
}

// Function for fading LED using PWM with gamma correction
void Smooth_Fade_LED_PWM(){
    Serial.println("Starting LED fade using PWM with gamma correction...");

    // Gradually increase the LED brightness
    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
        int correctedDuty = gammaCorrect(dutyCycle); // Apply gamma correction
        ledcWrite(pwmChannel, correctedDuty);        // Set PWM duty cycle
        delay(SHORT_DELAY);                          // Small delay for fade effect
    }

    // Gradually decrease the LED brightness
    for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
        int correctedDuty = gammaCorrect(dutyCycle); // Apply gamma correction
        ledcWrite(pwmChannel, correctedDuty);        // Set PWM duty cycle
        delay(SHORT_DELAY);                          // Small delay for fade effect
    }
}
