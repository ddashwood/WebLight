#include <Adafruit_NeoPixel.h>

#include "lightController.h"
#include "Config.h"


#define PIN 4 // Virtual pin 4 is equivalient to physical pin 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800);
bool currentValue = false;

String getCurrentValue()
{
  String value;
  
  if (currentValue)
  {
    value = String("On <img src=\"img/lighton.jpg\" width=50 height=76>");
  }
  else
  {
    value = String("Off <img src=\"img/lightoff.jpg\" width=50 height=76>");
  }
  return value;
}

String Links(ESP8266WebServer *server)
{
  if (currentValue)
  {
    return String("<a href=index.htmlx?value=off>Switch off</a>");
  }
  else
  {
    return String("<a href=index.htmlx?value=on>Switch on</a>");
  }
}

String SwitchOn(ESP8266WebServer *server)
{
  int i;
  
  currentValue=true;
  strip.begin();
  for (i = 0; i < PIXELS; i++)
  {
    strip.setPixelColor(i, 255, 255, 255);
  }
  strip.show();

  return getCurrentValue();
}

String SwitchOff(ESP8266WebServer *server)
{
  int i;
  
  currentValue = false;
  strip.begin();
  for (i = 0; i < PIXELS; i++)
  {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();

  return getCurrentValue();
}

String Switch(ESP8266WebServer *server)
{
  if (server->arg("value")=="on")
  {
    return SwitchOn(server);
  }
  else if (server->arg("value")=="off")
  {
    return SwitchOff(server);
  }
  else
  {
    return getCurrentValue();
  }
}

