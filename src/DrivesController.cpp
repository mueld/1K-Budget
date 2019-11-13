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


void DrivesController::MoveTheLadies(Direction_Drive Direction, int Veloctiy)
{
    if(State != Controller_Idle )
    {
        return;
    }

    State = Controller_MoveTheLadies;
    for (int i = 0; i < 4; i++)
    {
        Drives[i]->setMotor(Controller_Direction, Veloctiy)
    }
    
}

void DrivesController::MoveForward(int Velocity)
{
    MoveTheLadies(Drive_Forward, Velocity);
}

void DrivesController::MoveBackward(int Velocity)
{
    MoveTheLadies(Drive_Backward, Velocity);
}

void DrivesController::TurnRight(int Velocity)
{
    MoveTheLadies(Drive_TurnRight, Velocity);
}

void DrivesController::TurnLeft(int Velocity)
{
    MoveTheLadies(Drive_TurnLeft, Velocity);
}

void DrivesController::MoveRight(int Velocity)
{
    MoveTheLadies(Drive_MoveRight, Velocity);
}

void DrivesController::MoveLeft(int Velocity)
{
    State = 
    MoveTheLadies(Drive_MoveLeft, Velocity);
}

void DrivesController::Stay()
{
    State = Controller_Idle;
    for (int i = 0; i < 4; i++)
    {
        Drives[i]->setMotor(1, 0);
    }
    
}

bool DrivesController::setPosition(MotorPosition Motor, int Position)
{

    InPosition = false;
    switch (Motor)
    {
    case Motor_Linear:
        if (Encoder_Linear < Position - 2)
        {
            Linear.setMotor(FORWARD, 100);
        }
        else if (Encoder_Linear > Position + 2)
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
    VR.Setup(&AFMS1, 1, Location_VR);
    VL.Setup(&AFMS1, 2, Location_VL);
    HR.Setup(&AFMS1, 3, Location_HR);
    HL.Setup(&AFMS1, 4, Location_HL);
    Linear.Setup(&AFMS2, 1);
    Rotate.Setup(&AFMS2, 2);
    AFMS1.begin();
    AFMS2.begin();
}