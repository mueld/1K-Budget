#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include "Drive.h"

void Wheel::Setup(Adafruit_MotorShield *shield, int Port, Location location)
{
    this.base(shield, port);  
    Location_Drive = location;
}

void Axis::Setup(Adafruit_MotorShield *shield, int Port, Encoder encoder)
{
    this.base(shield, port);
    encoder = encoder;
}

void Drive::Setup(Adafruit_MotorShield *shield, int Port)
{
    Shield = shield;
    Wheel = Shield->getMotor(Port);
}

void Wheel::startMovement(Direction_Drive Direction, int Velocity)
{
    Motor->run(LookUpTable[Direction][Location_Drive]);
    Motor->setSpeed(Velocity);
}