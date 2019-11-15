#include "ToF.h"
#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>
void ToF::InitToF()
{
    for (int i = 6; i < 10; i++)
    {
        digitalWrite(i, LOW);
    }
    delay(10);

    // all unreset
    for (int i = 6; i < 10; i++)
    {
        digitalWrite(i, HIGH);
    }
    delay(10);

    for (int i = 7; i < 10; i++)
    {
        digitalWrite(i, LOW);
    }

    for (int i = 0; i < 4; i++)
    {
        digitalWrite(Pin[i], HIGH);
        delay(10);
        while (!Sensoren[i]->begin(Address[i]))
        {
            Serial.println("Falied to set the new Address for VR");
            digitalWrite(Pin[i], LOW);
            delay(10);
            digitalWrite(Pin[i], HIGH);
            delay(10);
        }
    }
}
void ToF::Setup()
{
    Cube.begin();
    InitToF();
}

void ToF::ExectueStateMachine()
{
    switch (State)
    {
    case ToF_Reading:
        VR.rangingTest(&measureVR, false);
        HR.rangingTest(&measureHR, false);
        Front.rangingTest(&measureFront, false);
        LEFT.rangingTest(&measureLEFT, false);
        Cube_Value = Cube.readRange();
        State = ToF_Idle;
        break;

    case ToF_Idle:

        break;
    }
}

void ToF::Reading()
{
    State = ToF_Reading;
}
