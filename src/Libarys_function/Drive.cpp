#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include <Drive.h>

void Drive::Setup(Adafruit_MotorShield *shield, int Port)
{
    Shield = shield;
    Wheel = Shield->getMotor(Port);
}
void Drive::setMotor(int Direction, int Velocity)
{
    Wheel->run(Direction);
    Wheel->setSpeed(Velocity);
}