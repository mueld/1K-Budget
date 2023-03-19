#include "ToF.h"
#include "objectdetection.h"
#include "Align.h"
#ifndef FirstRoundState_h
#define FirstRoundState_h

enum FirstRoundState_State
{
    FirstRoundState_Start,
    FirstRoundState_Prepare,
    FirstRoundState_Wait,
    FirstRoundState_Move,
    FirstRoundState_Turn,
    FirstRoundState_Align,
    FirstRoundState_Idle,
    FirstRoundState_FoundObject,
    FirstRoundState_Finish
};
enum Turn_State
{
    Verify,
    Turn_,
    Idle
};

class FirstRoundState : public ToF_Interface, public IModuleState
{
private:
    FirstRoundState_State State = FirstRoundState_Start;
    FirstRoundState_State OldState;
    DrivesController *DriveController;
    ToF *Sensor;
    IModuleState *IModuleState_;
    Align *Align_;
    Turn_State State_turn = Verify;
    int Turns = 0;
    int Sensor_Data[5];
    unsigned int starttime = 0;
    bool prepare = false;

public:
    void ExecuteStateMachine();
    void Setup(DrivesController *Instance, ToF *ToFs, IModuleState *IModuleState_, Align *AlignInstance);
    void Turn(int Distance);
   void Print_State();
   void update(int Table[5]);
   int ActiveState();
};

#endif