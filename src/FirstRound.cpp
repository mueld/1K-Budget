#include "FirstRound.h"
#include "ToF.h"
#include "objectdetection.h"

FirstRound_State FirstRound::activeState()
{
    return State;
}
void FirstRound::Setup(DrivesController *Instance, ToF *ToFs, Objectdetection *PInstance)
{
    DriveController = Instance;
    Sensor = ToFs;
    Camera = PInstance;
}
void FirstRound::ExecuteStateMachine()
{
    switch (State)
    {
    case FirstRound_Start:
        Sensor->Reading();
        if (Sensor->measureFront.RangeMilliMeter <= 1000)
        {
            DriveController->MoveForward(100);
        }
        else if (Sensor->measureVR.RangeMilliMeter >= 10)
        {
            DriveController->MoveRight(50);
        }
        else
        {
            DriveController->Stay();
            State = FirstRound_Adjust;
        }
        break;

    case FirstRound_Adjust:
        Sensor->Reading();

        switch (State_Adjust)
        {

        case VerifyDistance:
            if (Turns == 2)
            {
                State_Adjust = VerifyDistance2;
                return;
            }

            else if (Sensor->measureVR.RangeMilliMeter > 15)
            {
                DriveController->MoveRight(25);
            }
            else if (Sensor->measureVR.RangeMilliMeter < 5)
            {
                DriveController->MoveLeft(25);
            }
            else
            {
                DriveController->Stay();
                State_Adjust = Adjust_Parallel;
            }
            break;

        case VerifyDistance2:
            if (Sensor->measureLEFT.RangeMilliMeter < 740)
            {
                DriveController->MoveRight(25);
            }
            else if (Sensor->measureLEFT.RangeMilliMeter > 745)
            {
                DriveController->MoveLeft(25);
            }
            else
            {
                DriveController->Stay();
                State_Adjust = Adjust_Parallel;
            }
            break;

        case Adjust_Parallel:
            if (Sensor->measureVR.RangeMilliMeter % Sensor->measureHR.RangeMilliMeter >= 4 && Sensor->measureVR.RangeMilliMeter > Sensor->measureHR.RangeMilliMeter)
            {
                DriveController->TurnLeft(25);
            }
            else if (Sensor->measureHR.RangeMilliMeter % Sensor->measureVR.RangeMilliMeter >= 2)
            {
                DriveController->TurnLeft(25);
            }
            else
            {
                DriveController->Stay();
                State_Adjust = VerifyDistance;
                State = FirstRound_Turn;
            }
            break;
        }

    case FirstRound_Move:
        Sensor->Reading();

        if (Camera->activestate() != Objectstate_found)
        {
            DriveController->MoveForward(50);
            State = FirstRound_Adjust;
        }
        else
        {
            DriveController->Stay();
            State = FirstRound_Idle;
        }
        break;

    case FirstRound_Idle:
        State = FirstRound_Move;
        break;

    case FirstRound_Turn:
        Sensor->Reading();

        if (Sensor->measureFront.RangeMilliMeter <= 50 || (Sensor->measureFront.RangeMilliMeter <= 900 &&Turns = 2))
        {
            DriveController->Stay();
        }
        else
        {
            State = FirstRound_Move;
            return;
        }

        if (Sensor->measureFront.RangeMilliMeter <= 900 || Sensor->measureHR.RangeMilliMeter % Sensor->measureVR.RangeMilliMeter > 6)
        {
            DriveController->TurnLeft(30);
        }

        else
        {
            DriveController->Stay();
            Turns++;
            State = FirstRound_Adjust;
        }
    }
}
