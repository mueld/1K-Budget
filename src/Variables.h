#include "FirstRound.h"
#include <EEPROM.h>
#ifndef Variables_h
#define Variables_h
#define EncoderPinA_L 2
#define EncoderPinB_L 3
#define EncoderPinA_R 18
#define EncoderPinB_R 19

ToF Sensors;
FirstRound Round;
Pixy2 Pixyinstance;
Objectdetection ObjectdetectionInstance;
DrivesController DrivesControllerInstance;
volatile int Encoder_L;
volatile int Encoder_R;

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
void EncoderTraceA_Linear();
void EncoderTraceB_Linear();
void EncoderTraceA_Rotate();
void EncoderTraceB_Rotate();

#endif
