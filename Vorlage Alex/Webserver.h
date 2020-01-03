#include "Parking.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#ifndef Webserver_h
#define Webserver_h


class Webserver
{
private:
    char SSID[8] = "ZbW-IoT";
    char PWD[7] = "zbwzbw";
    String Response;
    byte RXBuffer[2];
    int rxindex = 0;
    HttpClient *Client_;
    int WifiState = WL_IDLE_STATUS;
    int SendState;
    int Cubes;
    String Send;
    bool Start;

public:
    void Reading();
    void sending();
    int ActiveState();
    void Setup(HttpClient *Client_);
    void Summery(const Processstate SendState, const int Cubes);
};
#endif