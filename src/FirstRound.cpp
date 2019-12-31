#include "FirstRound.h"
#include "ToF.h"
#include "objectdetection.h"

FirstRound_State FirstRound::activeState()
{
    return State;
}
void FirstRound::Setup(DrivesController *Instance, ToF *ToFs, IModuleState *IModuleState_, Align *AlignInstance)
{
    DriveController = Instance;
    Sensor = ToFs;
    this->IModuleState_ = IModuleState_;
    Align_ = AlignInstance;
}

void FirstRound::ExecuteStateMachine()
{
    switch (State)
    {
    case FirstRound_Start:
        starttime = millis();
        DriveController->MoveForward(70);
        State = FirstRound_Align;
        OldState = FirstRound_Start;
        break;

    case FirstRound_Align:
        if(millis()-starttime > 2500 && OldState==FirstRound_Start)
        {
           Align_->Execute(50); 
        }
        else
        {
    Align_->Execute(28);
        }

        if (Align_->ActiveState() == Align_Idle)
        {
            State = FirstRound_Move;
            OldState = FirstRound_Align;
        }
        break;
    case FirstRound_Move:
            DriveController->MoveForward(70);
            State = FirstRound_Idle;

            break;

    case FirstRound_Idle:
        if (IModuleState_->ActiveState() != Objectstate_found)
        {
            State = FirstRound_Turn;
        }
        
        break;

    case FirstRound_Turn:
        if(Turns <2)
        {
            Turn(140);
        }
       else
       {
           Turn(350);
       }
        if(State_turn == Idle)
        {
            State = FirstRound_Align;
        }
    }
}

void FirstRound::Turn(int Distance)
{
    switch (State_turn)
    {
    case Verify:
        if (Sensor_Data[2] <= Distance)
        {
            Align_->Execute(50);
            if (Align_->ActiveState() == Align_Idle)
            {
                State_turn = Turn_;
            DriveController->TurnLeft(80);
            }
        }
        else 
        {
            State_turn = Idle;
        }
            break;
    
    case Turn_:

        if (Sensor_Data[2] <= 560 )
        {
            DriveController->TurnLeft(80);
        }
        else
        {
            DriveController->Stay();
                Turns++;
                State_turn = Idle;
        }
        break;
    case Idle:
        State_turn = Verify;
        break;
    }
}
void FirstRound::update(int Table[4]) {
    for (int i = 0; i < 4; i++)
    {
        if (Table[i] != 8190)
        {
            Sensor_Data[i] = Table[i];
        }
        
        
    }
    
}
