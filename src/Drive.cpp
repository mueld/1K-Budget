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
    if(Encoder != Encoder_old)
    {
            if (Encoder < Position[position] - 2)
        {
            MovementMotor(FORWARD, 100);
            Encoder_old = Encoder;
        }
        else if (Encoder > Position[position] + 2)
        {
            MovementMotor(BACKWARD, 100);
        }
        else
        {
            MovementMotor(1, 0);
            InPosition = true;
        }
    }
    else
    {
        MovementMotor(1, 0);
        Error = true;
    }
    
    return InPosition;
}
bool Axis::ErrorState()
{
    if(Error)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Axis::RemedyError()
{
    if(SetPosition(Position_StartingPositionStroke))
    {
        Error = false;
    }
}