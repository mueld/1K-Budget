#include "ToF.h"
#include "objectdetection.h"
#include "Align.h"
#ifndef FirstRound_h
#define FirstRound_h

enum FirstRound_State
{
    FirstRound_Start,
    FirstRound_Prepare,
        FirstRound_Wait,
    FirstRound_Move,
    FirstRound_Turn,
    FirstRound_Align,
    FirstRound_Idle,
    FirstRound_FoundObject,
    FirstRound_Finish
};
enum Turn_State
{
    Verify,
    Turn_,
    Idle
};

class FirstRound : public ToF_Interface, public IModuleState
{
private:
    FirstRound_State State = FirstRound_Start;
    FirstRound_State OldState;
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