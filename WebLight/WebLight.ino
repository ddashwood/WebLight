#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FS.h>

#include "Config.h"
#include "htmlxHandler.h"
#include "lightController.h"

static const IPAddress ip IP;
static const IPAddress gateway GATEWAY;
static const IPAddress subnet SUBNET;

static const char* ssid = SSID;
static const char* password = PASSWORD;

ESP8266WebServer server(80);
htmlxHandler theHandler = htmlxHandler(&server);

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  // WiFi
  connectWiFi (ssid, password, ip, gateway, subnet);

  // SPIFFS file system
  SPIFFS.begin();

  // And finally, the web server.
  // Three types of handlers:
  
  // 1: redirect to index.html
  server.on("/", []() {
    server.sendHeader("Location", String("/index.htmlx"), true);
    server.send ( 302, "text/plain", "");
  } );
  server.on("/index.html", []() {
    server.sendHeader("Location", String("/index.htmlx"), true);
    server.send ( 302, "text/plain", "");
  } );
  

  // 2: handle htmlx files
  theHandler.on ("on", SwitchOn);
  theHandler.on ("off", SwitchOff);
  theHandler.on ("light", Switch);
  theHandler.on ("links", Links);
  server.addHandler(&theHandler);

  // 3: The static server deals with all other URIs
  server.serveStatic("/", SPIFFS, "/");

  server.begin();
  Serial.println("Server listening");
}

void loop() {
  server.handleClient();
}

void connectWiFi(const char *ssid, const char *password, IPAddress ip, IPAddress gateway, IPAddress submask)
{
  WiFi.config(ip, gateway, submask);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Subnet: ");
  Serial.println(WiFi.subnetMask());
}

