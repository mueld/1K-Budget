#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include "Drive.h"

void Drive::SetShield(Adafruit_MotorShield *shield_, int Port)
{
    Shield = shield_;
    Motor = Shield->getMotor(Port);
}

void Drive::MovementMotor(int Direction, int Velocity)
{
    Motor->run(Direction);
    Motor->setSpeed(Velocity);
}

void Wheel::Setup(Adafruit_MotorShield *shield, int Port, Location location)
{
    Wheel_ID = location;
    SetShield(shield, Port);
}

void Wheel::startMovement(Direction_Drive Direction, int Velocity)
{
    MovementMotor(LookUpTable[Direction][Wheel_ID], Velocity);
}

void Axis::Setup(Adafruit_MotorShield *shield, int port, volatile int *encoder)
{
    Encoder = encoder;
    SetShield(shield, port);
}

bool Axis::SetPosition(Position_Axis position)
{
    InPosition = false;
    if (*Encoder < Position[position] -50 )
    {
        if(*Encoder < Position[position] - 2000)
        {
            MovementMotor(FORWARD, 200);
        }
        else
        {
            MovementMotor(FORWARD, 100);
        }  
    } 

    else if (*Encoder > Position[position]+50)
    {
        if (*Encoder > Position[position] + 2000)
        {
            MovementMotor(BACKWARD, 200);
        }
        else
        {
            MovementMotor(BACKWARD, 100);
        }
    } 
    else
    {
        Serial.println("Position erreicht");
        MovementMotor(1, 0);
        InPosition = true;
        starttime = 0;
    }
    return InPosition;
}
bool Axis::Schleppabstand()
{
    Sollposition = faktor * (starttime - millis()) + 0;
    if (Sollposition - *Encoder < 20)
    {
        return true;
    }
}
bool Axis::ErrorState()
{
   if(Schleppabstand()) 
   {
       return true;
   }
}
String Axis::Error_Message()
{
    String Message = "Schleppabstand zu gross";
    return Message;
}