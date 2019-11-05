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
    volatile int *encoder;
    Adafruit_MotorShield *Shield;
    Adafruit_MotorShield *Shield2;
    int Velocity_Drives;

public:
    void ExecuteStateMachine();
    void Setup(Adafruit_MotorShield Pointer, Adafruit_MotorShield Pointer2, volatile int *Encoder);
    void setCommand(Command Command, int Velocity);
    void Collect(int Direction, int Inkrement);
};

#endif
