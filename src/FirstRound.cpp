#include "FirstRound.h"
#include "ToF.h"
#include "objectdetection.h"

void FirstRound::Setup(DrivesController Instance, ToF ToFs, Objectdetection Pixy)
{
    DriveController = &Instance;
    Sensor = &ToFs;
    Camera = &Pixy;
}
void FirstRound::ExecuteStateMachine()
{
    switch (State)
    {
    case FirstRound_Start:
        Sensor->Reading();
        if (Sensor->measureFront.RangeMilliMeter <= 1000)
        {
            DriveController->setCommand(StraightForward, 100);
        }
        else if (Sensor->measureVR.RangeMilliMeter >= 10)
        {
            DriveController->setCommand(GoRight, 50);
        }
        else
        {
            DriveController->setCommand(Stay, 0);
            State = FirstRound_Adjust;
        }
        break;

    case FirstRound_Adjust:
        Sensor->Reading();

        switch (State_Adjust)
        {

        case Adjust_Distance:
            if (Turns == 2)
            {
                State_Adjust = Adjust_Distance2;
            }

            if (Sensor->measureVR.RangeMilliMeter > 280)
            {
                DriveController->setCommand(GoRight, 25);
            }
            else if (Sensor->measureVR.RangeMilliMeter < 270)
            {
                DriveController->setCommand(GoLeft, 25);
            }
            else
            {
                DriveController->setCommand(Stay, 0);
                State_Adjust = Adjust_Parallel;
            }
            break;

        case Adjust_Distance2:
            if (Sensor->measureVR.RangeMilliMeter > 15)
            {
                DriveController->setCommand(GoRight, 25);
            }
            else if (Sensor->measureVR.RangeMilliMeter < 5)
            {
                DriveController->setCommand(GoLeft, 25);
            }
            else
            {
                DriveController->setCommand(Stay, 0);
                State_Adjust = Adjust_Parallel;
            }
            break;

        case Adjust_Parallel:
            if (Sensor->measureVR.RangeMilliMeter % Sensor->measureHR.RangeMilliMeter >= 2 && Sensor->measureVR.RangeMilliMeter > Sensor->measureHR.RangeMilliMeter)
            {
                DriveController->setCommand(TurnRight, 25);
            }
            else if (Sensor->measureHR.RangeMilliMeter % Sensor->measureVR.RangeMilliMeter >= 2)
            {
                DriveController->setCommand(TurnLeft, 25);
            }
            else
            {
                DriveController->setCommand(Stay, 0);
                State_Adjust = Adjust_Distance;
                State = FirstRound_Drive;
            }

            break;
        }

       
    case FirstRound_Drive:
        Sensor->Reading();

        if (Camera->activestate() != Objectstate_found)
        {
            if (Sensor->measureFront.RangeMilliMeter >= 270 && Turns == 1)
            {
                DriveController->setCommand(Stay, 0);
                State = FirstRound_Turn;
            }

            if (Sensor->measureVR.RangeMilliMeter > 15 || Sensor->measureVR.RangeMilliMeter < 5)
            {
                DriveController->setCommand(Stay, 0);
                State = FirstRound_Adjust;
            }

            if (Sensor->measureFront.RangeMilliMeter >= 50)
            {
                DriveController->setCommand(StraightForward, 100);
            }
            else
            {
                DriveController->setCommand(Stay, 0);
                Turns++;
                State = FirstRound_Turn;
            }
        }
        else
        {
            DriveController->setCommand(Stay, 0);
            State = FirstRound_Idle;
        }
        break;
    case FirstRound_Idle:
        State = FirstRound_Drive;
        break;

    case FirstRound_Turn:
        Sensor->Reading();
        if (Sensor->measureFront.RangeMilliMeter <= 900 || Sensor->measureHR.RangeMilliMeter % Sensor->measureVR.RangeMilliMeter > 2)
        {
            DriveController->setCommand(TurnLeft, 30);
        }

        else
        {
            DriveController->setCommand(Stay, 0);
            Turns++;
            State = FirstRound_Adjust;
        }
    }
}