/**
 * @file example_1
 * @brief Turn an LED on and off on a webpage.
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 29/12/2024
 **/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "Galaxy A33 5G CFB1";          // Wi-Fi network SSID
const char* password = "txex0537";  // Wi-Fi network password

// Set up the web server on port 80
WebServer server(80);

// Pin for controlling the LED
constexpr int LED_PIN = 13; // Define LED pin as a constant for better readability

// Function declarations for handling HTTP requests
void connectToWiFi();
void handleRoot();
void handleLEDOn();
void handleLEDOff();

// Setup function: Initialize Serial, connect to Wi-Fi, and start the web server
void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi network
  connectToWiFi();

  // Set up HTTP routes for handling requests
  server.on("/", HTTP_GET, handleRoot);                // Root endpoint to show a simple message
  server.on("/led/on", HTTP_GET, handleLEDOn);   // LED ON endpoint
  server.on("/led/off", HTTP_GET, handleLEDOff); // LED OFF endpoint

  // Start the web server
  server.begin();
  Serial.println("Server started!");
}

// Loop function: Continuously handle incoming client requests
void loop() {
  server.handleClient();
}

// Function to connect to Wi-Fi
void connectToWiFi() {
  WiFi.begin(ssid, password);

  // Wait until the ESP32 is connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print the IP address once connected
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Handle the root endpoint ("/")
void handleRoot() {
  String html = "<html><body><h1>ESP32 LED Control</h1>";
  html += "<p><a href=\"/led/on\"><button>Turn ON LED</button></a></p>";
  html += "<p><a href=\"/led/off\"><button>Turn OFF LED</button></a></p>";
  html += "</body></html>";

  // Send HTML content as response
  server.send(200, "text/html", html);
}

// Handle the "/led/on" request
void handleLEDOn() {
  digitalWrite(LED_PIN, HIGH);  // Turn ON the LED
  server.send(200, "text/plain", "LED is ON");
}

// Handle the "/led/off" request
void handleLEDOff() {
  digitalWrite(LED_PIN, LOW);   // Turn OFF the LED
  server.send(200, "text/plain", "LED is OFF");
}

// Please follow these steps
// 1. "pio run --target uploadfs" to upload the SPIFFS (SPI Flash File System) data to the ESP32's flash memory
// 2. Upload the main.cpp code
