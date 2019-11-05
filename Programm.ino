#include "objectdetection.h"
#include <Wire.h>
Adafruit_MotorShield AFMS1 = Adafruit_MotorShield(0x60);
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

void setup()
{
    Serial.begin(115200);
    DrivesControllerInstance.Setup(AFMS1);
    ObjectdetectionInstance.Setup(DrivesControllerInstance, Pixyinstance);
}
void loop()
{
    switch (Processstate)
    {
        case Process_Initialize:
        break;

        case Process_Start:
        break;

        case Process_FirstRound:
        FirstRound.ExecuteStateMachine();
        if(FirstRound.activeState() == Finish)
        {
            Processstate = Process_Searching;
        }
        break;
        case Process_Searching:
        ObjectdetectionInstance.ExecuteStateMachine();
        if(Objectdetection.activeState()==Objectstate_found)
        {
            Processstate = Process_Collect;
        }
        break;
        
        case Process_Collect:
        Collect.ExecuteStateMachine();
        if(Collect.activeState() == Collect_Finish)
        {
            Processstate = Process_Searching;
        }
    }

    
    ObjectdetectionInstance.ExecuteStateMachine();

}