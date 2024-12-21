/**
 * @file example_6.cpp
 * @brief Controls an LED using an ESP32 web server with ON/OFF buttons.
 * @description This sketch creates a simple web server running on ESP32 that controls an LED using HTTP requests.
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 
 **/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "YourSSID";        // Wi-Fi network SSID
const char* password = "YourPassword"; // Wi-Fi network password

// Set up the web server on port 80
WebServer server(80);

// Pin for controlling the LED
constexpr int LED_PIN = 13; // Define LED pin as a constant for better readability

// Function declarations for handling HTTP requests
void handleRoot();
void handleLED();

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
  server.on("/led/{state}", HTTP_GET, handleLED);       // LED control endpoint

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

// Handle LED control requests ("/led/on" or "/led/off")
void handleLED() {
  String state = server.pathArg(0); // Extract state from the URL path

  if (state == "on") {
    digitalWrite(LED_PIN, HIGH);  // Turn ON the LED
    server.send(200, "text/plain", "LED is ON");
  } 
  else if (state == "off") {
    digitalWrite(LED_PIN, LOW);   // Turn OFF the LED
    server.send(200, "text/plain", "LED is OFF");
  } 
  else {
    server.send(400, "text/plain", "Invalid request: Use '/led/on' or '/led/off'");
  }
}

