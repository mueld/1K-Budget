#include "Libarys/Variables.h"

void setup()
{
    Serial.begin(115200);
    DrivesControllerInstance.Setup();
    ObjectdetectionInstance.Setup(&DrivesControllerInstance, &Pixyinstance);
    Sensors.Setup();
    Round.Setup(&DrivesControllerInstance, &Sensors, &ObjectdetectionInstance);
    attachInterrupt(0, DrivesControllerEncoderLinear, FALLING);
    attachInterrupt(1, DrivesControllerEncoderRotate, FALLING);
}
void loop()
{
    Sensors.ExectueStateMachine();

    switch (State)
    {

    case Process_FirstRound:
        void FirstRound();
        break;

    case Process_Searching:
        void Searching();
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

    case Process_Unload:
        /* UnloadInstance.ExecuteStateMachine();
        if(OnloadInstance.activeState() == Onload_Finish)
        {
            State = Process_Parking;
        }
        */
        break;

    case Process_Parking:
        /* ParkingInstance.ExecuteStateMachine();
        if(ParkingInstance.activeState() == Parking_Finish)
        {
            State = Process_Finish;
        }
        */
        break;
    }
}