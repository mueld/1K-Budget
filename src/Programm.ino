#include "Libarys/Variables.h"

void setup()
{
 for (int i =8 ; i < 13; i++)
    {
        pinMode(i, OUTPUT);
    }
    for (int i = 0; i < 8; i++)
    {
        pinMode(i, INPUT_PULLUP);
    }
    
    Serial.begin(115200);
    //Serial1.begin(9600);
   Sensors.Setup();
   DrivesControllerInstance.Setup();
   ObjectdetectionInstance.Setup(&DrivesControllerInstance, &Pixyinstance);
    Round.Setup(&DrivesControllerInstance, &Sensors, &ObjectdetectionInstance, &AlignInstance);
    AlignInstance.Setup(&DrivesControllerInstance);
    CollectInstance.Setup(&DrivesControllerInstance);
    UnloadInstance.Setup(&DrivesControllerInstance);
    ParkingInstance.Setup(&DrivesControllerInstance, &Pixyinstance, &AlignInstance);
    attachInterrupt(0, DrivesControllerEncoderLinear, FALLING);
    attachInterrupt(1, DrivesControllerEncoderRotate, FALLING);
    Sensors.Register(&AlignInstance);
    Sensors.Register(&Round);
    Sensors.Register(&CollectInstance);
    Sensors.Register(&ParkingInstance);
     
    //SendDebugMessage("Setup finished");*/
    DrivesControllerInstance.ReadEEPROM();
   
}



void loop()
{
    Serial.print("Encoder:");
    DrivesControllerInstance.PrintEncoder(Motor_Linear);
    //DrivesControllerInstance.IBNAxis(Motor_Linear, 2);
    Sensors.Reading();
    Sensors.NotifyObserver();

    switch (State)
    {
    case Process_Waiting:
        if (MKR100Instance.Read())
        {
            State = Process_FirstRound;
        }
        
    break;

    case Process_FirstRound:

       Execute_FirstRound();
        break;

    case Process_Idle:
    //    Execute_Idle();
        break;

    case Process_Searching:
    Execute_Searching();
        break;
    case Process_ObjectFound:
        Serial.println("objekt gefunden");
        State = Process_Collect;
        break;
    case Process_Collect:
        ExecuteCollect();
        break;
    /*
    case Process_CollectedCube:
        State = Process_Idle;
        break;
    case Process_Unload:
        ExecuteUnload();
        break;
    case Process_UnloadedCubes:
        State = Process_Finish;
        break;
    case Process_Parking:
        ExectueParking();
        break;*/
    //}
    // MKR100Instance.SendData(State, Cubes);
    }
    DrivesControllerInstance.UpdateEEPROM();
}