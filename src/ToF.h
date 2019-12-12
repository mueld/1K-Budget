#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>
#include"Drive.h"

#ifndef Tof_h
#define Tof_h


enum ToF_State
{
    ToF_Reading,
    ToF_Idle,
    ToF_Verify_Error,
    ToF_Error
};
class ToF_Interface
{
    public:
    virtual void update(int Table[]);
};
class Subject_Interface
{
    public:
        virtual void Register(ToF_Interface *OI);
        virtual void NotifyObserver();
};
class ToF : public Subject_Interface
{
private:
    ToF_Interface *Observers[5];
    int Pin[4] = {3,4,5,6};
    int Address[4] = {48, 49, 50, 51};
    Adafruit_VL53L0X VR = Adafruit_VL53L0X();
    Adafruit_VL53L0X HR = Adafruit_VL53L0X();
    Adafruit_VL53L0X Front = Adafruit_VL53L0X();
    Adafruit_VL53L0X LEFT = Adafruit_VL53L0X();
    Adafruit_VL53L0X *Sensoren[4] = {&VR, &HR, &Front, &LEFT};
    Adafruit_VL6180X Cube = Adafruit_VL6180X();
    ToF_State State;
    int Index_Interface = 0;
    VL53L0X_RangingMeasurementData_t measureVR;
    VL53L0X_RangingMeasurementData_t measureHR;
    VL53L0X_RangingMeasurementData_t measureFront;
    VL53L0X_RangingMeasurementData_t measureLEFT;
    VL53L0X_RangingMeasurementData_t *Table_Measure[4] = {&measureVR, &measureHR, &measureFront, &measureLEFT};
public:
    int Table_Measure_Data[4];
    int Cube_Value;
    void Setup();
    void Reading();
    void InitToF();
    bool ErrorState();
    bool RemedyError();
    void Register(ToF_Interface *Ob);
    void NotifyObserver();
};

#endif