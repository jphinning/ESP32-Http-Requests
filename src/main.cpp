#include <Arduino.h>
#include <ArduinoJson.h>
#include <EasyHTTP.h>
#define SensorPin 4  // used for ESP32

char* ssid = (char*) "VIVOFIBRA-55C0";
char* password = (char*) "6FCBCC76C2";

String baseURL = "https://sensor-info.herokuapp.com/test";

EasyHTTP http(ssid, password);

void setup() {
  Serial.begin(115200);
  http.connectWiFi();
  http.setBaseURL(baseURL);
}

void loop() {

  float sensorValue = analogRead(SensorPin);
  Serial.println(sensorValue);


  DynamicJsonDocument doc(2048);
  String payload = "";

  doc["data"] = sensorValue;
  serializeJson(doc, payload);

  Serial.println(payload);

  String response = http.post("/sensor-information", payload);
  Serial.println(response);

  delay(5000);
} 

