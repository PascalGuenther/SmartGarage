#pragma once
#include "Arduino.h"

// #define NDEBUG


#ifdef LED_BUILTIN
    #undef LED_BUILTIN
#endif // LED_BUILTIN

#define NODEMCU_V1 (1u)
#define NODEMCU_V2 (2u)
#define NODEMCU_V3 (3u)

#define BOARD_TYPE NODEMCU_V3

#define SERIAL_BAUDRATE (115200u)

// At first start, the device will create an Access Point WiFi network (Captive portal).
// Connect to this network to configure the credentials of your WiFi network.
// Below, please configure the credentials of the Access Point that the device will create.
#define WIFI_CFG_ACCESS_POINT_SSID        ("Garage")
#define WIFI_CFG_ACCESS_POINT_PASSWORD    ("456config789")

// uncomment to set a minimum threadhold for signal quality of the AP to connect to
//#define WIFI_CFG_MINIMUM_SIGNAL_QUALITY_PERCENT (8)

// uncomment to set a timeout after which the configuration portal will close
// #define WIFI_CFG_PORTAL_TIMEOUT_SECONDS (4*60)

// Double reset detector: Timeout
#define DRD_CFG_TIMEOUT_SECONDS       (10u)

// Double reset detector: Address
#define DRD_CFG_TIMEOUT_ADDRESS       (0u)

#define WEMO_DEVICE_NAME_GARAGE "Garage"