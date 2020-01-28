#include <Wire.h>
#include <Adafruit_MotorShield.h>

#ifndef Drive_h
#define Drive_h


enum Direction_Drive
{
    Drive_Forward = 0,
    Drive_Backward = 1,
    Drive_TurnRight = 2,
    Drive_TurnLeft = 3,
    Drive_MoveRight = 4,
    Drive_MoveLeft = 5
};

enum Position_Axis
{
    Position_StrokeOT,
    Position_StrokeUT,
    Position_RotateMovingHome,
    Position_Rotate
};

enum Location
{
    Location_VR,
    Location_VL,
    Location_HR,
    Location_HL
};
class Errorhandler
{   
    public:
    virtual bool ErrorState();
    virtual String Error_Message();
};
class Drive
{
protected:
    Adafruit_DCMotor *Motor;
    Adafruit_MotorShield *Shield;

public:
    void SetShield(Adafruit_MotorShield *shield_, int port);
    void MovementMotor(int Direction, int Velocity);
};


class  Wheel: public Drive{
private:
    Location Wheel_ID;
    int LookUpTable[6][4] =
        {
            {1,2, 1, 2},
            {2, 1, 2, 1},
            {2, 2, 2, 2},
            {1, 1, 1, 1},
            {2, 2, 1, 1},
            {1, 1, 2, 2},
            };


public:
    void startMovement(Direction_Drive Direction, int Velocity);
    void Setup(Adafruit_MotorShield *shield, int Port, Location location);
};


class Axis: public Drive, public Errorhandler
{
    protected:
        int Position[4]{12000, 1000, 0, 4000};
        bool InPosition;
        volatile int *Encoder;
        volatile int Encoder_old = 100;
        bool Error = false;
        unsigned int starttime = 0;
        float faktor = 0;
        int Sollposition;

    public:
        String Error_Message();
        void Setup(Adafruit_MotorShield *shield, int port, volatile int *encoder);
        bool SetPosition(Position_Axis position);
        bool ErrorState();
        bool Schleppabstand();
};    


#endif
