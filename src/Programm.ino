#include "objectdetection.h"
#include <Wire.h>

Pixy2 Pixyinstance;
Objectdetection ObjectdetectionInstance;
DrivesController DrivesControllerInstance;

enum Processstate
{
    Process_Initialize,
    Process_Start,
    Process_Searching,
    Process_Collect,
    Process_Parking,
    Process_FirstRound
};
Processstate State;
void setup()
{
    Serial.begin(115200);
    DrivesControllerInstance.Setup();
    ObjectdetectionInstance.Setup(DrivesControllerInstance, Pixyinstance);
}
void loop()
{
    
}