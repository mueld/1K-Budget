#include "../Parking.h"

#ifndef Variables_h
#define Variables_h
#define DEBUG

ToF Sensors;
FirstRound Round;
Pixy2 Pixyinstance;
Objectdetection ObjectdetectionInstance;
DrivesController DrivesControllerInstance;
Collect CollectInstance;
Unload UnloadInstance;
Parking ParkingInstance;
Align AlignInstance;

int Cubes;

enum Processstate
{
    Process_Initialize,
    Process_Start,
    Process_Searching,
    Process_Collect,
    Process_Unload,
    Process_Parking,
    Process_FirstRound,
    Process_Idle,
    Process_Error,
    Process_Finish
};


Processstate State;
Processstate OldState;

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
    if (ObjectdetectionInstance.activestate() == Objectstate_found)
    {
        State = Process_Collect;
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
    if (ObjectdetectionInstance.activestate() == Objectstate_found)
    {
        State = Process_Collect;
    }
}
void Execute_Idle()
{
    /* if (StartButton == true)
    {
        State = Process_Start;
    }*/
    if (Round.activeState() != FirstRound_Finish)
    {
        State = Process_FirstRound;
    }
    else if (Cubes == 6)
    {
        State = Process_Unload;
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
    if (UnloadInstance.ExecuteUnload())
    {
        State = Process_Parking;
    }
}
void ExectueParking()
{
    if (ParkingInstance.ExecuteParking())
    {
         State = Process_Idle;
    }
}
#endif