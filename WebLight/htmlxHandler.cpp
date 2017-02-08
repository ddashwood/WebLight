#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include "htmlxHandler.h"


// Constructor
htmlxHandler::htmlxHandler(ESP8266WebServer *server) {
  theServer = server;
}


// Set a callback
void htmlxHandler::on(String handlerText, handler theHandler) {
  handlerDetails *newHandler = (handlerDetails*) malloc(sizeof(handlerDetails));
  newHandler->next = firstHandler;
  newHandler->handlerText = handlerText;
  newHandler->theHandler = theHandler;

  firstHandler = newHandler;
}


// Override this method from the base class - determines whether we can handle this file
// If not, the web server class will return a Not Found message
bool htmlxHandler::canHandle(HTTPMethod method, String uri) {
  // We only handle GET requests for .htmlx files
  if (method != HTTP_GET || !uri.endsWith(".htmlx")) {
    return false;
  }
  return true;
}

// Handle a request from a browser
bool htmlxHandler::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
  Serial.print("Looking for file: ");
  Serial.println(requestUri);

  File f = SPIFFS.open(requestUri, "r");
  if (!f)
  {
    Serial.println("  Not found");
    return false; // Returning false here results in the web server sending a Not Found message
  }

  // We've found the file - now load it into memory for processing
  String s = f.readString();

  // Loop through all the handlers, and check each of them
  struct handlerDetails *currentHandler;
  currentHandler = firstHandler;
  String text;
  while (currentHandler)
  {
    text = String("[") + currentHandler->handlerText + String("]");
    Serial.print("Searching for text: ");
    Serial.println(text);
    if (s.indexOf(text) != -1) {
      s.replace(text, currentHandler->theHandler(theServer));
    }

    currentHandler = currentHandler->next;
  }

  // And send it to the browser
  server.send(200, "text/html", s);
    
  return true;
} 

