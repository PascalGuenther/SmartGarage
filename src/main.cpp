/**
 * @file main.cpp
 * @author Pascal Guenther (pascal.develop@pguenther.net)
 * @brief Garage door opener for Amazon Alexa
 * @version 1.0
 * @date 2020-05-22
 * 
 * @copyright Copyright (c) 2020 Pascal Guenther
 * 
 * Control your garage door with Amazon Alexa using the ESP8266 WiFi microcontroller.
 * See README.md for instructions.
 * 
 */

#include <Arduino.h>
#include <ArduinoOTA.h>
#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#elif defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#else
#error "platform not supported"
#endif
#include <WiFiManager.h>
#include <fauxmoESP.h>
#include "project-config.h"
#include "bsp-config.h"
#include "Garage.h"

#if !defined(NDEBUG)
  #define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__)
  #define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else // NDEBUG
  #define DEBUG_PRINT(...)
  #define DEBUG_PRINTF(...)
  #define DEBUG_PRINTLN(...)
#endif // NDEBUG


// ------- Static Variables -------

fauxmoESP oFauxmo;
SmartGarage::GarageDoor oGarage(ucGarageActuatorPin, SmartGarage::Polarity::activeLow);

static void fauxmoSetup(void)
{
  oFauxmo.setPort(80);

  oFauxmo.addDevice(WEMO_DEVICE_NAME_GARAGE);
  oFauxmo.onSetState([](unsigned char ucDeviceId, const char * aucDeviceName, bool bState, unsigned char ucValue)
  {
    DEBUG_PRINTF("[MAIN] Device #%d (%s) state: %s value: %d\n", ucDeviceId, aucDeviceName, bState ? "ON" : "OFF", ucValue);
    if (0u == strncmp(aucDeviceName, WEMO_DEVICE_NAME_GARAGE, sizeof(WEMO_DEVICE_NAME_GARAGE)))
    {
      DEBUG_PRINTLN(bState ? "Wemo Garage ON": "Wemo Garage OFF");
      oGarage.Move();
    }
  });
  oFauxmo.enable(true);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println("\n\n\n");
  Serial.println("============================");
  Serial.println("       System start         ");
  Serial.println("============================");


  // WiFi Manager will be freed after configuration has finished
  WiFiManager wifiManager;

  wifiManager.setTimeout(40);
  bool bWiFiConnected = wifiManager.startConfigPortal(WIFI_CFG_ACCESS_POINT_SSID, WIFI_CFG_ACCESS_POINT_PASSWORD);
  if(!bWiFiConnected)
  {
    wifiManager.setTimeout(0);
    bWiFiConnected = wifiManager.autoConnect(WIFI_CFG_ACCESS_POINT_SSID, WIFI_CFG_ACCESS_POINT_PASSWORD);
  }

  if (!bWiFiConnected)
  {
    // failed to connect to an AP
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.restart();
    delay(5000);
  }
#if defined(ARDUINO_ARCH_ESP8266)
  WiFi.onStationModeDisconnected([] (const WiFiEventStationModeDisconnected& /* event */) {
    Serial.println("WiFi disconnected. Resetting device...");
    delay(30000);
    ESP.reset();
  });
#endif // defined(ARDUINO_ARCH_ESP8266)

  Serial.println("Connected to WiFi \"" + WiFi.SSID() + "\", IP " + WiFi.localIP().toString());
  fauxmoSetup();

  Serial.printf("Leaving setup...");
  ArduinoOTA.begin();

}

#if 0
static unsigned long lastMillis;
#endif

void loop()
{
  ArduinoOTA.handle();
#if 0
  const auto newMillis = millis();
  static_assert(std::is_same<std::decay<decltype(lastMillis)>::type, std::decay<decltype(newMillis)>::type>::value, "");
  const auto deltaTime = (newMillis >= lastMillis) ? (newMillis - lastMillis) : (lastMillis - newMillis);
  if(deltaTime > 30000ul)
  {
    lastMillis = newMillis;
    if(WiFi.status() != WL_CONNECTED)
    {
      WiFi.disconnect();
      WiFi.reconnect();
    }
  }
#endif

  oFauxmo.handle();
}
