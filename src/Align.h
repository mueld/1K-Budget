#include "objectdetection.h"
#include "ToF.h"

#ifndef Align_h
#define Align_h
enum Align_State
{
    Align_Distance,
    Align_Parallel,
    Align_Idle
}
class Align
{
    private:
        Align_State State;
        DrivesController *Controller;
        ToF *Sensors;

    public:
        void Setup(DrivesController *Controller, ToF *Sensors);
        void Execute(int Distance);
        Align_State ActiveState();
}





#endif