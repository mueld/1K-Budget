#include "objectdetection.h"
#include "ToF.h"
#include "Align.h"

void Align::Setup(DrivesController *Controller)
{
    this->Controller = Controller;

}

void Align::Execute(int Distance)
{
    Serial.println("bin in align execute");
    switch (State)
    {
    case Align_Distance:
        if (Sensor_Data[0] > Distance)
        {
            Controller->MoveRight(70);
        }
        /*else if (Sensor_Data[0] < Distance)
        {
            Controller->MoveLeft(25);
        }*/
        else
        {
            
            State = Align_Idle;
        }
        break;
    
    case  Align_Parallel:
        if ((Sensor_Data[0]+8) % Sensor_Data[1] >= 10 && (Sensor_Data[0]+8) > Sensor_Data[1])
        {
            Controller->TurnRight(50);
        }
        else if ((Sensor_Data[1] - 8) % Sensor_Data[0] >= 10 && (Sensor_Data[0] + 8) < Sensor_Data[1])
        {
            Controller->TurnLeft(50);
        }
        else
        {
            Controller->Stay();
            State = Align_Distance;
        }
        break;
    case Align_Idle:
        State = Align_Parallel;
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