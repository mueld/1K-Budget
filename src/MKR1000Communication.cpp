#include "MKR1000Communication.h"
#include "Parking.h"
#include <Arduino_JSON.h>
void MKR1000Communication::SendData(int ProcessState, int ProcessCubes)
{
    if (millis() - starttime > 100)
    {
        // Serial.println("Sende Daten!!!!!!");
        Serial1.write(ProcessState);
        Serial1.write(ProcessCubes);
        starttime = millis();
    }
}
bool MKR1000Communication::Read()
{
    bool result = false;
    if (Serial1.available())
    {
        Response = "";

        while (Serial1.available())
        {
            Response.concat((char)Serial1.read());
        }
        Serial.print("Response: ");
        Serial.println(Response);
        Data = JSON.parse(Response);
        if (JSON.typeof(Data) == "undefined")
        {
            Serial.println("Parsing input failed!");
            return;
        }
        //Serial.println((const char*)Data["Start"]);
    }
    return result;
}
int MKR1000Communication::ActiveState()
{
    if (*(const char *)Data["Start"] == '1')
    {
        Serial.println("starttttt!!!!!!!!!");
        state = Start;
    }
    if (*(const char *)Data["Stop"] == '1')
    {
        state = Stop;
    }
    if (*(const char *)Data["Reset"] == '1')
    {
        state = Reset;
    }
    return (int)state;
}
