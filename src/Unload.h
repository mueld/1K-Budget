#ifndef Unload_h
#define Unload_h
#include "Collect.h"
enum Unload_State
{
    Unload_Start,
    Unload_MovingHome,
    Unload_Idle
};

class Unload: public IModuleState
{
    private:
    Unload_State State;
    DrivesController *Controller;
    unsigned long int starttime = 0;

public:
    void Setup(DrivesController *DriveController);
    void ExecuteUnload();
    int ActiveState();
};

#endif