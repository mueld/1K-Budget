#include "../Collect.h"

#ifndef Variables_h
#define Variables_h

ToF Sensors;
FirstRound Round;
Pixy2 Pixyinstance;
Objectdetection ObjectdetectionInstance;
DrivesController DrivesControllerInstance;
Collect CollectInstance;

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
void FirstRound()
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

void Searching()
{
    ObjectdetectionInstance.ExecuteStateMachine();
    if (ObjectdetectionInstance.activestate() == Objectstate_found)
    {
        State = Process_Collect;
    }
}

#endif