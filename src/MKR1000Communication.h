#ifndef MKR1000Communication_h
#define MKR1000Communication_h
#include "Parking.h"
#include <Arduino_JSON.h>
#define STATE_INDEX 0
#define CUBES_INDEX 1

enum WebserverState
{
    Start,
    Stop,
    Reset,
    undef
};
class MKR1000Communication
{
    private:
        unsigned long starttime = millis();
        String Response;
        WebserverState state = undef;
        JSONVar Data;

    public:
        void
        SendData(const int ProcessState, const int ProcessCubes);
        bool Read();
        int ActiveState();
};

#endif