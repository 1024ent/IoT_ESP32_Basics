/**
 * @file main.cpp
 * @brief Main program 
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 28/12/2024
 **/
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

constexpr int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  SerialBT.begin("ESP32_LED");  // Bluetooth device name
  Serial.println("Bluetooth device started, ready to pair!");
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    
    // Turn LED on/off based on command
    if (cmd == '1') {
      digitalWrite(LED_PIN, HIGH);
      SerialBT.println("LED ON");
    } else if (cmd == '0') {
      digitalWrite(LED_PIN, LOW);
      SerialBT.println("LED OFF");
    } else if(cmd == 'T') {
      digitalWrite(LED_PIN, HIGH);
      delay(1000);
      digitalWrite(LED_PIN, LOW);
      delay(1000);
      SerialBT.println("LED Blinking");
    } else {
      SerialBT.println("Send 1 to turn ON, 0 to turn OFF");
    }
  }
}

