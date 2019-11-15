#ifndef Collect_h
#define Collect_h

#include "FirstRound.h"

enum State_Collect
{

};

class Collect_h
{
    private:

    public:
        void Setup(ToF *Sensor DrivesController *DriveController);
        bool Collect();
};