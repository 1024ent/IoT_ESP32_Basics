/**
 * @file example_1
 * @brief main esp32doit-devkit-v1
 * @copyright UMPSA ROBOTICS
 * @author LOO HUI KIE
 * @date - 
 **/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
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
void handleCSS();
void handleJS();

void setup() {
  Serial.begin(115200);
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);

  connectToWiFi();

  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS filesystem.");
    return;
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/style.css", HTTP_GET, handleCSS);
  server.on("/script.js", HTTP_GET, handleJS);
  server.on("/set_brightness", HTTP_GET, handleBrightness);

  server.begin();
  Serial.println("Server started!");
}

void loop() {
  server.handleClient();
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open index.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleBrightness() {
  String value = server.arg("value");
  int brightness = constrain(value.toInt(), 0, 255);
  ledcWrite(PWM_CHANNEL, brightness);
  server.send(200, "text/plain", "Brightness set to: " + String(brightness));
}

void handleCSS() {
  File file = SPIFFS.open("/style.css", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open style.css");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
}

void handleJS() {
  File file = SPIFFS.open("/script.js", "r");
  if (!file) {
    server.send(500, "text/plain", "Failed to open script.js");
    return;
  }
  server.streamFile(file, "application/javascript");
  file.close();
}
