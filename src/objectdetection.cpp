
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
            index = Camera->ccc.blocks[0].m_index;
            FirstCubeFound = true;
        }
        if (Camera->ccc.numBlocks != 0)
        {

            for (int i = 0; i < Camera->ccc.numBlocks; i++)
            {

                if (Camera->ccc.blocks[i].m_index == index)
                {
                    if (Camera->ccc.blocks[i].m_x >= 180)
                    {
                        Drivecontroller->TurnRight(100);
                    }
                    else if (Camera->ccc.blocks[i].m_x >= 160)
                    {
                        Drivecontroller->TurnRight(30);
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
            Drivecontroller->TurnRight(100);
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
                if (Camera->ccc.blocks[i].m_y >= 170 && Camera->ccc.blocks[i].m_x <= 120)
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
