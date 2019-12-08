#include "ToF.h"
#include "objectdetection.h"
#include "Align.h"
#ifndef FirstRound_h
#define FirstRound_h

enum FirstRound_State
{
    FirstRound_Start,
    FirstRound_Move,
    FirstRound_Turn,
    FirstRound_Align,
    FirstRound_Idle,
    FirstRound_Finish
};
enum Turn
{
    Verify,
    Turn,
    Idle
};


class FirstRound
{
private:
    FirstRound_State State = FirstRound_Start;
    DrivesController *DriveController;
    ToF *Sensor;
    Objectdetection *Camera;
    Align *Align_;
    Turn State_turn = Verify;
    int Turns = 0;

public:
    void ExecuteStateMachine();
    void Setup(DrivesController *Instance, ToF *ToFs, Objectdetection *PInstance, Align *AlignInstance);
    bool Turn(int Distance);
    FirstRound_State activeState();

};

#endif