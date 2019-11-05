#include "DrivesController.h"
 
Adafruit_MotorShield AFMS;

DrivesController Instance;
char Direction;
Command CommandInstance;
void setup ()
{
    Serial.begin(9600);
    Instance.Setup(AFMS);
    Serial.println("test");
}

void loop()
{
    if(Serial.available() != 0)
    {
        Direction = Serial.read();
    }
    switch (Direction)
    {
        case "w":
        DrivesController.setCommand(StraightForward, 100);
        break;
        case "a":
        DrivesController.setCommand(TurnLeft, 100);    
        break;
        case "s":
        DrivesController.setCommand(StraightBackward, 100);
        break;
        case "d":
        DrivesController.setCommand(TurnRight, 100);
        break;
        case "q":
        DrivesController.setCommand(GoLeft, 100);
        break;
        case "e":
        DrivesController.setCommand(GoRight, 100);
        break;
        default:
        DrivesController.setCommand(Stay, 0);      
        }
}
