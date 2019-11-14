#ifndef Tof_h
#define Tof_h
#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>

enum ToF_State
{
    ToF_Reading,
    ToF_Idle
};
class ToF
{
private:
    int Pin[] = {6, 7, 8, 9};
    int Address[] = {48, 49, 50, 51};
    Adafruit_VL53L0X VR = Adafruit_VL53L0X();
    Adafruit_VL53L0X HR = Adafruit_VL53L0X();
    Adafruit_VL53L0X Front = Adafruit_VL53L0X();
    Adafruit_VL53L0X LEFT = Adafruit_VL53L0X();
    Adafruit_VL53L0X *Sensoren[] = {&VR, &HR, &Front, &LEFT};
    Adafruit_VL6180X Cube = Adafruit_VL6180X();
    ToF_State State;

public:
    int Cube_Value;
    VL53L0X_RangingMeasurementData_t measureVR;
    VL53L0X_RangingMeasurementData_t measureHR;
    VL53L0X_RangingMeasurementData_t measureFront;
    VL53L0X_RangingMeasurementData_t measureLEFT;
    void ExectueStateMachine();
    void Setup();
    void Reading();
    void InitToF(Adafruit_VL53L0X Sensor, int Pin);
};

#endif