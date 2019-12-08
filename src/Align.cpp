#include "objectdetection.h"
#include "ToF.h"
#include "Align.h"

void Align::Setup(DrivesController *Controller, ToF *Sensors)
{
    this->Controller = Controller;
    this->Sensor = Sensors;
}

void Align::Execute(int Distance)
{
    switch (State)
    {
    case Align_Distance:
        if (Sensor->measureVR.RangeMilliMeter > Distance)
        {
            Controller->MoveRight(25);
        }
        else if (Sensor->measureVR.RangeMilliMeter < Distance)
        {
            Controller->MoveLeft(25);
        }
        else
        {
            Controller->Stay();
            State = Align_Parallel;
        }
        break;
    
    case  Align_Parallel:
        if (Sensor->measureVR.RangeMilliMeter % Sensor->measureHR.RangeMilliMeter >= 4 && Sensor->measureVR.RangeMilliMeter > Sensor->measureHR.RangeMilliMeter)
        {
            Controller->TurnLeft(25);
        }
        else if (Sensor->measureHR.RangeMilliMeter % Sensor->measureVR.RangeMilliMeter >= 2)
        {
            Controller->TurnRight(25);
        }
        else
        {
            Controller->Stay();
            State = Align_Idle;
        }
        break;
    }
}
Align_State Align::ActiveState()
{
    return State;
}