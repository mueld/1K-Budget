#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "Drive.h"
#include <EEPROM.h>
#ifndef DrivesController_h
#define DrivesController_h
#define EncoderPinA_L 2
#define EncoderPinB_L 4
#define EncoderPinA_R 3
#define EncoderPinB_R 12

enum Motor
{
    Motor_Linear,
    Motor_Rotate
};
enum ControllerState
{
    Controller_Initilaize,
    Controller_MoveTheLadies,
    Controller_Positioning,
    Controller_Idle

};

class DrivesController:public Errorhandler
{
private:
    Wheel VR;
    Wheel VL;
    Wheel HR;
    Wheel HL;
    Axis Linear;
    Axis Rotate;
    Wheel *Drives[4] = {&VR, &VL, &HR, &HL};

    Adafruit_MotorShield AFMS1;
    Adafruit_MotorShield AFMS2;
    volatile int Encoder[2] = {12067,0};

    ControllerState State;
    unsigned long activetime = 0;
    void MoveTheLadies(Direction_Drive Direction, int Velocity_Drives);

public:
    void Setup();
    void MoveForward(int Velocity);
    void MoveBackward(int Velocity);
    void TurnRight(int Velocity);
    void TurnLeft(int Velocity);
    void MoveRight(int Velocity);
    void MoveLeft(int Velocity);
    void Stay();

    bool setPosition(Motor Motor, Position_Axis position);
    void ReadEncoderLinear();
    void ReadEncoderRotate();
    String Error_Message();
    bool ErrorState();
    void PrintEncoder(Motor motor);
    void IBNAxis(Motor motor, int direction);
    void ReadEEPROM();
    void UpdateEEPROM();
};

#endif
