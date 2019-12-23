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
void FirstRound::Print_State()
{
    Serial.println(IModuleState_->ActiveState());
}
void FirstRound::ExecuteStateMachine()
{
    Sensor->Reading();
    switch (State)
    {
    case FirstRound_Start:
        if (Sensor_Data[2] >= 660)
        {
                DriveController->MoveForward(100);
        }
        else if (Sensor_Data[0] >= 10)
        {
            SendDebugFirstround("660 erreicht jetzt nacht rechts");
            DriveController->MoveRight(200);
        }
        else
        {
            SendDebugFirstround("startposition erreicht");
            DriveController->Stay();
            State = FirstRound_Align;
        }
        break;

    case FirstRound_Align:
        Align_->Execute(10);
        
        if(Align_->ActiveState() == Align_Idle)
        {
            State = FirstRound_Idle;
        }
        break;
    case FirstRound_Move:
            DriveController->MoveForward(50);
            State = FirstRound_Align;

            break;

    case FirstRound_Idle:
        if (IModuleState_->ActiveState() != Objectstate_found)
        {
            State = FirstRound_Turn;
        }
        else
        {
            State = FirstRound_Idle;
        }
        
        break;

    case FirstRound_Turn:
        if(Turns <2)
        {
            Turn(10);
        }
       else
       {
           Turn(780);
       }
        if(State_turn == Idle)
        {
            State = FirstRound_Move;
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
            State_turn = Turn_;
            DriveController->TurnLeft(30);
        }
        else 
        {
            State_turn = Idle;
        }
            break;
    
    case Turn_:

        if (Sensor_Data[2] <= 900 )
        {
            DriveController->TurnLeft(30);
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
        Sensor_Data[i] = Table[i];
    }
    
}
