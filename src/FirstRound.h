#include "ToF.h"
#include "objectdetection.h"

#ifndef FirstRound_h
#define FirstRound_h

enum FirstRound_State
{
    FirstRound_Start,
    FirstRound_Move,
    FirstRound_Turn,
    FirstRound_Adjust,
    FirstRound_Idle,
    FirstRound_Finish
};
enum Adjust
{
    VerifyDistance,
    Adjust_Parallel,
    VerifyDistance2
};

class FirstRound
{
private:
    FirstRound_State State = FirstRound_Start;
    Adjust State_Adjust = VerifyDistance;
    DrivesController *DriveController;
    ToF *Sensor;
    Objectdetection *Camera;

    int Turns = 0;

public:
    void ExecuteStateMachine();
    void Setup(DrivesController *Instance, ToF *ToFs, Objectdetection *PInstance);
    FirstRound_State activeState();

};

#endif