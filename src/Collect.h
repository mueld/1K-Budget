#ifndef Collect_h
#define Collect_h

#include "FirstRound.h"

enum State_Collect
{
    MovetoPosition,
    Stroke,
    Finish
};

class Collect: public IModuleState
{
    private:
        State_Collect State;
        DrivesController *Controller;
        ToF *Sensoren;

    public:
        void Setup(ToF *Sensor, DrivesController *DriveController);
        bool CollectThatShit();
        int ActiveState();
};

#endif