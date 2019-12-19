#include "Parking.h"
#include "Unload.h"

void Parking::Setup(DrivesController *DriveController, Objectdetection *objectdetection, ToF *Sensors, Pixy2 *pixy, Align *align)
{
    Controller = DriveController;
    Detection = objectdetection;
    this->align = align;
    Sensor = Sensors;
    camera = pixy;
}

void Parking::ExecuteParking()
{
    camera->ccc.getBlocks();
    switch (State)
    {
    case Parking_SearchPosition:
        if (camera->ccc.numBlocks[0].m_x >=160)
        {
            Controller->TurnRight(100);
        }
        break;

    case Parking_Align:
        align->Execute(600);
        if(align->ActiveState == Align_Idle)
        {
            State = Parking_GotoWall;
        }
        break;
    case Parking_GotoWall:
        if(Sensor->Table_Measure_Data[2] >10)
        {
            Controller->MoveForward(100);
        }
        else
        {
            Controller->Stay();
            State = Parking_Park;
        }
        
        break;
    case Parking_Park:
        align->Execute(960);
        if (align->ActiveState()== Align_Idle)
        {
            State = Parking_Idle;
        }
        break;
    }
}
int Parking::ActiveState()
{
    return State;
}