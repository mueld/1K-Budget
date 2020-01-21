#include "Libarys/Variables.h"

void setup()
{
//  for (int i =7 ; i < 8; i++)
//     {
//         pinMode(i, OUTPUT);
//     }
    for (int i = 0; i < 8; i++)
    {
        pinMode(i, INPUT_PULLUP);
    }
    pinMode(12, INPUT_PULLUP);
    Serial.begin(115200);
    //Serial1.begin(9600);
   // Sensors.Setup();
    DrivesControllerInstance.Setup();
   /* /* ObjectdetectionInstance.Setup(&DrivesControllerInstance, &Pixyinstance);
    Round.Setup(&DrivesControllerInstance, &Sensors, &ObjectdetectionInstance, &AlignInstance);
    AlignInstance.Setup(&DrivesControllerInstance);
    CollectInstance.Setup(&DrivesControllerInstance);
    UnloadInstance.Setup(&DrivesControllerInstance);
    ParkingInstance.Setup(&DrivesControllerInstance, &Pixyinstance, &AlignInstance); */
    attachInterrupt(0, DrivesControllerEncoderLinear, FALLING);
    attachInterrupt(1, DrivesControllerEncoderRotate, FALLING);
    /* Sensors.Register(&AlignInstance);
    Sensors.Register(&Round);
    Sensors.Register(&CollectInstance);
    Sensors.Register(&ParkingInstance);
     */
    //SendDebugMessage("Setup finished");*/
   // DrivesControllerInstance.ReadEEPROM();
}



void loop()
{
    //DrivesControllerInstance.setPosition(Motor_Linear, Position_StrokeMovingHome);
    DrivesControllerInstance.MoveLeft(100);
    DrivesControllerInstance.PrintEncoder(Motor_Linear);
    DrivesControllerInstance.IBNAxis(Motor_Rotate);
    // Sensors.Reading();
    //Sensors.NotifyObserver();
    /*
    switch (State)
    {
    case Process_Waiting:
        if (MKR100Instance.Read())
        {
            State = Process_FirstRound;
        }
        
    break;

    case Process_FirstRound:
       // DrivesControllerInstance.MoveLeft(100);
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
        Serial.print("Sensor Front:");
        Serial.println(CollectInstance.Sensor_Data[2]);
        ExecuteCollect();
        break;*/
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
    DrivesControllerInstance.UpdateEEPROM();
}