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
    //Aus Startposition fahren
        starttime = millis();
        DriveController->MoveForward(100);
        State = FirstRound_Wait;
        OldState = FirstRound_Start;
        break;
    case FirstRound_Wait:
        if (millis() - starttime > 2200)
        {
            DriveController->Stay();
            State = FirstRound_Align;
        }
        break;
        case FirstRound_Align:
            Serial.println("FirstRound Align");
            if(Turns == 3)
            {
                Serial.println("Align 320 Turns= 3 ");
                Align_->Execute(320);
                return;
            }

            if (OldState == FirstRound_Start)
            {
                Align_->Execute(40);
            }
            else
            {
                if (Turns == 3)
                {
                    State = FirstRound_Move;
                    OldState = FirstRound_Align;
                    return;
                }
                
                Align_->Execute(32);
            }

        if (Align_->ActiveState() == Align_Idle)
        {
            State = FirstRound_Move;
            OldState = FirstRound_Align;
        }
        break;
    case FirstRound_Move:
        Serial.println("Firstround Move");
        DriveController->MoveForward(80);
        State = FirstRound_Idle;

        break;

    case FirstRound_Idle:
        Serial.println("FirsrroundIdle");
        if (Sensor_Data[4] > 200)
        {
            State = FirstRound_Turn;
        }
         else
         {
             State = FirstRound_FoundObject;
         }    
        break;
    case FirstRound_FoundObject:
        State = FirstRound_Turn;
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
            if(Turns != 3)
            {
            State = FirstRound_Align;
            }
            else
            {
                State = FirstRound_Finish;
            }
            
        }
    }
}

void FirstRound::Turn(int Distance)
{
    Serial.println("Turn");
    switch (State_turn)
    {
    case Verify:
        if (Sensor_Data[2] <= Distance)
        {
            State_turn = Turn_;
            DriveController->TurnLeft(80);
            starttime = millis();
        }
        else 
        {
            State_turn = Idle;
        }
            break;
    
    case Turn_:
        if (millis() - starttime < 3300 )
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
void FirstRound::update(int Table[5]) {
    for (int i = 0; i < 5; i++)
    {
        if (Table[i] != 8190)
        {
            Sensor_Data[i] = Table[i];
        }
        
        
    }
    
}
