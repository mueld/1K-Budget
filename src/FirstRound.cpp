#include "FirstRound.h"
#include "ToF.h"
#include "objectdetection.h"

int FirstRound::ActiveState()
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
        if (millis() - starttime > 2500)
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
            State = FirstRound_Finish;
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
        if (Sensor_Data[4] < 200)
        {
             starttime = millis();
             DriveController->MoveLeft(100);
             State = FirstRound_Prepare;
        }
         else
         {
            State = FirstRound_Turn;
         }    
        break;
    case FirstRound_FoundObject:
        State = FirstRound_Turn;
        break;

        case FirstRound_Turn:
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
            State = FirstRound_Align;
            }
            else
            {
                State = FirstRound_Finish;
            }
            
        }
        break;
        case FirstRound_Prepare:
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
                State = FirstRound_FoundObject;
            }
            break;
        case FirstRound_Finish:
            Turns = 0;
            State = FirstRound_Start;
            break;
    }
}

void FirstRound::Turn(int Distance)
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
void FirstRound::update(int Table[5]) {
    for (int i = 0; i < 5; i++)
    {
        if (Table[i] != 8190)
        {
            Sensor_Data[i] = Table[i];
        }
        
        
    }
    
}
