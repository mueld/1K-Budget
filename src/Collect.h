#ifndef Collect_h
#define Collect_h

#include "FirstRound.h"

enum State_Collect
{
    MovetoPosition,
    Stroke,
    Finish
};

class Collect: public IModuleState , public ToF_Interface
{
    private:
        State_Collect State;
        DrivesController *Controller;
        int Sensor_Data[4];

    public:
        void Setup(DrivesController *DriveController);
        bool CollectThatShit();
        int ActiveState();
        void update(int Table[4]);
};

#endif