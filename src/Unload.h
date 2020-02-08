#ifndef Unload_h
#define Unload_h
#include "Collect.h"
enum Unload_State
{
    Unload_Start,
    Unload_MovingHome,
    Unload_MovetoPosition,
    Unload_Idle,
    Unload_Crash
};

class Unload: public IModuleState
{
    private:
    Unload_State State;
    DrivesController *Controller;
    unsigned long int starttime = 0;
    bool Pushposition = false;

public:
    void Setup(DrivesController *DriveController);
    void ExecuteUnload();
    int ActiveState();
};

#endif