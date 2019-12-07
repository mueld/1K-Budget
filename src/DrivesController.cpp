#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "DrivesController.h"
#include "Drive.h"

void DrivesController::ReadEncoderLinear()
{
    if (digitalRead(EncoderPinB_L) == LOW)
    {
        Encoder[0]++;
    }
    else
    {
        Encoder[0]--;
    }
}

void DrivesController::ReadEncoderRotate()
{
    if (digitalRead(EncoderPinB_R) == LOW)
    {
        Encoder[1]++;
    }
    else
    {
        Encoder[1]--;
    }
}

void DrivesController::MoveTheLadies(Direction_Drive Direction, int Veloctiy)
{
    Serial.println("bin in MoveTheLadies");
    State = Controller_MoveTheLadies;
    for (int i = 0; i < 4; i++)
    {
        Serial.println(i);
        Drives[i]->startMovement(Direction, Veloctiy);
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
    MoveTheLadies(Drive_MoveLeft, Velocity);
}

void DrivesController::Stay()
{
    State = Controller_Idle;
    for (int i = 0; i < 4; i++)
    {
        Drives[i]->startMovement(1, 0);
    }
}

bool DrivesController::setPosition(Motor Motor, Position_Axis Position)
{
    switch (Motor)
    {
    case Motor_Linear:
        if(Linear.SetPosition(Position))
        {
            return true;
        }
        break;

    case Motor_Rotate:
        if (Rotate.SetPosition(Position))
        {
            return true;
        }
        break;
    }
    return false;
}


void DrivesController::Setup()
{
    Serial.println("bin im setup");
    AFMS1 = Adafruit_MotorShield(0x61);
    AFMS2 = Adafruit_MotorShield(0x60);
    VR.Setup(&AFMS1, 1, Location_VR);
    VL.Setup(&AFMS1, 2, Location_VL);
    HR.Setup(&AFMS1, 3, Location_HR);
    HL.Setup(&AFMS1, 4, Location_HL);
    Linear.Setup(&AFMS2, 1, &Encoder[0]);
    Rotate.Setup(&AFMS2, 2, &Encoder[1]);
    AFMS2.begin();
    AFMS1.begin();
}
void DrivesController::PrintEncoder()
{
    Serial.println(Encoder[0]);
}