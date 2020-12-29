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
#include <ESP8266WiFi.h> 
#include <DoubleResetDetector.h>
#include "project-config.h"
#include "bsp-config.h"
#include <WiFiManager.h>
#include <fauxmoESP.h>
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
DoubleResetDetector oDrd(DRD_CFG_TIMEOUT_SECONDS, DRD_CFG_TIMEOUT_ADDRESS);
fauxmoESP oFauxmo;
SmartGarage::GarageDoor oGarage(ucGarageActuatorPin, SmartGarage::Polarity::activeLow);

static void fauxmoSetup(void)
{
  oFauxmo.createServer(true);
  oFauxmo.setPort(80);
  oFauxmo.enable(true);

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

  // Start a configuration portal, if not network config is present.
  // Otherwise, try to connect to the WiFi network
  bool bWiFiConnected;
  if(oDrd.detectDoubleReset())
  {
    // device has been double-reset in a short amount of time
    Serial.println("Config mode after reset");
    bWiFiConnected = wifiManager.startConfigPortal(WIFI_CFG_ACCESS_POINT_SSID, WIFI_CFG_ACCESS_POINT_PASSWORD);
  } else
  {
    bWiFiConnected = wifiManager.autoConnect(WIFI_CFG_ACCESS_POINT_SSID, WIFI_CFG_ACCESS_POINT_PASSWORD);
  }
  oDrd.stop();

  if (!bWiFiConnected)
  {
    // failed to connect to an AP
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.println("Connected to WiFi \"" + WiFi.SSID() + "\", IP " + WiFi.localIP().toString());
  fauxmoSetup();

  Serial.printf("Leaving setup...");

}

void loop()
{
  oFauxmo.handle();
}