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

class  Wheel: Drive{
private:
    Location Wheel_ID;
    int LookUpTable[6][4] =
        {
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 1, 1},
            {1, 1, 0, 1}};

    void startMovement(Direction_Drive Direction, int Velocity);
};


class Drive
{
private:
    Adafruit_DCMotor *Motor;
    Adafruit_MotorShield *Shield;
    
public:
    void Setup(Adafruit_MotorShield *shield, int Port);
};

#endif
