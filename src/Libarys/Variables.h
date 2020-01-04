#include "../MKR1000Communication.h"


#ifndef Variables_h
#define Variables_h
#define DEBUG

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

ToF Sensors;
FirstRound Round;
Pixy2 Pixyinstance;
Objectdetection ObjectdetectionInstance;
DrivesController DrivesControllerInstance;
Collect CollectInstance;
Unload UnloadInstance;
Parking ParkingInstance;
Align AlignInstance;
MKR1000Communication MKR100Instance;

Processstate State = Process_Searching;
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
        State = Process_ObjectFound;
    }
}
void Execute_Idle()
{
     if (MKR100Instance.Read() == true)
    {
        State = Process_FirstRound;
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
void ExecuteCollect()
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

#endif