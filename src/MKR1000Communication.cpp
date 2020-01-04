#include "MKR1000Communication.h"
#include "Parking.h"
void MKR1000Communication::SendData(const int &ProcessState, const int &ProcessCubes)
{
    Serial1.write(ProcessState);
    Serial1.write(ProcessCubes);
}

bool MKR1000Communication::Read()
{
    bool result = false;
    if(Serial1.available() == 1)
    {
        if(Serial.read() == '1')
        {
            result = true;
        }
    }
    return result;
}