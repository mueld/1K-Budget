#ifndef Parking_h
#define Parking_h
#include "Unload.h"
enum Parking_State
{
    Parking_SearchPosition,
    Parking_GotoWall,
    Parking_Park
};

class Parking: public ToF_Interface
{
private:
    Parking_State State;
    DrivesController *Controller;
    Objectdetection *Detection;
    ToF *Sensor;
    int Sensor_Data[4];

public:
    void Setup(DrivesController *DriveController, Objectdetection *objectdetection, ToF *Sensors);
    bool ExecuteParking();
    void update(int Table[4]);
};


#endif