#ifndef Collect_h
#define Collect_h

#include "FirstRound.h"

enum State_Collect
{
    MovetoPosition,
    Stroke,
    Finish
};

class Collect: public ToF_Interface
{
    private:
        State_Collect State;
        DrivesController *Controller;
        ToF *Sensoren;
        int Sensor_Data[4];

    public:
        void Setup(ToF *Sensor, DrivesController *DriveController);
        bool CollectThatShit();
        void update(int Table[4]);
};

#endif