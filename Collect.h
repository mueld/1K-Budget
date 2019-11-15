#ifndef Collect_h
#define Collect_h

#include "FirstRound.h"

enum State_Collect
{
    MovetoPosition,
    Stroke,
    Idle
};

class Collect_h
{
    private:
        State_Collect State;
        DrivesController *Controller;
        ToF *Sensoren;

    public:
        void Setup(ToF *Sensor DrivesController *DriveController);
        void StateMachine();
};