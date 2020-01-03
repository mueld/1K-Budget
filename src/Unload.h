#ifndef Unload_h
#define Unload_h
#include "Collect.h"
enum Unload_State
{
    Unload_MoveToPosition,
    Unload_ContainerInPosition,
    Unload_ConatainerStartPostion,
    Unload_Idle
};

class Unload: public IModuleState
{
    private:
    Unload_State State;
    DrivesController *Controller;

public:
    void Setup(DrivesController *DriveController);
    void ExecuteUnload();
    int ActiveState();
};

#endif