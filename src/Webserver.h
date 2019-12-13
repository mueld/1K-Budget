#include "Parking.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#ifndef Webserver_h
#define Webserver_h
enum Processstate
{
    Process_Start = 0,
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
    String SSID = "ZbW-IoT";
    HttpClient *Client_;
    int SendState;
    int Cubes;
    String Send;

public:
    void sending();
    int ActiveState();
    void Setup(Processstate &SendState, int &Cubes, HttpClient *Client_);
    void Summery(const Processstate SendState, const int Cubes);
};
#endif