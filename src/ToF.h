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
    //muss von den Observern implementiert werden!!
    public:
    virtual void update(int Table[]);
};

class Subject_Interface
{
    //muss vom Subjekt implentiert werden!!
    //bietet Registerung und benachrichtung.
    public:
        virtual void Register(ToF_Interface *Ob);
        virtual void NotifyObserver();
};
class ToF : public Subject_Interface, public Errorhandler
{
private:
    ToF_Interface *Observers[4];
    int Pin[5] = {8,9,10,11,13};
    int Address[5] = {48, 49, 50, 51,53};
    Adafruit_VL53L0X VR = Adafruit_VL53L0X();
    Adafruit_VL53L0X HR = Adafruit_VL53L0X();
    Adafruit_VL53L0X Front = Adafruit_VL53L0X();
    Adafruit_VL53L0X LEFT = Adafruit_VL53L0X();
    Adafruit_VL53L0X Cube = Adafruit_VL53L0X();
    Adafruit_VL53L0X *Sensoren[5] = {&VR, &HR, &Front, &LEFT, &Cube};
    //Adafruit_VL6180X Cube = Adafruit_VL6180X();
    ToF_State State;
    int Index_Interface = 0;
    VL53L0X_RangingMeasurementData_t measureVR;
    VL53L0X_RangingMeasurementData_t measureHR;
    VL53L0X_RangingMeasurementData_t measureFront;
    VL53L0X_RangingMeasurementData_t measureLEFT;
    VL53L0X_RangingMeasurementData_t measureCube;
    VL53L0X_RangingMeasurementData_t *Table_Measure[5] = {&measureVR, &measureHR, &measureFront, &measureLEFT, &measureCube};
    int index = 0;
    int Table_Measure_Data[5][2];
    
    int summ = 0;
    int Cube_Value;
public:
    void Setup();
    void Reading();
    void InitToF();
    bool ErrorState();
    String Error_Message();
    void Register(ToF_Interface *Ob);
    void NotifyObserver(); //benachtitigt Observer
    int Average_Measure[5];
};

#endif