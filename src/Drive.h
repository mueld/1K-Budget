#include <Wire.h>
#include <Adafruit_MotorShield.h>

#ifndef Drive_h
#define Drive_h

enum Direction_Drive
{
    Drive_Forward = 4,
    Drive_Backward = 5,
    Drive_TurnRight = 2,
    Drive_TurnLeft = 3,
    Drive_MoveRight = 1,
    Drive_MoveLeft = 0
};

enum Location
{
    Location_VR,
    Location_VL,
    Location_HR,
    Location_HL
};

class  Wheel::Drive{
        
}


class Drive
{
private:
    Adafruit_DCMotor *Wheel;
    Adafruit_MotorShield *Shield;
    Location Location_Drive;
    int LookUpTable[6][4] =
        {
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 1, 1},
            {1, 1, 0, 1}};

public:
    void Setup(Adafruit_MotorShield *shield, int Port, Location location);
    void startMovement(Direction_Drive Direction, int Velocity);
};

#endif
