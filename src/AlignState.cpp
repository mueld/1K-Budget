#include "objectdetection.h"
#include "ToF.h"
#include "AlignState.h"

void AlignState::Setup(DrivesController *Controller)
{
    this->Controller = Controller;

}

void AlignState::Execute(int Distance)
{
    Serial.println("bin in align execute");
    Serial.println(Sensor_Data[0]);
    switch (State)
    {
     case  Align_Parallel:
        //Roboter richter sich parallel zur rechten seite aus.
        Serial.println("AlignParallel");
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
            if (Sensor_Data[0] < Distance)
            {
                State = Align_Idle;
            }
            else
            {
                Controller->Stay();
            State = Align_Distance; 
            }
        }
        break;
    
    case Align_Distance:
    //Richtet sich nach der übergeben Distanz aus
        if (Sensor_Data[0] > Distance)
        {
            Controller->MoveRight(150);
        }
        else if (Sensor_Data[0] <  (Distance-10))
        {
            Controller->MoveLeft(150);
        }
        else
        {
            
            State = Align_Idle;
        }
        break;
    
   
    case Align_Idle:
        State = Align_Parallel;
    }
}
void AlignState::update(int Table[5])
{
    for (int i = 0; i < 5; i++)
    {
        Sensor_Data[i] = Table[i];
    }
}
void AlignState::Print()
{

        for (int i = 0; i < 5; i++)
    {
        Serial.println(Sensor_Data[i]);
    }
    
    
    }
int AlignState::ActiveState()
{
    return (int)State;
}