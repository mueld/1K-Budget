#include "Unload.h"

void Unload::Setup(DrivesController *DriveController)
{
    Controller = DriveController;
}

void Unload::ExecuteUnload()
{


    switch (State)
    {

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