#include "objectdetection.h"
#include "ToF.h"
#include "Align.h"

void Align::Setup(DrivesController *Controller)
{
    this->Controller = Controller;

}

void Align::Execute(int Distance)
{
    switch (State)
    {
    case Align_Distance:
        if (Sensor_Data[0] > Distance)
        {
            Controller->MoveRight(25);
        }
        else if (Sensor_Data[0] < Distance)
        {
            Controller->MoveLeft(25);
        }
        else
        {
            Controller->Stay();
            State = Align_Parallel;
        }
        break;
    
    case  Align_Parallel:
        if (Sensor_Data[0] % Sensor_Data[1] >= 4 && Sensor_Data[0] > Sensor_Data[1])
        {
            Controller->TurnLeft(25);
        }
        else if (Sensor_Data[1] % Sensor_Data[0] >= 2)
        {
            Controller->TurnRight(25);
        }
        else
        {
            Controller->Stay();
            State = Align_Idle;
        }
        break;
    case Align_Idle:
        State = Align_Distance;
    }
}
void Align::update(int Table[])
{
    for (int i = 0; i < 4; i++)
    {
        Sensor_Data[i] = Table[i];
    }
}
void Align::Print()
{

        for (int i = 0; i < 4; i++)
    {
        Serial.println(Sensor_Data[i]);
    }
    
    
    }
int Align::ActiveState()
{
    return (int)State;
}