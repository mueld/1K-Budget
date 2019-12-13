#ifndef Parking_h
#define Parking_h
#include "Unload.h"
enum Parking_State
{
    Parking_SearchPosition,
    Parking_GotoWall,
    Parking_Park,
    Parking_Idle
};

class Parking: public IModuleState
{
private:
    Parking_State State;
    DrivesController *Controller;
    Objectdetection *Detection;
    ToF *Sensor;

public:
    void Setup(DrivesController *DriveController, Objectdetection *objectdetection, ToF *Sensors);
    void ExecuteParking();
    int ActiveState();
};


#endif