#include "objectdetection.h"
#include "ToF.h"
#include "Align.h"

void Align::Setup(DrivesController *Controller, ToF *Sensors)
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
        if (Sensor->measureVR.RangeMilliMeter % Sensor->measureHR.RangeMilliMeter >= 4 && Sensor->measureVR.RangeMilliMeter > Sensor->measureHR.RangeMilliMeter)
        {
            DriveController->TurnLeft(25);
        }
        else if (Sensor->measureHR.RangeMilliMeter % Sensor->measureVR.RangeMilliMeter >= 2)
        {
            DriveController->TurnRight(25);
        }
        else
        {
            DriveController->Stay();
            State = Align_Idle;
        }
        break;
    }
}