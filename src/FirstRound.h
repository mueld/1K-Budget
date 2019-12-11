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
enum Turn_State
{
    Verify,
    Turn_,
    Idle
};

class FirstRound : public ToF_Interface
{
private:
    FirstRound_State State = FirstRound_Start;
    DrivesController *DriveController;
    ToF *Sensor;
    Objectdetection *Camera;
    Align *Align_;
    Turn_State State_turn = Verify;
    int Turns = 0;
    int Sensor_Data[4];

public:
    void ExecuteStateMachine();
    void Setup(DrivesController *Instance, ToF *ToFs, Objectdetection *PInstance, Align *AlignInstance);
    void Turn(int Distance);
    void update(int Table[4]);
    FirstRound_State activeState();
};

#endif