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

Processstate State = Process_Unload;
Processstate OldState;
int Cubes = 0;


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
    if (Round.activeState() == FirstRound_FoundObject )
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
    //  if (MKR100Instance.Read() == true)
    // {
    //     State = Process_FirstRound;
    // }
    // if (Round.activeState() != FirstRound_Finish)
    // {
    //     State = Process_FirstRound;
    // }
     if (Cubes == 3)
    {
        State = Process_Parking;
    }
    else
    {
        Serial.println("STate = Searching");
        State = Process_Searching;
    }
}
void ExecuteCollect()
{
    CollectInstance.CollectThatShit();
    if (CollectInstance.ActiveState() == Collect_Finish)
    {
        Serial.println("Collect finish");
        State = Process_Idle;
        Cubes++;
        Serial.print("Cubes");
        Serial.println(Cubes);
    }
}
void ExecuteUnload()
{
    UnloadInstance.ExecuteUnload();
    if (UnloadInstance.ActiveState() == Unload_Idle)
    {
        State = Process_UnloadedCubes;
    }
}
void ExectueParking()
{
    ParkingInstance.ExecuteParking();
    if (ParkingInstance.ActiveState() == Parking_Idle)
    {
         State = Process_Unload;
    }
}

#endif