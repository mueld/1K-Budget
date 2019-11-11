#include "Variables.h"

void Encoder_Linear()
{

    if (digitalRead(EncoderPinB_L) == LOW)
    {
        Encoder_Li--;
    }
    else
    {
        Encoder_Li++;
    }
}

void Encoder_Rotate()
{
    if (digitalRead(EncoderPinB_R) == LOW)
    {
        Encoder_Ro--;
    }
    else
    {
        Encoder_Ro++;
    }
}

void setup()
{
    Serial.begin(115200);
    DrivesControllerInstance.Setup(&Encoder_Li, &Encoder_Ro);
    ObjectdetectionInstance.Setup(&DrivesControllerInstance, &Pixyinstance);
    Sensors.Setup();
    Round.Setup(&DrivesControllerInstance, &Sensors, &ObjectdetectionInstance);
    
}
void loop()
{
    DrivesControllerInstance.ExecuteStateMachine();

    switch (State)
    {

    case Process_FirstRound:

        ObjectdetectionInstance.FirstRound();
        if (ObjectdetectionInstance.activestate() == Objectstate_found)
        {
            OldState = State;
            State = Process_Collect;
        }
        else if (Round.activeState() == FirstRound_Finish)
        {
            State = Process_Searching;
        }

        else if (Round.activeState() != FirstRound_Finish)
        {
            Round.ExecuteStateMachine();
            OldState = State;
        }

        break;

    case Process_Searching:

        ObjectdetectionInstance.ExecuteStateMachine();
        if (ObjectdetectionInstance.activestate() == Objectstate_found)
        {
            OldState = State;
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