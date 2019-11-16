#include "Libarys/Variables.h"

void setup()
{
    Serial.begin(115200);
    DrivesControllerInstance.Setup();
    ObjectdetectionInstance.Setup(&DrivesControllerInstance, &Pixyinstance);
    Sensors.Setup();
    CollectInstance.Setup( &Sensors, &DrivesControllerInstance);
    Round.Setup(&DrivesControllerInstance, &Sensors, &ObjectdetectionInstance);
    attachInterrupt(0, DrivesControllerEncoderLinear, FALLING);
    attachInterrupt(1, DrivesControllerEncoderRotate, FALLING);
}
void loop()
{
    Sensors.Reading();

    switch (State)
    {

    case Process_Start:
            Cubes = 0;
    break;

    case Process_FirstRound:
        void FirstRound();
        break;
    case Process_Idle:
        if (Round.activeState() != FirstRound_Finish)
        {
            State = Process_FirstRound;
        }
        else if(Cubes == 6)
        {
            State = Process_Unload;
        }
        else
        {
            State = Process_Searching;
        }
    break;
        case Process_Searching:
        void Searching();
        break;

    case Process_Collect:

        if (CollectInstance.CollectThatShit())
        {
            State = Process_Idle;
        }
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