#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <DrivesController.h>


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

void DrivesController::Setup(Adafruit_MotorShield Pointer)
{
    Shield = &Pointer;
    VR.Setup(Shield, 1);
    VL.Setup(Shield, 2);
    HR.Setup(Shield, 3);
    HL.Setup(Shield, 4);
}