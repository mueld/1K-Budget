#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include "Drive.h"

void Drive::Setup(Adafruit_MotorShield *shield, int Port, Location location)
{
    Shield = shield;
    Location_Drive = location;
    Wheel = Shield->getMotor(Port);
}

void Drive::setMotor(Direction_Drive Direction, int Velocity)
{
    Wheel->run(LookUpTable[Direction][Location_Drive]);
    Wheel->setSpeed(Velocity);
}