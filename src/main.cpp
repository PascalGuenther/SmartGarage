#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include <DoubleResetDetector.h>
#include "project-config.h"
#include "bsp-config.h"
#include <WiFiManager.h>

// ------- Static Variables -------
DoubleResetDetector oDrd(DRD_CFG_TIMEOUT_SECONDS, DRD_CFG_TIMEOUT_ADDRESS);



void setup() {
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
  if(oDrd.detectDoubleReset()) {
    // device has been double-reset in a short amount of time
    Serial.println("Config mode after reset");
    bWiFiConnected = wifiManager.startConfigPortal(WIFI_CFG_ACCESS_POINT_SSID, WIFI_CFG_ACCESS_POINT_PASSWORD);
  } else {
    bWiFiConnected = wifiManager.autoConnect(WIFI_CFG_ACCESS_POINT_SSID, WIFI_CFG_ACCESS_POINT_PASSWORD);
  }
  oDrd.stop();

  if (!bWiFiConnected) {
    // failed to connect to an AP
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.println("Connected to WiFi \"" + WiFi.SSID() + "\", IP " + WiFi.localIP().toString());

  Serial.printf("Leaving setup...");

}

void loop() {

}