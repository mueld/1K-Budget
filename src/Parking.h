#ifndef Parking_h
#define Parking_h
#include "Unload.h"
enum Parking_State
{
    Parking_SearchPosition,
    Parking_GotoWall,
    Parking_Park
};

class Parking
{
private:
    Parking_State State;
    DrivesController *Controller;
    Objectdetection *Detection;
    ToF *Sensor;

public:
    void Setup(DrivesController *DriveController, Objectdetection *objectdetection, ToF *Sensors);
    bool ExecuteParking();

};


#endif