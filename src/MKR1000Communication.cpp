#include "MKR1000Communication.h"
#include "Parking.h"
void MKR1000Communication::SendData(const int &ProcessState, const int &ProcessCubes)
{
    Serial1.write(ProcessState);
    Serial1.write(ProcessCubes);
}

int MKR1000Communication::Read()
{
    char Data = Serial1.read();
    int State = 0;

    if(Serial1.available() == 1)
    {
        switch (Data)
        {
            case '1':
                State = 1;  //1 = Start
                break;
            case '2':
                State = 2; //2 = Restart
                break;
            case '3':
                State = 3; //3 = Stop
                break;
        } 
    }
    
    return State;
}