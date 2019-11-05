#include <Wire.h>
#include <Adafruit_MotorShield.h>

#ifndef Drive_h
#define Drive_h


class Drive
{
private:

    Adafruit_DCMotor *Wheel;
    Adafruit_MotorShield *Shield;
    volatile int *encoder;

public:
    void Setup(Adafruit_MotorShield *shield, int Port, volatile int *Encoder);
    void setMotor(int Direction, int Velocity);
    bool PositionMotor(int Direction, int Inkrement);
    
};

#endif
