#include "ToF.h"
#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>


void ToF::InitToF()
{
    
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(Pin[i], LOW);
    }
    
    delay(10);
    // all unreset
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(Pin[i], HIGH);
    }

    delay(10);

    // activating LOX1 and reseting LOX2
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);

    // initing LOX1
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(Pin[i], HIGH);
        delay(10);
        Serial.println("Initialized..");
        if (!Sensoren[i]->begin(Address[i]))
        {
           Serial.print("Failed to boot ");
           Serial.print(i);
           while (1)
               ;
       }
       else
       {
           Serial.println("Succesfull");
       }
       
    }  
}
void ToF::Setup()
{
    InitToF();
}


void ToF::Reading()
{
    for (int i = 0; i < 4; i++)
    {
        Sensoren[i]->rangingTest(Table_Measure[i], false);
    }
    for (int i = 0; i < 4; i++)
    {
        Table_Measure_Data[i] = Table_Measure[i]->RangeMilliMeter;
      //  Serial.println("Übergabe an Array:");
        //Serial.println(Table_Measure_Data[i]);
    }
}

bool ToF::ErrorState()
{
    for (int i = 0; i < 4; i++)
    {
        if (Sensoren[i]->Status != 0)
        {
            return true;
        }
    }
        return false;
}
String ToF::Error_Message()
{
    String Message = "Sensor ausgefallen Steuerung bitte neu starten";
    return Message;
}

void ToF::Register(ToF_Interface *O)
{
    Observers[Index_Interface] = O;
    Index_Interface++;
}
void ToF::NotifyObserver()
{
    for (int i = 0; i < 1; i++)
    {
        Observers[i]->update(Table_Measure_Data);
    }
    
}