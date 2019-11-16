#include "Collect.h"
#include "FirstRound.h"

void Collect::Setup(ToF *Sensor, DrivesController *DriveController)
{
    Controller = DriveController;
    Sensoren = Sensor;
}
bool Collect::CollectThatShit()
{
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
            return true;
        }
    break;

    case Finish:
        State = MovetoPosition;
    break;
    }
}