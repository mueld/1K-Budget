#ifndef Parking_h
#define Parking_h
#include "Unload.h"
enum Parking_State
{
    Parking_SearchPosition,
    Parking_Align,
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
    Pixy2 *camera;
    Align *align;

public:
    void Setup(DrivesController *DriveController, Objectdetection *objectdetection, ToF *Sensors, Pixy2 *pixy, Align *align);
    void ExecuteParking();
    int ActiveState();
};


#endif