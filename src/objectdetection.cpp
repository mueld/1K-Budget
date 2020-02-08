
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
    Camera->ccc.getBlocks();
    switch (state)
    {
    case Objectstate_Searching:
        
        //Ersten Würfel suchen da Pixy Objekte nach grösse sortiert.
        if (FirstCubeFound == false && Camera->ccc.numBlocks != 0)
        {
            for (int i = 0; i < Camera->ccc.numBlocks; i++)
            {
                if(Camera->ccc.blocks[i].m_signature == 1)
                {
                    index = Camera->ccc.blocks[i].m_index;
                    Serial.println("Ersten Cube gefunden");
                    Serial.print("Index:");
                    Serial.println(index);
                    FirstCubeFound = true;
                }
            }
            
            
        }
        //Wenn der erste Würfel gfunden wurde 
        if (Camera->ccc.numBlocks != 0 && FirstCubeFound == true)
        {
            for (int i = 0; i < Camera->ccc.numBlocks; i++)
            {
                if (Camera->ccc.blocks[i].m_index == index)
                {
                    Serial.print("Index: ");
                    Serial.println(index);

                    if (Camera->ccc.blocks[i].m_x >= 200)
                    {
                        Drivecontroller->TurnRight(130);
                    }
                    else if (Camera->ccc.blocks[i].m_x >= 165)
                    {
                        Drivecontroller->TurnRight(30);
                    }
                    else if (Camera->ccc.blocks[i].m_x <= 155)
                    {
                        Drivecontroller->TurnLeft(30);
                        return;
                    }
                    
                    else
                    {
                        Serial.println("bin in else nacht m_index ");
                        Drivecontroller->Stay();
                        state = Objectstate_MovingForward;
                        Starttime = millis();
                    }
                }
            }
        }
        else
        {
            Drivecontroller->TurnRight(150);
        }
        break;
    case Objectstate_found:
        FirstCubeFound = false;
        state = Objectstate_Searching;
        break;
    case Objectstate_MovingForward:
        Serial.println("Objectstate moving forward!!!!!!");
        if (millis() - Starttime < 500)
        {
            for (int i = 0; i < Camera->ccc.numBlocks; i++)
            {
                if (Camera->ccc.blocks[i].m_index == index)
                {
                    if (Camera->ccc.blocks[i].m_y <= 130)
                    {
                        Drivecontroller->MoveForward(100);
                    }
                    else
                    {
                        Serial.println("Objectstate found pos: 210!!!!!!");
                        state = Objectstate_found;
                    }
                    
                }
            }
        }
       else
       {
           state = Objectstate_Searching;
       }
       
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
