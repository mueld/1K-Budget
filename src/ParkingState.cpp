#include "ParkingState.h"
#include "Unload.h"

void ParkingState::Setup(DrivesController *DriveController, Pixy2 *pixy, Align *align)
{
    Controller = DriveController;
    this->align = align;
    camera = pixy;
}

void ParkingState::ExecuteParking()
{
    camera->ccc.getBlocks();
    switch (State)
    {
    case Parking_SearchPosition:
    if (camera->ccc.numBlocks != 0)
    {
         if (camera->ccc.blocks[0].m_x >= 160)
        {
            Controller->TurnRight(120);
        }
        else
        {
            Controller->Stay();
            State = Parking_Align;
        }
    }
    else
    {
        Controller->TurnRight(70);
    }
    
    
      
        
        break;

    case Parking_Align:
        align->Execute(100);
        if(align->ActiveState() == Align_Idle)
        {
            State = Parking_GotoWall;
        }
        break;
    case Parking_GotoWall:
        if(Sensor_Data[2] > 50)
        {
            Controller->MoveForward(150);
        }
        else
        {
            Controller->Stay();
            State = Parking_Park;
        }
        
        break;
    case Parking_Park:
       if(Sensor_Data[3] > 30)
       {
           Controller->MoveLeft(180);
       }
       else
       {
           Controller->Stay();
           State = Parking_Idle;
       }
       
        break;
    }
}
int ParkingState::ActiveState()
{
    return (int)State;
}
void ParkingState::update(int Table[5])
{
    for (int i = 0; i < 5; i++)
    {
        if (Table[i] != 8190)
        {
            Sensor_Data[i] = Table[i];
        }
    }
}
