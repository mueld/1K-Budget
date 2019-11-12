#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "DrivesController.h"
#include "Drive.h"

void DrivesController::ReadEncoderLinear()
{
    if (digitalRead(EncoderPinB_L) == LOW)
    {
        Encoder_Linear--;
    }
    else
    {
        Encoder_Linear++;
    }
}

void DrivesController::ReadEncoderRotate()
{
    if (digitalRead(EncoderPinB_R) == LOW)
    {
        Encoder_Rotate--;
    }
    else
    {
        Encoder_Rotate++;
    }
}
void DrivesController::ExecuteStateMachine()
{
    switch (Command_Controller)
    {
    case StraightForward:
        for (int i = 0; i < 4; i++)
        {
            Drives[i]->setMotor(1, Velocity_Drives);
        }
        break;

    case StraightBackward:
        for (int i = 0; i < 4; i++)
        {
            Drives[i]->setMotor(2, Velocity_Drives);
        }
        break;
    case Stay:
        for (int i = 0; i < 4; i++)
        {
            Drives[i]->setMotor(1, 0);
        }

    case TurnLeft:
        Drives[0], Drives[2]->setMotor(1, Velocity_Drives);
        Drives[1], Drives[3]->setMotor(2, Velocity_Drives);

        break;
    case TurnRight:
        Drives[0], Drives[2]->setMotor(2, Velocity_Drives);
        Drives[1], Drives[3]->setMotor(1, Velocity_Drives);
        break;
    case GoRight:
        Drives[0], Drives[3]->setMotor(2, Velocity_Drives);
        Drives[1], Drives[2]->setMotor(1, Velocity_Drives);

        break;
    case GoLeft:
        Drives[0], Drives[3]->setMotor(1, Velocity_Drives);
        Drives[1], Drives[2]->setMotor(2, Velocity_Drives);
        break;
    }
}
void DrivesController::setCommand(Command Command, int Velocity)
{
    Command_Controller = Command;
    Velocity_Drives = Velocity;
}

bool DrivesController::setPosition(MotorPosition Motor, int Position)
{

    State = false;
    switch (Motor)
    {
    case Motor_Linear:
        if (Encoder_Linear < Position - 10)
        {
            Linear.setMotor(FORWARD, 100);
        }
        else if (Encoder_Linear > Position + 10)
        {
            Linear.setMotor(BACKWARD, 100);
        }
        else
        {
            Linear.setMotor(1, 0);
            State = true;
        }
        break;

    case Motor_Rotate:
        if (Encoder_Rotate < Position - 10)
        {
            Rotate.setMotor(FORWARD, 100);
        }
        else if (Encoder_Rotate > Position + 10)
        {
            Rotate.setMotor(BACKWARD, 100);
        }
        else
        {
            Rotate.setMotor(1, 0);
            State = true;
        }
        break;
    }
    return State;
}

void DrivesController::Setup()
{
    AFMS1 = Adafruit_MotorShield(0x60);
    AFMS2 = Adafruit_MotorShield(0x61);
    VR.Setup(&AFMS1, 1);
    VL.Setup(&AFMS1, 2);
    HR.Setup(&AFMS1, 3);
    HL.Setup(&AFMS1, 4);
    Linear.Setup(&AFMS2, 1);
    Rotate.Setup(&AFMS2, 2);
    AFMS1.begin();
    AFMS2.begin();
}