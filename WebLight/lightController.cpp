#include <Adafruit_NeoPixel.h>

#include "lightController.h"
#include "Config.h"

#define PIN 4 // Virtual pin 4 is equivalient to physical pin 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800);
bool currentValue = false;

/* Return some HTML that shows the user the current light value
 */
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

/* Set the currentValue variable correctly - should be called at the start of each handler
 *  if there's a chance the value parameter will be passed with the request
 */
void setCurrentValue(ESP8266WebServer *server)
{
  if (server->arg("value")=="on")
  {
    currentValue = true;
  }
  else if (server->arg("value")=="off")
  {
    currentValue = false;
  }
  // If the value parameter is not set, leave the current value is it is
}

/* Set the light based on the currentValue
 */
void setLights()
{
  int i;
  
  strip.begin();
  for (i = 0; i < PIXELS; i++)
  {
    if (currentValue)
      strip.setPixelColor(i, 255, 255, 255);
    else
      strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

/* Handler connected to the [links] tag - show the relevant link to the user
 * Expects the value parameter to be passed at the same time
 * (N.b. if this is used in conjunction with the [switch] tag, the value parameter
 * will be passed as expected. But that may not be the case if this is used with
 * the [on] or [off] tags)
 */
String Links(ESP8266WebServer *server)
{
  setCurrentValue(server);
  if (currentValue)
  {
    return String("<a href=index.htmlx?value=off>Switch off</a>");
  }
  else
  {
    return String("<a href=index.htmlx?value=on>Switch on</a>");
  }
}

/* Handler connected to the [on] tag - turns the lights on
 */
String SwitchOn(ESP8266WebServer *server)
{
  currentValue=true;
  setLights();
  return getCurrentValue();
}

/* Handler connected to the [off] tag = turns the lights off
 */
String SwitchOff(ESP8266WebServer *server)
{
  currentValue = false;
  setLights();
  return getCurrentValue();
}

/* Handler connected to the [switch] tag - switches the lights on or off.
 * Expects the value parameter to be passed at the same time
 */
String Switch(ESP8266WebServer *server)
{
  setCurrentValue(server);
  setLights();
  return getCurrentValue();
}

