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
            State = Finish;
            result = true;
            return result;
        }
    break;

    case Finish:
        State = MovetoPosition;
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