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
    switch (State)
    {
        case Process_Initialize:
        break;

        case Process_Start:
        break;

        case Process_FirstRound:
        
        
        break;
        case Process_Searching:
        ObjectdetectionInstance.ExecuteStateMachine();
        if (ObjectdetectionInstance.activestate() == Objectstate_found)
        {
            State = Process_Collect;
        }
        break;
        
        case Process_Collect:

            break;
    }

    
    ObjectdetectionInstance.ExecuteStateMachine();

}