#ifndef Tof_h
#define Tof_h
#include <Adafruit_VL53L0X.h>

#define VR_ADDRESS 0x30
#define HR_ADDRESS 0x31
#define FRONT_ADDRESS 0x32
#define CUBE_ADDRESS 0x33
#define SHT_VR 6
#define SHT_HR 7
#define SHT_FRONT 8
#define SHT_CUBE 9

enum ToF_State
{
    ToF_Reading,
    ToF_Idle
};

class ToF
{
private:
    Adafruit_VL53L0X VR = Adafruit_VL53L0X();
    Adafruit_VL53L0X HR = Adafruit_VL53L0X();
    Adafruit_VL53L0X Front = Adafruit_VL53L0X();
    Adafruit_VL53L0X Cube = Adafruit_VL53L0X();
    ToF_State State;

public:
    VL53L0X_RangingMeasurementData_t measureVR;
    VL53L0X_RangingMeasurementData_t measureHR;
    VL53L0X_RangingMeasurementData_t measureFront;
    VL53L0X_RangingMeasurementData_t measureCube;
    void ExectueStateMachine();
    void Setup();
    void Reading();
};

#endif