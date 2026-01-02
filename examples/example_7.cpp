/**
 * @file example_7.cpp
 * @brief Controls the brightness of an LED using PWM and a slider on a webpage.
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date 29/12/2024
 **/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

const char* ssid = "Galaxy A33 5G CFB1";
const char* password = "txex0537";

WebServer server(80);

constexpr int LED_PIN = 13;
constexpr int PWM_CHANNEL = 0;
constexpr int PWM_FREQUENCY = 5000;
constexpr int PWM_RESOLUTION = 8;

void connectToWiFi();
void handleRoot();
void handleBrightness();
void handleFile(const char* path, const char* type);

void setup() {
    Serial.begin(115200);

    // Initialize PWM for LED
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(LED_PIN, PWM_CHANNEL);

    connectToWiFi();

    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS mount failed.");
        return;
    }

    server.on("/", handleRoot);
    server.on("/style.css", [](){ handleFile("/style.css", "text/css"); });
    server.on("/script.js", [](){ handleFile("/script.js", "application/javascript"); });
    server.on("/set_brightness", handleBrightness);

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

void handleBrightness() {
    if (server.hasArg("value")) {
        int brightness = constrain(server.arg("value").toInt(), 0, 255);
        ledcWrite(PWM_CHANNEL, brightness);
        server.send(200, "text/plain", "Brightness set to " + String(brightness));
    } else {
        server.send(400, "text/plain", "Missing value");
    }
}
