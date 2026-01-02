/**
 * @file example_6.cpp
 * @brief Turn an LED on and off on a webpage.
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 29/12/2024
 **/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

// ===== WIFI SETTINGS =====
const char* ssid = "Galaxy A33 5G CFB1";
const char* password = "txex0537";

// ===== HARDWARE =====
constexpr int LED_PIN = 13;

// ===== WEB SERVER =====
WebServer server(80);

// ===== FUNCTION DECLARATIONS =====
void connectWiFi();
void handleRoot();
void handleScript();
void handleLedOn();
void handleLedOff();

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Start SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS failed!");
    return;
  }

  // Connect to Wi-Fi
  connectWiFi();

  // Routes
  server.on("/", handleRoot);
  server.on("/script.js", handleScript);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);

  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}

// ===== WIFI CONNECTION =====
void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ===== ROUTES =====
void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open index.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleScript() {
  File file = SPIFFS.open("/script.js", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open script.js");
    return;
  }
  server.streamFile(file, "application/javascript");
  file.close();
}

void handleLedOn() {
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/plain", "ON");
}

void handleLedOff() {
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "OFF");
}

// Please follow these steps
// 1. "pio run --target uploadfs" to upload the SPIFFS (SPI Flash File System) data to the ESP32's flash memory
// 2. Upload the main.cpp code
