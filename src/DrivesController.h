#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "Drive.h"

#ifndef DrivesController_h
#define DrivesController_h

enum Command
{
    StraightForward,
    StraightBackward,
    TurnLeft,
    TurnRight,
    GoRight,
    GoLeft,
    Stay
};
class DrivesController
{
private:
    Drive VR;
    Drive VL;
    Drive HR;
    Drive HL;
    Drive Linear;
    Drive Rotate;

    Drive *Drives[4] = {&VR, &VL, &HR, &HL};
    Command Command_Controller;
    Adafruit_MotorShield AFMS1;
    Adafruit_MotorShield AFMS2;
    volatile int *Encoder_Linear;
    volatile int *Encoder_Rotate;
    bool Position;
    int Velocity_Drives;

public:
    void ExecuteStateMachine();
    void Setup(volatile int *Encoder_L, volatile int *Encoder_R);
    void setCommand(Command Command, int Velocity);
    bool setPosition(int Direction, int Increment);
};

#endif
