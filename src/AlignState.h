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
class AlignState: public ToF_Interface, public IModuleState
{
    private:
        Align_State State = Align_Parallel;
        DrivesController *Controller;
        int Sensor_Data[5];

    public:
        void Setup(DrivesController *Controller);
        void Execute(int Distance);
        void update(int Table[5]);
        void Print();
        int ActiveState();
};

#endif