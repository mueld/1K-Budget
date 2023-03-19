#include "FirstRoundState.h"
#include "ToF.h"
#include "objectdetection.h"

int FirstRoundState::ActiveState()
{
    return State;
}
void FirstRoundState::Setup(DrivesController *Instance, ToF *ToFs, IModuleState *IModuleState_, Align *AlignInstance)
{
    DriveController = Instance;
    Sensor = ToFs;
    this->IModuleState_ = IModuleState_;
    Align_ = AlignInstance;
}

void FirstRoundState::ExecuteStateMachine()
{
    switch (State)
    {
    case FirstRoundState_Start:
    //Aus Startposition fahren
        starttime = millis();
        DriveController->MoveForward(100);
        State = FirstRoundState_Wait;
        OldState = FirstRoundState_Start;
        break;
    case FirstRoundState_Wait:
        if (millis() - starttime > 2500)
        {
            DriveController->Stay();
            State = FirstRoundState_Align;
        }
        break;
        case FirstRoundState_Align:
            Serial.println("FirstRoundState Align");
            if(Turns == 3)
            {
                Serial.println("Align 320 Turns= 3 ");
                Align_->Execute(320);
                return;
            }

            if (OldState == FirstRoundState_Start)
            {
                Align_->Execute(40);
            }
            else
            {
                if (Turns == 3)
                {
                    State = FirstRoundState_Move;
                    OldState = FirstRoundState_Align;
                    return;
                }
                
                Align_->Execute(32);
            }

        if (Align_->ActiveState() == Align_Idle)
        {
            State = FirstRoundState_Finish;
            OldState = FirstRoundState_Align;
        }
        break;
    case FirstRoundState_Move:
        Serial.println("FirstRoundState Move");
        DriveController->MoveForward(80);
        State = FirstRoundState_Idle;

        break;

    case FirstRoundState_Idle:
        Serial.println("FirsrroundIdle");
        if (Sensor_Data[4] < 200)
        {
             starttime = millis();
             DriveController->MoveLeft(100);
             State = FirstRoundState_Prepare;
        }
         else
         {
            State = FirstRoundState_Turn;
         }    
        break;
    case FirstRoundState_FoundObject:
        State = FirstRoundState_Turn;
        break;

        case FirstRoundState_Turn:
        if(Turns < 2)
        {
            Turn(150);
        }
       else
       {
           Turn(350);
       }
        if(State_turn == Idle)
        {
            if(Turns != 3)
            {
            State = FirstRoundState_Align;
            }
            else
            {
                State = FirstRoundState_Finish;
            }
            
        }
        break;
        case FirstRoundState_Prepare:
            if (millis()-starttime > 1500 && prepare == false)
            {
                DriveController->MoveRight(100);
                starttime = millis();
                prepare = true;
            }
            if (millis() - starttime > 1500 && prepare == true)
            {
                DriveController->Stay();
                prepare = false;
                State = FirstRoundState_FoundObject;
            }
            break;
        case FirstRoundState_Finish:
            Turns = 0;
            State = FirstRoundState_Start;
            break;
    }
}

void FirstRoundState::Turn(int Distance)
{
    Serial.print("TState Turn.");
    Serial.println(State_turn);
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
void FirstRoundState::update(int Table[5]) {
    for (int i = 0; i < 5; i++)
    {
        if (Table[i] != 8190)
        {
            Sensor_Data[i] = Table[i];
        }
        
        
    }
    
}
