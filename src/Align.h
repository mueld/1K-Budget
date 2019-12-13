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
class Align: public ToF_Interface, public IModuleState
{
    private:
        Align_State State;
        DrivesController *Controller;
        int Sensor_Data[4];

    public:
        void Setup(DrivesController *Controller);
        void Execute(int Distance);
        void update(int Table[]);
        void Print();
        int ActiveState();
};

#endif