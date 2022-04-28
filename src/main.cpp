#include <Arduino.h>
#include <ArduinoJson.h>
#include <EasyHTTP.h>
#define SENSOR_PIN 34  // used for ESP32

int sensorValue = 0;

char* ssid = (char*) "Redmi";
char* password = (char*) "senha111";

String baseURL = "https://sensor-info.herokuapp.com";

EasyHTTP http(ssid, password);

void setup() {
  Serial.begin(115200);
  http.connectWiFi();
  http.setBaseURL(baseURL);
}

void loop() {

  sensorValue = analogRead(SENSOR_PIN);
  sensorValue = 100 - (((sensorValue * 100)) / (4095));
  Serial.print("Moisture : ");
  Serial.println(sensorValue);
  Serial.println("%");
  


  DynamicJsonDocument doc(2048);
  String payload = "";

  doc["data"] = sensorValue;
  serializeJson(doc, payload);

  Serial.println(payload);

  String response = http.post("/sensor-information", payload);
  Serial.println(response);

  delay(5000);
} 

