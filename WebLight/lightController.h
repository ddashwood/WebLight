#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include <ESP8266WebServer.h>

String SwitchOn(ESP8266WebServer *server);
String SwitchOff(ESP8266WebServer *server);
String Switch(ESP8266WebServer *server);
String Links(ESP8266WebServer *server);
#endif
