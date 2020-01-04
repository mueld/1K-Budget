
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#ifndef Webserver_h
#define Webserver_h
#define STATE_INDEX 0
#define CUBES_INDEX 1


class Webserver
{
private:
    char SSID[8] = "ZbW-IoT";
    char PWD[7] = "zbwzbw";
    String Response;
    int RXBuffer[2];
    int rxindex = 0;
    HttpClient *Client_;
    int WifiState = WL_IDLE_STATUS;
    String Send;
    bool Start;

public:
    void Reading();
    void sending();
    void Setup(HttpClient *Client_);
    void Summery(const int &State, const int &Cubes);
};
#endif