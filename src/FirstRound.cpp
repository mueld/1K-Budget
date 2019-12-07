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
    Sensor->Reading();
    switch (State)
    {
    case FirstRound_Start:
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
            State = FirstRound_Align;
        }
        break;

    case FirstRound_Align:
        /*Align.Execute(10);
        
        if(Align.ActiveState() == Align_Idle)
        {
            State = FirstRound_Move;
        }
        */
        break;
    case FirstRound_Move:

        if (Camera->activestate() != Objectstate_found)
        {
            DriveController->MoveForward(50);
            State = FirstRound_Align;
        }
        else
        {
            DriveController->Stay();
            State = FirstRound_Turn;
        }
        break;

    case FirstRound_Idle:
        State = FirstRound_Move;
        break;

    case FirstRound_Turn:
        if(Turn <2)
        {
            Turn(10);
        }
       else
       {
           Turn(780);
       }
        if(State_turn == Idle)
        {
            State = FirstRound_Idle;
        }
    }
}

void FirstRound::Turn(int Distance)
{
    switch (State_turn)
    {
    case Verify:
        if (Sensor->*measureFront.RangeMilliMeter <= Distance)
        {
            State_turn = Turn;
            DriveController->TurnLeft();
        }
        else 
        {
            State_turn = Idle;
        }
            break;
    
    case Turn:

        if (Sensor->measureFront.RangeMilliMeter <= 900 )
        {
            DriveController->TurnLeft(30);
        }
        else
        {
            DriveController->Stay();
            Turns++;
            Statet_turn = Idle;
            
        }
        break;
    case Idle:
        State_turn = Verify;
        break;
    }
}





   
