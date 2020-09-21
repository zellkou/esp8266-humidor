// Local include
#include "async.h"
#include "mqtt.h"
#include "ota.h"
#include "wifimanager.h"

// Library include
#include <Adafruit_Sensor.h>     // https://github.com/adafruit/Adafruit_Sensor
#include <Arduino.h>             //
#include <AsyncMqttClient.h>     // https://github.com/me-no-dev/async-mqtt-client
#include <DHT.h>                 // https://github.com/adafruit/DHT-sensor-library
#include <DNSServer.h>           //
#include <ESP8266WebServer.h>    //
#include <ESP8266WiFi.h>         //
#include <ESPAsyncTCP.h>         // https://github.com/me-no-dev/ESPAsyncTCP
#include <ESPAsyncWebServer.h>   // https://github.com/me-no-dev/ESPAsyncWebServer
#include <Hash.h>                //
#include <Ticker.h>              //
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager

// const
const int FW_VERSION = 2017102501 ; /// year_month_day_same day release number
const char* fwUrlBase = "https://thehillbillyhacker.com/.fota/";
const long interval = 10000;  // Updates DHT readings every 10 seconds
unsigned long previousMillis = 0;   // Stores last time temperature was published

// define

#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11     // DHT 11
#define MQTT_PUB_TEMP "esp/dht/temperature"
#define MQTT_PUB_HUM "esp/dht/humidity"
#define MQTT_HOST "example.com"
#define MQTT_PORT 1883

// variable
float t = 0.0; // float to hold temp
float h = 0.0; // float to hold humidity
bool HTTP_OTA = false; // for http update if loop may not need
String header; // Variable to store the HTTP request
