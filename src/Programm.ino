#include "Libarys/Variables.h"

void setup()
{
    for (int i = 3; i < 8; i++)
    {
        pinMode(i, OUTPUT);
    }
        Serial.begin(115200);
    DrivesControllerInstance.Setup();
    ObjectdetectionInstance.Setup(&DrivesControllerInstance, &Pixyinstance);
    Round.Setup(&DrivesControllerInstance, &Sensors, &ObjectdetectionInstance, &AlignInstance);
    Sensors.Setup();
    AlignInstance(&DrivesControllerInstance);
    CollectInstance.Setup(&Sensors, &DrivesControllerInstance);
    UnloadInstance.Setup(&DrivesControllerInstance, &Sensors);
    ParkingInstance.Setup(&DrivesControllerInstance, &ObjectdetectionInstance, &Sensors);

    attachInterrupt(0, DrivesControllerEncoderLinear, FALLING);
    attachInterrupt(1, DrivesControllerEncoderRotate, FALLING);
    Sensors.Register(&AlignInstance);
    Sensors.Register(&Round);
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
        Execute_FirstRound();
        break;

    case Process_Idle:
        Execute_Idle();
        break;

    case Process_Searching:
        Execute_Searching();
        break;

    case Process_Collect:
        ExectueCollect();
        break;

    case Process_Unload:
        ExecuteUnload();
        break;

    case Process_Parking:
        ExectueParking();
        break;
    }

}