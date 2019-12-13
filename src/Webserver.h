#include "Parking.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#ifndef Webserver_h
#define Webserver_h

enum WebserverState
{
    Webserver_openConnection,
    Webserver_sendValues,
    Webserver_closeConnection,
    Webserver_Idle
};
class Webserver
{
private:
    WebserverState State;
    HttpClient *Client_;
    int *SendState;
    int *Cubes;

public:
    void Execute();
    int ActiveState();
    void Setup(int *SendState, int *Cubes, HttpClient *Client_);
};




#endif