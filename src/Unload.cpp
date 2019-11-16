#include "Unload.h"

void Unload::Setup(DrivesController *DriveController, ToF *Sensoren)
{
    Controller = DriveController;
    Sensors = Sensoren;
}

bool Unload::ExecuteUnload()
{
    bool result = false;

    switch (State)
    {
    case Unload_MoveToPosition:
        
        break;

    case Unload_ContainerInPosition:
        break;

    case Unload_ConatainerStartPostion:

        result = true;
        return result;
        break;

    case Unload_Idle:
        State = Unload_MoveToPosition;
        break;
    }
    return result;
}