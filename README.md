# SmartGarage - Alexa Garage Door Drive Remote
The SmartGarage software allows you to control your garage door with Amazon Alexa-powered devices like the Amazon Echo.
This project is based on the very inexpensive ESP8266 or ESP32 microcontroller and the [PlatformIO](https://platformio.org) IDE.
## Usage
This project should run on all ESP8266 or ESP32 boards which are available from various
manufacturers. By default, the software is configured to use the ESP-01 board
and Pin 0. If you prefer to use a different board (like NodeMCU), please edit
the files platform.ino and bsp-config.h.
### Hardware setup
Most garage door drivers provide an input for an extension unit. **Caution**: These
connectors can carry a live voltage of 240 V or more. Typically used
to connect wall-mounted push buttons.
The microcontroller will output a pulse on the configured GPIO pin
which can be used to emulate a press operation of the push button.

On my garage, there are an 18 V and a GND connector pin. I use an PC123 optocoupler
to hook up these input terminals to the microcontroller. The 18 V terminal is connected to the
collector (PCF123 Pin 4), Ground to the emitter (PCF123 Pin 3).
Since the microcontroller is configured to output a low pulse, the Anode is connected to
Pin 0 of the ESP, and the cathode to 3.3 V via a 100 Ohm resistor.

## Software installation
If you haven't already, please download the PlatformIO IDE, which is an extension for 
[Visual Studio Code](https://code.visualstudio.com) or [Atom](https://atom.io).
Please follow the instructions on the [PlatformIO Website](https://platformio.org)
to compile and download the firmware to the device.

You might apply changes to the configuration. To configure which board and which GPIO
pin to use, please edit the files platform.ino and bsp-config.h.
Also make sure to instantiate the Garage object in main.c to the matching polarity for
your installation, with "false" meaning active-high and "true" meaning active-low, respectively.

Additional options can be set in project-settings.h.

### Setting up WiFi credentials
Upon first boot, the device will boot in WiFi Access Point mode
to provide a configuration portal.
After the software has been downloaded to the device, connect to the WiFi network
with SSID "Garage", the default password is "456config789" (without the quotation marks).
Open the browser and navigate to http://http://192.168.4.1 where you
can setup your WiFi connection.

### Connect to Alexa
After the device has connected to your WiFi network, ask Alexa to start device discovery.
> "Alexa, discover my devices!"

If your device has been discovered, you can interact with it as if it were a light bulb.
To open or close the garage, just say
> "Alexa, turn on the garage"
> 
## Dependencies
This project is based on the [fauxmoESP](https://bitbucket.org/xoseperez/fauxmoesp/src/master) library by Xose Pérez.
Additional libraries:
- [DoubleResetDetector](https://github.com/datacute/DoubleResetDetector) by Stephen Denne
- [WiFiManager](https://github.com/tzapu/WiFiManager) by tzapu

Thank you and all people who contribute to these projects and the SDKs for your great work!

## Disclaimer
This software is provided without warranty of any kind. Distribution
and/or use of radio-enabled devices may be subject to regulatory and
approval.

This software is missing fundamental security features. Therefore, this
software does not provide sufficient access control. This may result in
refusal of insurance claims  and/or voiding/cancellation of your policy.
### Warning
Work with electricity poses dangers. Electricity can cause severe
injury, death, or property loss. Please consult a Licensed Electrician
before performing with electrical circuits and follow your local
electrical code.