#include "Unload.h"

void Unload::Setup(DrivesController *DriveController, ToF *Sensoren)
{
    Controller = DriveController;
    Sensors = Sensoren;
}

void Unload::ExecuteUnload()
{


    switch (State)
    {
    case Unload_MoveToPosition:
        
        break;

    case Unload_ContainerInPosition:
        break;

    case Unload_ConatainerStartPostion:


        break;

    case Unload_Idle:
        State = Unload_MoveToPosition;
        break;
    }

}
int Unload::ActiveState()
{
    return State;
}