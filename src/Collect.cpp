#include "Collect.h"
#include "FirstRound.h"

void Collect::Setup(DrivesController *DriveController)
{
    Controller = DriveController;
}
bool Collect::CollectThatShit()
{
    bool result = false;
    switch (State)
    {
    case MovetoPosition:
        if (Sensor_Data[3] >= 5)
        {
            Controller->MoveForward(75);
        }
        else
        {
            Controller->Stay();
            State = Stroke;
        }
        break;

    case Stroke:
        if (Controller->setPosition(Motor_Linear, Position_Stroke))
        {
            State = MovingHome;
        }
    case MovingHome:
        if (Controller->setPosition(Motor_Linear, Position_StrokeMovingHome))
        {
            State = Verify_Cube;
        }
        break;

    case Verify_Cube:
        /*if(Sensor_Data[4] < 50)
    {
        State = MovetoPosition;
        result = true;
    }
    else{
        State = Stroke;
    }
        */
        break;
    }
    return result;
}
int Collect::ActiveState()
{
    return State;
}
void Collect::update(int Table[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (Table[i] != 8190)
        {
            Sensor_Data[i] = Table[i];
        }
    }
}