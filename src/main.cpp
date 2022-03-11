#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <EasyHTTP.h>

char* ssid = (char*) "VIVOFIBRA-55C0";
char* password = (char*) "6FCBCC76C2";

String baseURL = "https://aqueous-coast-43643.herokuapp.com";

EasyHTTP http(ssid, password);

void setup() {
  Serial.begin(115200);
  http.connectWiFi();
  http.setBaseURL(baseURL);
}

void loop() {
  DynamicJsonDocument doc(2048);
  String payload = "";

  char* user = (char*) "john";
  char* password = (char*) "I wnat to describe tahr";

  doc["user"] = user;
  doc["password"] = password;
  serializeJson(doc, payload);

  Serial.println(payload);

  String response = http.post("/login", payload);
  Serial.println(response);

  delay(300000);
} 

