#include "../Parking.h"
#include "../Webserver.h"
#include <ArduinoHttpClient.h>
#ifndef Variables_h
#define Variables_h
#define DEBUG
/*
char serverAddress[] = "192.168.1.125";
int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);*/
ToF Sensors;
FirstRound Round;
Pixy2 Pixyinstance;
Objectdetection ObjectdetectionInstance;
DrivesController DrivesControllerInstance;
/* Collect CollectInstance;
Unload UnloadInstance;
Parking ParkingInstance;*/
Align AlignInstance;
//Webserver WsInstance;

Processstate State;
Processstate OldState;
int Cubes = 6;


void DrivesControllerEncoderLinear()
{
    DrivesControllerInstance.ReadEncoderLinear();
}
void DrivesControllerEncoderRotate()
{
    DrivesControllerInstance.ReadEncoderRotate();
}
void Execute_FirstRound()
{
    ObjectdetectionInstance.FirstRound();
    if (ObjectdetectionInstance.ActiveState() == Objectstate_found)
    {
        State = Process_ObjectFound;
    }
    else if (Round.activeState() == FirstRound_Finish)
    {
        State = Process_Idle;
    }

    else if (Round.activeState() != FirstRound_Finish)
    {
        Round.ExecuteStateMachine();
    }
}

void Execute_Searching()
{
    ObjectdetectionInstance.ExecuteStateMachine();
    if (ObjectdetectionInstance.ActiveState() == Objectstate_found)
    {
        State = Process_Collect;
    }
}
/*void Execute_Idle()
{
     if (StartButton == true)
    {
        State = Process_Start;
    }
    if (Round.activeState() != FirstRound_Finish)
    {
        State = Process_FirstRound;
    }
    else if (Cubes == 6)
    {
        State = Process_Parking;
    }
    else
    {
        State = Process_Searching;
    }
}
void ExectueCollect()
{
    if (CollectInstance.CollectThatShit())
    {
        State = Process_Idle;
    }
}
void ExecuteUnload()
{
    if (UnloadInstance.ActiveState() == Unload_Idle)
    {
        State = Process_UnloadedCubes;
    }
}
void ExectueParking()
{
    if (ParkingInstance.ActiveState() == Parking_Idle)
    {
         State = Process_Unload;
    }
}
*/
#endif