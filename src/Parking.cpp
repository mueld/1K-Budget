#include "Parking.h"
#include "Unload.h"

void Parking::Setup(DrivesController *DriveController, Objectdetection *objectdetection, ToF *Sensors)
{
    Controller = DriveController;
    Detection = objectdetection;
    Sensor = Sensors;
}

void Parking::ExecuteParking()
{
    switch (State)
    {
    case Parking_SearchPosition:
        break;

    case Parking_GotoWall:
        break;
    case Parking_Park:
        break;
    }
}
int Parking::ActiveState()
{
    return State;
}