#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "DrivesController.h"
#include "Drive.h"

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
        VR.setMotor(1, Velocity_Drives);
        VL.setMotor(2, Velocity_Drives);
        HR.setMotor(1, Velocity_Drives);
        HL.setMotor(2, Velocity_Drives);
        break;
    case TurnRight:
        VR.setMotor(2, Velocity_Drives);
        VL.setMotor(1, Velocity_Drives);
        HR.setMotor(2, Velocity_Drives);
        HL.setMotor(1, Velocity_Drives);
        break;
    case GoRight:
        VR.setMotor(2, Velocity_Drives);
        VL.setMotor(1, Velocity_Drives);
        HR.setMotor(1, Velocity_Drives);
        HL.setMotor(2, Velocity_Drives);
        break;
    case GoLeft:
        VR.setMotor(1, Velocity_Drives);
        VL.setMotor(2, Velocity_Drives);
        HR.setMotor(2, Velocity_Drives);
        HL.setMotor(1, Velocity_Drives);
        break;
    }
}
void DrivesController::setCommand(Command Command, int Velocity)
{
    Command_Controller = Command;
    Velocity_Drives = Velocity;
}

bool DrivesController::setPosition(MotorPosition Motor, int direction, int Increment)
{
    Position = false;
    switch (Motor)
    {
    case Motor_Linear:
        if (Increment < Encoder_Linear)
        {
            Linear.setMotor(direction, 100);
        }
        else
        {
            Linear.setMotor(1, 0);
            Encoder_Linear = 0;
        }
        break;

    default:
        break;
    }
    if (Increment < Encoder_Rotate)
    {
    }
}

void DrivesController::Setup(volatile int *Encoder_L, volatile int *Encoder_R)
{
    Encoder_Linear = Encoder_L;
    Encoder_Rotate = Encoder_R;
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