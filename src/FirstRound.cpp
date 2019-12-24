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
    Sensor->Reading();
    Serial.print("State:");
    Serial.println(State);
    switch (State)
    {
    case FirstRound_Start:
        Serial.print("Sensordata VR:");
        Serial.println(Sensor_Data[2]);
        if (Sensor_Data[2] > 670 && Sensor_Data[1] <70)
        {
            Serial.println("start vorwaärts");
            DriveController->MoveForward(70);
        }
        else if (Sensor_Data[0] >= 30 && Sensor_Data[2]<670)
        {
            Serial.println("start rechts");
            DriveController->MoveRight(80);
        }
        else
        {
            
            DriveController->Stay();
            State = FirstRound_Align;
        }
        break;

    case FirstRound_Align:
        Align_->Execute(30);
        
        if(Align_->ActiveState() == Align_Idle)
        {
            State = FirstRound_Idle;
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
        else
        {
            State = FirstRound_Align;
        }
        
        break;

    case FirstRound_Turn:
        if(Turns <2)
        {
            Turn(70);
        }
       else
       {
           Turn(810);
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
            DriveController->TurnLeft(50);
        }
        else 
        {
            State_turn = Idle;
        }
            break;
    
    case Turn_:

        if (Sensor_Data[2] <= 900 )
        {
            DriveController->TurnLeft(50);
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
