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
enum MotorPosition
{
    Motor_Rotate,
    Motor_Linear
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
    volatile int *E_linear;
    volatile int *E_rotate;
    bool Position;
    int Velocity_Drives;

public:
    void ExecuteStateMachine();
    void Setup(volatile int *Encoder_l, volatile int *Encoder_r);
    void setCommand(Command Command, int Velocity);
    bool setPosition(MotorPosition Motor, int Direction, int Increment);
};

#endif
