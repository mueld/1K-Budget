#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include "Drive.h"

void Drive::Setup(Adafruit_MotorShield *shield, int Port,volatile int *Encoder)
{
    encoder = Encoder;
    Shield = shield;
    Wheel = Shield->getMotor(Port);
}
void Drive::setMotor(int Direction, int Velocity)
{
    Wheel->run(Direction);
    Wheel->setSpeed(Velocity);
}
bool Drive::PositionMotor(int Direction, int Inkrement)
{
        
       while(encoder <= Inkrement)
       {
           Wheel->run(Direction);
           Wheel->setSpeed(125);

       }
       encoder = 0;
       return true;
}