#include "Parking.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#ifndef Webserver_h
#define Webserver_h
enum Processstate
{
    Process_Waiting = 0,
    Process_Searching = 2,
    Process_ObjectFound = 3,
    Process_Collect = 4,
    Process_CollectedCube = 5,
    Process_Unload = 7,
    Process_Parking = 6,
    Process_UnloadedCubes = 8,
    Process_FirstRound = 1,
    Process_Idle = 10,
    Process_Error = 11,
    Process_Finish = 9
};

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