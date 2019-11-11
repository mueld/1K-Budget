#include "FirstRound.h"
#include <Arduino.h>
#ifndef Variables_h
#define Variables_h
#define EncoderPinA_L 2
#define EncoderPinB_L 4
#define EncoderPinA_R 3
#define EncoderPinB_R 5

ToF Sensors;
FirstRound Round;
Pixy2 Pixyinstance;
Objectdetection ObjectdetectionInstance;
DrivesController DrivesControllerInstance;
volatile int Encoder_Li;
volatile int Encoder_Ro;



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
