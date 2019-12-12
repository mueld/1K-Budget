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

class Unload:  public ToF_Interface
{
    private:
    Unload_State State;
    DrivesController *Controller;
    ToF *Sensors;
    int Sensor_Data[4];

public:
    void Setup(DrivesController *DriveController, ToF *Sensoren);
    bool ExecuteUnload();
    void update(int Table[4]);
};

#endif