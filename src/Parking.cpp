#include "Parking.h"
#include "Unload.h"

void Parking::Setup(DrivesController *DriveController, Objectdetection *objectdetection, ToF *Sensors)
{
    Controller = DriveController;
    Detection = objectdetection;
    Sensor = Sensors;
}

bool Parking::ExecuteParking()
{
    bool result = false;
    switch (State)
    {
    case Parking_SearchPosition:
        break;

    case Parking_GotoWall:
        break;
    case Parking_Park:
        result = true;
        return result;
        break;
    }
    return result;
}