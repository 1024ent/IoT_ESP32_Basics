#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>

// Wi-Fi credentials
const char* ssid = "YourSSID";        // Wi-Fi network SSID
const char* password = "YourPassword"; // Wi-Fi network password

// Pin for LDR sensor (Analog pin)
constexpr int LDR_PIN = 34;  // Connect LDR to pin 34 (analog input)

// Set up the web server on port 80
WebServer server(80);

// Function declarations
void connectToWiFi();
void handleRoot();
void handleLDRValue();

void setup() {
  Serial.begin(115200);

  // Initialize analog pin (LDR)
  pinMode(LDR_PIN, INPUT);

  // Connect to Wi-Fi network
  connectToWiFi();

  // Initialize SPIFFS for file system access (HTML, JS, CSS)
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS filesystem.");
    return;
  }

  // Set up HTTP routes for handling requests
  server.on("/", HTTP_GET, handleRoot);                // Root endpoint for the web page
  server.on("/ldr_value", HTTP_GET, handleLDRValue);    // Endpoint for getting LDR value

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

void handleLDRValue() {
  // Read the LDR value from the analog pin (0-4095)
  int ldrValue = analogRead(LDR_PIN);

  // Send the LDR value as a response
  server.send(200, "text/plain", String(ldrValue));
}
