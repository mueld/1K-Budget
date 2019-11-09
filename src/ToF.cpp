#include "ToF.h"
#include <Adafruit_VL53L0X.h>

void ToF::Setup()
{
    
        // all reset
        digitalWrite(SHT_VR, LOW);
        digitalWrite(SHT_HR, LOW);
        digitalWrite(SHT_FRONT, LOW);
        digitalWrite(SHT_CUBE, LOW);
        delay(10);
        // all unreset
        digitalWrite(SHT_VR, HIGH);
        digitalWrite(SHT_HR, HIGH);
        digitalWrite(SHT_FRONT, HIGH);
        digitalWrite(SHT_CUBE, HIGH);
        delay(10);

        // activating LOX1 and reseting LOX2
        digitalWrite(SHT_VR, HIGH);
        digitalWrite(SHT_HR, LOW);
        digitalWrite(SHT_FRONT, LOW);
        digitalWrite(SHT_CUBE, LOW);

        // initing LOX1
        if (!VR.begin(VR_ADDRESS))
        {
            Serial.println("Falied to set the new Address for VR");
            digitalWrite(SHT_VR, LOW);
            delay(10);
            digitalWrite(SHT_VR, HIGH);
            delay(10);
        }

        digitalWrite(SHT_HR, HIGH);
        delay(10);

        if (!HR.begin(HR_ADDRESS))
        {
            Serial.println("Falied to set the new Address for HR");
            digitalWrite(SHT_HR, LOW);
            delay(10);
            digitalWrite(SHT_HR, HIGH);
            delay(10);
        }

        digitalWrite(SHT_FRONT, HIGH);
        delay(10);

        if (!Front.begin(FRONT_ADDRESS))
        {
            Serial.println("Falied to set the new Address for FRONT");
            digitalWrite(SHT_FRONT, LOW);
            delay(10);
            digitalWrite(SHT_FRONT, HIGH);
            delay(10);
        }

        digitalWrite(SHT_CUBE, HIGH);
        delay(10);

        if (!Cube.begin(CUBE_ADDRESS))
        {
            Serial.println("Falied to set the new Address for CUBE");
            digitalWrite(SHT_CUBE, LOW);
            delay(10);
            digitalWrite(SHT_CUBE, HIGH);
            delay(10);
        }
    }


void ToF::ExectueStateMachine()
{
    switch (State)
    {
    case ToF_Reading:
        VR.rangingTest(&measureVR, false);
        HR.rangingTest(&measureHR, false);
        Front.rangingTest(&measureFront, false);
        Cube.rangingTest(&measureCube, false);
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