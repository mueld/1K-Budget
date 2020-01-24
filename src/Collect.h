#ifndef Collect_h
#define Collect_h

#include "FirstRound.h"

enum State_Collect
{
    MovetoPosition_Sensor,
    MovetoPosition,
        Stroke,
    Collect_Finish
};

class Collect: public ToF_Interface
{
    private:
        State_Collect State = MovetoPosition;
        DrivesController *Controller;
        int Sensor_Data[5];
        unsigned long Starttime = 0;

    public:
        void
        Setup(DrivesController *DriveController);
        void CollectThatShit();
        State_Collect ActiveState();
        void update(int Table[5]);
        
};

#endif