#include "ToF.h"
#include "objectdetection.h"

#ifndef FirstRound_h
#define FirstRound_h

enum FirstRound_State
{
    FirstRound_Start,
    FirstRound_Drive,
    FirstRound_Turn,
    FirstRound_Adjust,
    FirstRound_Idle,
    FirstRound_Finish
};
enum Adjust
{
    Adjust_Distance,
    Adjust_Parallel,
    Adjust_Distance2
};

class FirstRound
{
private:
    FirstRound_State State = FirstRound_Start;
    DrivesController *DriveController;
    ToF *Sensor;
    Objectdetection *Camera;
    int Turns;
    Adjust State_Adjust = Adjust_Distance;

public:
    void ExecuteStateMachine();
    void Setup(DrivesController *Instance, ToF *ToFs, Objectdetection *PInstance);
    FirstRound_State activeState();
};

#endif