#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "Drive.h"

#ifndef DrivesController_h
#define DrivesController_h
#define EncoderPinA_L 2
#define EncoderPinB_L 4
#define EncoderPinA_R 3
#define EncoderPinB_R 5
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
    volatile int Encoder_Linear;
    volatile int Encoder_Rotate;
    bool State;
    int Velocity_Drives;

public:
    void ExecuteStateMachine();
    void Setup();
    void setCommand(Command Command, int Velocity);
    bool setPosition(MotorPosition Motor, int Position);
    void ReadEncoderLinear();
    void ReadEncoderRotate();
};

#endif
