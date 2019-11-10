#include "FirstRound.h"

#ifndef Variables_h
#define Variables_h
ToF Sensors;
FirstRound Round;
Pixy2 Pixyinstance;
Objectdetection ObjectdetectionInstance;
Objectdetection *Pointer = &ObjectdetectionInstance;
DrivesController DrivesControllerInstance;

enum Processstate
{
    Process_Initialize,
    Process_Start,
    Process_Searching,
    Process_Collect,
    Process_Unload,
    Process_Parking,
    Process_FirstRound,
    Process_Finish
};

Processstate State;
Processstate OldState;
#endif
