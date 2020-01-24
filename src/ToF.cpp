#include "ToF.h"
#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_VL6180X.h>


void ToF::InitToF()
{
    
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(Pin[i], LOW);
    }
    
    delay(10);
    // all unreset
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(Pin[i], HIGH);
    }

    delay(10);

    // activating LOX1 and reseting LOX2
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);

    // initing LOX1
    for (int i = 0; i < 5; i++)
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
    for (int i = 0; i < 5; i++)
    {
        Sensoren[i]->rangingTest(Table_Measure[i], false);
    }
    index = index % 2;
    for (int i = 0; i < 5; i++)
    {
             Table_Measure_Data[i][index] = Table_Measure[i]->RangeMilliMeter;
           
        //  Serial.println("Übergabe an Array:");
        //Serial.println(Table_Measure_Data[i]);
    }
    index++;
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            summ += Table_Measure_Data[i][k];
         /*   Serial.print("Summ:");
            Serial.println(summ);
*/        }
        Average_Measure[i] = summ / 2;
        summ = 0;
    }
    
}

bool ToF::ErrorState()
{
    for (int i = 0; i < 5; i++)
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
   
    for (int i = 0; i < 4; i++)
    {
        Observers[i]->update(Average_Measure);
    }
    
}