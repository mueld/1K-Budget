#include "objectdetection.h"
#include "ToF.h"
#include "Align.h"

void Align::Setup(Objectdetection &Camera, DrivesController &Controller, ToF &Sensors)
{
    this->Camera = Camera;
    this->Controller = Controller;
    this->Sensors = Sensors;
}

void Align::Execute(int Distance)
{
    switch (State)
    {
    case Align_Distance:
        if (Sensor->*measureVR.RangeMilliMeter > Distance)
        {
            DriveController->MoveRight(25);
        }
        else if (Sensor->*measureVR.RangeMilliMeter < Distance)
        {
            DriveController->MoveLeft(25);
        }
        else
        {
            DriveController->Stay();
            State = Align_Parallel;
        }
        break;
    
    case  Align_Parallel:
        break;
    }
}