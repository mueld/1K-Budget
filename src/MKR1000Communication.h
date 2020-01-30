#ifndef MKR1000Communication_h
#define MKR1000Communication_h
#include "Parking.h"
#define STATE_INDEX 0
#define CUBES_INDEX 1

class MKR1000Communication
{
    private:
       

    public:
        void SendData(const int &ProcessState, const int &ProcessCubes);
        int Read();
};

#endif