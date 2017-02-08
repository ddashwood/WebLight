# WebLight

A simple web page that controls a light

## Hardware - Shopping List and Setup

* A NodeMCU.
  * Any ESP8266-compatible board would probably work, but hasn't been tested
* NeoPixel lights

### Up to 4 NeoPixels

* Connect the GND pin on the NodeMCU to the GND connector on the NeoPixels
* Connect the VIN pin on the NodeMCU to the 5VDC connector on the NeoPixels
* Connect the D2 pin on the NodeMCU to the DIN connector on the NeoPixels
* The NodeMCU can be powered by a USB cable, and it will also provide power to the NeoPixels

### More than 4 NeoPixels

The power that can be supplied by the NodeMCU may not be sufficient for powering more than 4 NeoPixels. If you wish to connect more than 4 NeoPixels, use a separate power supply. Connect the power supply to the GND and VIN pins on the NodeMCU, as well as to the GND and 5VDC connectors on the NeoPixels.

## Software Compilation and Installation

1. If you have not used a NodeMCU before, you will need to:
  * Install [serial drivers](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx) for the board
  * Add the following link to the Additional Board Manager URLs in the Arduino IDE Preferences:
    > http://arduino.esp8266.com/package_esp8266com_index.json
  * Open the Boards Manager from the Tools -> Board menu, search for esp8266 and install the platform. Then select NodeMCU 1.0 from the Tools -> Board menu

2. In the Arduino IDE Library Manager, search for and install the following additional library:
  * https://github.com/adafruit/Adafruit_NeoPixel

3. Download and install the ESP8266FS Tool as described [here](http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html)

4. Clone this Git repository

5. Rename Config.h.example to Config.h file, and change the following:
  * The IP address. It is recommended you use a fixed IP address, since this will make it easier to point your web browser at the right place. You may need to configure your router to keep certain addresses free, then choose one of these addresses as the IP address for your NodeMCU
  * The gateway and subnet should be set as required by your router
  * The ssid and password should be set to the credentials used to connect to your WiFi
  * Change the number of pixels as required

6. Compile and upload the WebLight.ino project

7. Select Tools -> ESP8266 Sketch Data Upload to upload the web server files

8. Test by pointing a web browser at the IP address you chose for the NodeMCU

## The Web Server

The web server introduces the concept of an "HTMLX" file:

* HTMLX files may contain tags surrounded by [square brackets]
* Each tag is associated with a method which is registered with the server
* The method returns a string, which is inserted into the HTML. It may also carry out any other activity it wants

## The Web Light

A simple HTMLX page which displays the current status of the light, and includes links to turn the light on or off

## Planned Enhancements

* Modify the web server so that it supports requests for JSON-formatted data
* Modify the web page so that submits a JSON request when the light is turned on/off rather than re-loading the whole page
* Turn the web server into a proper service
* Add support for hardware switches to turn the light on and off
