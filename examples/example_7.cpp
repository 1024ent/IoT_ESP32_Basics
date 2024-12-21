/**
 * @file main.cpp
 * @brief Controls the brightness of an LED using PWM and a slider on a webpage.
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 
 **/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>

// Wi-Fi credentials
const char* ssid = "YourSSID";        // Wi-Fi network SSID
const char* password = "YourPassword"; // Wi-Fi network password

// Set up the web server on port 80
WebServer server(80);

// Pin for controlling the LED
constexpr int LED_PIN = 13; // Define LED pin as a constant for better readability
constexpr int PWM_CHANNEL = 0; // PWM channel for controlling brightness
constexpr int PWM_FREQUENCY = 5000; // PWM frequency (5kHz)
constexpr int PWM_RESOLUTION = 8; // PWM resolution (8-bit: 0-255)

void connectToWiFi();
void handleRoot();
void handleBrightness();

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Initialize the LED pin for PWM output
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION); // Set up PWM on the LED pin
  ledcAttachPin(LED_PIN, PWM_CHANNEL); // Attach the LED pin to the PWM channel

  // Connect to Wi-Fi network
  connectToWiFi();

  // Initialize SPIFFS for file system access (HTML, JS, CSS)
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS filesystem.");
    return;
  }

  // Set up HTTP routes for handling requests
  server.on("/", HTTP_GET, handleRoot);                // Root endpoint for the web page
  server.on("/set_brightness", HTTP_GET, handleBrightness); // Endpoint for setting brightness

  // Start the web server
  server.begin();
  Serial.println("Server started!");
}

void loop() {
  server.handleClient();
}

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

void handleRoot() {
  // Serve the HTML file from SPIFFS
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open index.html");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}

void handleBrightness() {
  // Get the brightness value from the query string
  String value = server.arg("value");

  // Convert to integer and constrain to valid PWM range (0-255)
  int brightness = constrain(value.toInt(), 0, 255);

  // Set the LED brightness using PWM
  ledcWrite(PWM_CHANNEL, brightness);

  // Send the current brightness value back as a response
  server.send(200, "text/plain", "Brightness set to: " + String(brightness));
}
