#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "DrivesController.h"
#include "Drive.h"

void DrivesController::ExecuteStateMachine()
{
    switch(Command_Controller)
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

void DrivesController::Setup()
{
    AFMS = Adafruit_MotorShield();
    Pointer = &AFMS;
    VR.Setup(Pointer, 1);
    VL.Setup(Pointer, 2);
    HR.Setup(Pointer, 3);
    HL.Setup(Pointer, 4);
    Pointer->begin();
}