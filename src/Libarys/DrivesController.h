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

    Drive *Drives[4] = {&VR, &VL, &HR, &HL};
    Command Command_Controller;
    Adafruit_MotorShield AFMS;
    Adafruit_MotorShield *Pointer;
    int Velocity_Drives;

public:
    void ExecuteStateMachine();
    void Setup();
    void setCommand(Command Command, int Velocity);
};

#endif
