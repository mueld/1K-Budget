#include "Libarys/Variables.h"

void setup()
{
 for (int i =8 ; i < 14; i++)
    {
        pinMode(i, OUTPUT);
    }
    for (int i = 0; i < 8; i++)
    {
        pinMode(i, INPUT_PULLUP);
    }
    
    Serial.begin(115200);
    Serial1.begin(9600);
   Sensors.Setup();
   DrivesControllerInstance.Setup();
   ObjectdetectionInstance.Setup(&DrivesControllerInstance, &Pixyinstance);
    Round.Setup(&DrivesControllerInstance, &Sensors, &ObjectdetectionInstance, &AlignInstance);
    AlignInstance.Setup(&DrivesControllerInstance);
    CollectInstance.Setup(&DrivesControllerInstance, &Round);
    UnloadInstance.Setup(&DrivesControllerInstance);
    ParkingInstance.Setup(&DrivesControllerInstance, &Pixyinstance, &AlignInstance);
    attachInterrupt(0, DrivesControllerEncoderLinear, FALLING);
    attachInterrupt(1, DrivesControllerEncoderRotate, FALLING);
    Sensors.Register(&AlignInstance);
    Sensors.Register(&Round);
    Sensors.Register(&CollectInstance);
    Sensors.Register(&ParkingInstance);
     
    //SendDebugMessage("Setup finished");*/
    DrivesControllerInstance.ReadEEPROM(); //liest Encoderpositionen aus dem EEPROM
}


void loop()
{

    // DrivesControllerInstance.IBNAxis(Motor_Linear, 2);
    Sensors.Reading();
    Sensors.NotifyObserver();           //übergibt allen Observers die Messdaten der Sensoren
    MKR100Instance.Read();


    if (MKR100Instance.ActiveState() != 1)
    {
    
    switch (State)
    {
    case Process_Waiting:
        if (MKR100Instance.ActiveState() == 0)
        {
            State = Process_FirstRound;
        }
        
    break;

    case Process_FirstRound:

       Execute_FirstRound();
        break;

    case Process_Idle:
        Execute_Idle();
        break;

    case Process_Searching:
        //DrivesControllerInstance.IBNAxis(Motor_Linear, 2);
        Execute_Searching();
       // DrivesControllerInstance.MoveLeft(100);
        // AlignInstance.Print();
        break;
    case Process_ObjectFound:
        Serial.println("objekt gefunden");
        State = Process_Collect;
        break;
    case Process_Collect:
        ExecuteCollect();
        break;
    
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
        break;
    case Process_Finish:
        if(MKR100Instance.ActiveState() == 2)
        {
            Cubes = 0;
            State = Process_Waiting;

        }
        break;
        
    }
    }
    else
    {
        DrivesControllerInstance.Stay();
    }
    
    DrivesControllerInstance.UpdateEEPROM(); //schreibt alle 10ms Encoderpositionen aus dem EEPROM 
    if(OldState != State)
    {
        MKR100Instance.SendData(State, Cubes);
        OldState = State;
    }
    
}