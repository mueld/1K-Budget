
#include "DrivesController.h"
#include "objectdetection.h"

void Objectdetection::Setup(DrivesController *drivecontroller, Pixy2 *pixy)
{
    Drivecontroller = drivecontroller;
    Camera = pixy;
    Camera->init();
}

int Objectdetection::ActiveState()
{
    return state;
}

void Objectdetection::ExecuteStateMachine()
{
    switch (state)
    {
    case Objectstate_Searching:
        Camera->ccc.getBlocks();
        if (FirstCubeFound == false && Camera->ccc.numBlocks != 0)
        {
            for (int i = 0; i < Camera->ccc.numBlocks; i++)
            {
                if(Camera->ccc.blocks[i].m_signature == 1)
                {
                    index = Camera->ccc.blocks[i].m_index;
                    Serial.println("Ersten Cube gefunden");
                    FirstCubeFound = true;
                }
            }
            
            
        }
        if (Camera->ccc.numBlocks != 0 && FirstCubeFound == true)
        {
            for (int i = 0; i < Camera->ccc.numBlocks; i++)
            {
                if (Camera->ccc.blocks[i].m_index == index)
                {
                    if (Camera->ccc.blocks[i].m_x >= 200)
                    {
                        Drivecontroller->TurnRight(50);
                    }
                    else if (Camera->ccc.blocks[i].m_x >= 160)
                    {
                        Drivecontroller->TurnRight(40);
                    }
                    else
                    {
                        Drivecontroller->Stay();
                        FirstCubeFound = false;
                        state = Objectstate_found;
                    }
                }
            }
        }
        else
        {
            Drivecontroller->TurnRight(70);
        }
        break;

    case Objectstate_found:

        state = Objectstate_Searching;
        break;
    }
}

void Objectdetection::FirstRound()
{
    Camera->ccc.getBlocks();

    switch (state)
    {
    case Objectstate_Searching:

        if (Camera->ccc.numBlocks != 0)
        {
            for (int i = 0; i < Camera->ccc.numBlocks; i++)
            {
                if (Camera->ccc.blocks[i].m_y >= 170 && Camera->ccc.blocks[i].m_x <= 120 && (Camera->ccc.blocks[i].m_signature == 1))
                {
                    Drivecontroller->Stay();
                    state = Objectstate_found;
                }
            }
            break;

        case Objectstate_found:
            state = Objectstate_Searching;
            break;
        }
    }
}
