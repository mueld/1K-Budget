#include "objectdetection.h"
#include "ToF.h"

#ifndef Align_h
#define Align_h
enum Align_State
{
    Align_Distance,
    Align_Parallel,
    Align_Idle
};
class Align: public ToF_Interface
{
    private:
        Align_State State;
        DrivesController *Controller;
        int Sensor_Data[4];

    public:
        void Setup(DrivesController *Controller);
        void Execute(int Distance);
        void update(int Table[4]);
        Align_State ActiveState();
};

#endif