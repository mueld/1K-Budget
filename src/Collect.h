#ifndef Collect_h
#define Collect_h

#include "FirstRound.h"

enum State_Collect
{
    MovetoPosition,
    Stroke,
    Verify_Cube,
    MovingHome
};

class Collect: public ToF_Interface
{
    private:
        State_Collect State = MovetoPosition;
        DrivesController *Controller;
        int Sensor_Data[5];

    public:
        void Setup(DrivesController *DriveController);
        bool CollectThatShit();
        void update(int Table[5]);
        
};

#endif