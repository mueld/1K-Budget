#include <Wire.h>
#include <Adafruit_MotorShield.h>

#ifndef Drive_h
#define Drive_h


class Drive
{
private:

    Adafruit_DCMotor *Wheel;
    Adafruit_MotorShield *Shield;


public:
    void Setup(Adafruit_MotorShield *shield, int Port);
    void setMotor(int Direction, int Velocity);
};

#endif
