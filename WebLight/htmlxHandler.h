#ifndef HTMLX_HANDLER_H
#define HTMLX_HANDLER_H

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

typedef String (*handler)(ESP8266WebServer *server);

struct handlerDetails
{
  struct handlerDetails *next;
  String handlerText;
  handler theHandler;
};


class htmlxHandler : public RequestHandler {
  public:
    htmlxHandler(ESP8266WebServer *server);
    bool canHandle(HTTPMethod method, String uri) override;
    bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override;
    void on(String handlerText, handler theHandler);
  private:
    struct handlerDetails *firstHandler = 0;
    ESP8266WebServer *theServer;
};

#endif

