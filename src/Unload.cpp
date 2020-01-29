#include "Unload.h"

void Unload::Setup(DrivesController *DriveController)
{
    Controller = DriveController;
}

void Unload::ExecuteUnload()
{
    switch (State)
    {

    case Unload_Start:
    //Beide Achsen auf in Kippposition bringen
        if (Controller->setPosition(Motor_Linear, Position_StrokeOT))
        {
            if (Controller->setPosition(Motor_Rotate, Position_Rotate))
            {
                State = Unload_MovingHome;
            starttime = millis();
            }

            
    }
        break;

    case Unload_MovingHome:
    if (millis()-starttime > 10000)
    {
        if (Controller->setPosition(Motor_Rotate, Position_RotateMovingHome))
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
int Unload::ActiveState()
{
    return State;
}