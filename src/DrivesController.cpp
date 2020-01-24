#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "DrivesController.h"
#include "Drive.h"

void DrivesController::ReadEncoderLinear()
{
    if (digitalRead(EncoderPinB_L) == LOW)
    {
        Encoder[0]--;
    }
    else
    {
        Encoder[0]++;
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
    Serial.print("Direction:");
    Serial.println(Direction);
    State = Controller_MoveTheLadies;
    for (int i = 0; i < 4; i++)
    {
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
        Drives[i]->MovementMotor(1, 0);
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
 AFMS1 = Adafruit_MotorShield(0x60);
   AFMS2 = Adafruit_MotorShield(0x61);
    VR.Setup(&AFMS1, 1, Location_VR);
    VL.Setup(&AFMS1, 2, Location_VL);
    HR.Setup(&AFMS1, 3, Location_HR);
    HL.Setup(&AFMS1, 4, Location_HL);
   Linear.Setup(&AFMS2, 1, &Encoder[0]);
    Rotate.Setup(&AFMS2, 2, &Encoder[1]);
    AFMS1.begin();
    AFMS2.begin();
}
void DrivesController::PrintEncoder(Motor motor)
{
    Serial.println(Encoder[motor]);
}
bool DrivesController::ErrorState()
{
    if(Linear.ErrorState() == true || Rotate.ErrorState() == true)
    {
        return true;
    }
}
String DrivesController::Error_Message()
{
    if(Linear.ErrorState() == true)
    {
        return Linear.Error_Message();
    }
    else if (Rotate.ErrorState() == true)
    {
        return Rotate.Error_Message();
    }
}
void DrivesController::IBNAxis(Motor motor, int direction)
{
     if (digitalRead(6) ==  false)
    {
        Serial.println("Taster FOrwad gedrüvkt");
        switch (motor)
        {
        case Motor_Linear:
            Linear.MovementMotor(direction, 255);
            break;
        
        case Motor_Rotate:
            Rotate.MovementMotor(direction, 100);
            break;
        }  
    }
    else
    {
        Linear.MovementMotor(1, 0);
        Rotate.MovementMotor(1, 0);
    }
    


    if (digitalRead(5) == false)
    {
        Encoder[motor] = 0;
     }
     
}
void DrivesController::ReadEEPROM()
{
    byte *p = (byte*)&Encoder[0];
    for (int i = 0; i < 4; i++)
    {
        *p++ =EEPROM.read(i);
    }
    
}
void DrivesController::UpdateEEPROM()
{
    if (millis()-activetime >10)
    {
        byte *p;
    p = (byte *)&Encoder[0];

    for (int i = 0; i < 4; i++)

    {
        
        EEPROM.update(i, *p++);
    }
    activetime = millis();
    }
}