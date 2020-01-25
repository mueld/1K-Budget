#include "Collect.h"
#include "FirstRound.h"

void Collect::Setup(DrivesController *DriveController)
{
    Controller = DriveController;
}
void Collect::CollectThatShit()
{
    switch (State)
    {
    case MovetoPosition_Sensor:
        if (Sensor_Data[2] >= 50)
        {
            Serial.println("Fahre auf würfel zu");
            Controller->MoveForward(75);
            if (Sensor_Data[4] < 150)
            {
                Serial.println("Sensor detected Cube!!!!!!!!!!!!!!!");
                Starttime = millis();
                State = MovetoPosition;
            }
            
        }
        else
        {
            Controller->Stay();
        }
        break;
    case MovetoPosition:
        if (millis() - Starttime > 1000)
        {
            Controller->Stay();
            if (Controller->setPosition(Motor_Linear, Position_StrokeOT))
            {
                Starttime = millis();
                State = Stroke;
            }
        
    }
    
        break;
    case Stroke:
        if (millis() - Starttime < 500)
        {
            Controller->MoveForward(80);
        }
    else
    {
        Controller->Stay();
        
        if (Controller->setPosition(Motor_Linear, Position_StrokeUT))
        {
            State = Collect_Finish;
        }
    }
    break;
    case Collect_Finish:
        State = MovetoPosition;
        break;
    }
}

void Collect::update(int Table[5])
{
    for (int i = 0; i < 5; i++)
    {
        if (Table[i] != 8190)
        {
            Sensor_Data[i] = Table[i];
        }
    }
}
State_Collect Collect::ActiveState()
{
    return State;
}