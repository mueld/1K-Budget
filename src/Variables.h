#include "FirstRound.h"

#ifndef Variables_h
#define Variables_h
#define EncoderPinA_L 2
#define EncoderPinA_R 3
#define EncoderPinB_L 4
#define EncoderPinB_R 5

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

void EncoderRotate()
{
    if(EncoderPinB_R == LOW)
{
    Encoder_R--;
}
else
{
    Encoder_R++;
}

}


void EncoderLinear()
{
if (EncoderPinB_L == LOW)
{
    Encoder_L--;
}
else
{
    Encoder_L++;
}
}
#endif
