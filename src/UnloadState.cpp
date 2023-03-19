#include "UnloadState.h"

void UnloadState::Setup(DrivesController *DriveController)
{
    Controller = DriveController;
}

void UnloadState::ExecuteUnload()
{
    switch (State)
    {

    case Unload_Start:
    //Beide Achsen auf in Kippposition bringen
    if (Controller->setPosition(Motor_Linear, Position_LinearUnload) && Pushposition == false)
    {
        if (Controller->setPosition(Motor_Rotate, Position_RotatePushCube))
        {
            Pushposition = true;
            }     
    }
    if (Pushposition == true)
    {
        if (Controller->setPosition(Motor_Linear, Position_LinearPushCube))
        {
            Pushposition == false;
            State = Unload_MovetoPosition;
        }
        
    }
    
        break;
    case Unload_MovetoPosition:
        if (Controller->setPosition(Motor_Linear, Position_LinearUnload))
        {
            if (Controller->setPosition(Motor_Rotate, Position_Rotate))
            {
                State = Unload_Crash;
                Controller->MoveLeft(255);
                starttime = millis();
            }
    }
        break;
    case Unload_Crash:
        if (millis()-starttime > 7000)
        {
            Controller->Stay();
            State = Unload_MovingHome;
        }
        
        break;
     case Unload_MovingHome:


             if (Controller->setPosition(Motor_Rotate, Position_RotateMovingHome))
             {
                 if (Controller->setPosition(Motor_Linear, Position_StrokeUT))
                 {
                     State = Unload_Idle;
                 }
             }
        break;

    case Unload_Idle:
        State = Unload_Start;
        break;
    }

}
int UnloadState::ActiveState()
{
    return State;
}