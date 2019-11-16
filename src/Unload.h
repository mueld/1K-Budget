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

class Unload
{
    private:
    Unload_State State;
    DrivesController *Controller;
    ToF *Sensors;

public:
    void Setup(DrivesController *DriveController, ToF *Sensoren);
    bool ExecuteUnload();
};

#endif