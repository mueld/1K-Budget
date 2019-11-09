#include "FirstRound.h"

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
    Process_Parking,
    Process_FirstRound
};
Processstate State;
Processstate OldState;
void setup()
{
    Serial.begin(115200);
    DrivesControllerInstance.Setup();
    ObjectdetectionInstance.Setup(DrivesControllerInstance, Pixyinstance);
    Sensors.Setup();
    Round.Setup(DrivesControllerInstance, Sensors, Pointer);
}
void loop()
{
    DrivesControllerInstance.ExecuteStateMachine();

    switch (State)
    {

    case Process_FirstRound:
        if (Pointer->activestate() != Objectstate_found || Round.activeState() != FirstRound_Finish)
        {
            Pointer->FirstRound();
            Round.ExecuteStateMachine();
            OldState = State;
        }
        else
        {
            State = Process_Collect;
        }
        break;

    case Process_Searching:
        if (Pointer->activestate() != Objectstate_found)
        {
            Pointer->ExecuteStateMachine();
            OldState = State;
        }
        else
        {
            State = Process_Collect;
        }
        break;

    case Process_Collect:
        /*if (Collect.activeState() == Finish)
        {
              State = Process_Parking;
        }
       if (Collect.activeState() != Collect && Collect.activeState() != Finish)
       {
           Collect.ExecuteStateMachine();
       }
       else 
       {
           State = OldState;
       }
        */
        break;
    }
}