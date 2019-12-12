#include "Collect.h"
#include "FirstRound.h"

void Collect::Setup(ToF *Sensor, DrivesController *DriveController)
{
    Controller = DriveController;
    Sensoren = Sensor;
}
bool Collect::CollectThatShit()
{
    bool result = false;
    switch (State)
    {
    case MovetoPosition:
        if (Sensoren->Cube_Value >= 5)
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
void Collect::update(int Table[4])
{
    for (int i = 0; i < 4; i++)
    {
        Sensor_Data[i] = Table[i];
    }
    
}