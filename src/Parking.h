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

class Parking : public ToF_Interface
{
private:
    Parking_State State;
    DrivesController *Controller;
    Pixy2 *camera;
    Align *align;
    int Sensor_Data[5];

public:
    void Setup(DrivesController *DriveController, Pixy2 *pixy, Align *align);
    void ExecuteParking();
    int ActiveState();
    void update(int Table[5]);
};


#endif