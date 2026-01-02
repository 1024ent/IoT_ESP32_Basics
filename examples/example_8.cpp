/**
 * @file example_8.cpp
 * @brief Read the value of LDR sensor and display the value on a webpage.
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 29/12/2024
 **/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

// Wi-Fi credentials
const char* ssid = "Galaxy A33 5G CFB1";
const char* password = "txex0537";

// LDR analog pin
constexpr int LDR_PIN = 35;

// Web server
WebServer server(80);

// Function declarations
void connectToWiFi();
void handleRoot();
void handleLDRValue();
void handleFile(const char* path, const char* type);

void setup() {
    Serial.begin(115200);
    pinMode(LDR_PIN, INPUT);

    connectToWiFi();

    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS mount failed.");
        return;
    }

    server.on("/", handleRoot);
    server.on("/ldr_value", handleLDRValue);
    server.on("/style.css", [](){ handleFile("/style.css", "text/css"); });
    server.on("/script.js", [](){ handleFile("/script.js", "application/javascript"); });

    server.begin();
    Serial.println("Server started!");
}

void loop() {
    server.handleClient();
}

void connectToWiFi() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void handleRoot() {
    handleFile("/index.html", "text/html");
}

void handleFile(const char* path, const char* type) {
    File file = SPIFFS.open(path);
    if (!file) {
        server.send(404, "text/plain", "File not found");
        return;
    }
    server.streamFile(file, type);
    file.close();
}

void handleLDRValue() {
    int ldrValue = analogRead(LDR_PIN);
    server.send(200, "text/plain", String(ldrValue));
}

