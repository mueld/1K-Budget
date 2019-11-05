
#include "DrivesController.h"
#include "objectdetection.h"

    void Objectdetection::Setup(DrivesController drivecontroller, Pixy2 pixy)
    {
        Drivecontroller = &drivecontroller;
        Camera = &pixy;
        Camera->init();
    }

    Objectstate Objectdetection::activestate()
    {
        return state;
    }

    void Objectdetection::ExecuteStateMachine()
    {
        switch (state)
        {
        case Objectstate_Searching:
            if (Camera->ccc.numBlocks != 0)
            {
                
                if (Camera->ccc.blocks[0].m_x  >= 180)
                {
                    
                    DrivesControllerCommmand = TurnRight;
                    Drivecontroller->setCommand(DrivesControllerCommmand, 255);
                }
                else if (Camera->ccc.blocks[0].m_x  >= 160)
                {
                    DrivesControllerCommmand = TurnRight;
                    Drivecontroller->setCommand(DrivesControllerCommmand, 150);
                }
                else
                {
                    DrivesControllerCommmand = Stay;
                    Drivecontroller->setCommand(DrivesControllerCommmand, 0);
                    state = Objectstate_Select;
                }
            }
            else

            {
                
                DrivesControllerCommmand = TurnRight;
                Drivecontroller->setCommand(DrivesControllerCommmand, 255);
            }

            break;

        case Objectstate_Select:
            if (Camera->ccc.numBlocks == 1)
            {
                state = Objectstate_found;
            }
            
            nearest = Camera->ccc.blocks[0].m_y ;

            for (int i = 0; i <= Camera->ccc.numBlocks; i++)
            {
                if (Camera->ccc.blocks[i].m_y  > nearest)
                {
                    nearest = Camera->ccc.blocks[i].m_y;
                    nearest_index = i;
                 
                    state = Objectstate_NewPosition;
                }
            }
            break;

        case Objectstate_NewPosition:
            

            if (Camera->ccc.blocks[nearest_index].m_x >= 180)
            {
                DrivesControllerCommmand = TurnRight;
                Drivecontroller->setCommand(DrivesControllerCommmand, 255);
            }

            else if (Camera->ccc.blocks[nearest_index].m_x >= 160)
            {
                DrivesControllerCommmand = TurnRight;
                    Drivecontroller->setCommand(DrivesControllerCommmand, 120);
            }
            else
            {
                DrivesControllerCommmand = Stay;
                   Drivecontroller->setCommand(DrivesControllerCommmand, 0);
                state = Objectstate_found;
            }
            break;

        case Objectstate_found:
            state = Objectstate_Searching;
            break;
        }
    }
