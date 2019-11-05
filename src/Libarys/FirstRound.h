#include "DrivesController.h"
#include "Collect.h"

enum Collectstate
{
    Collect_Position,
    Collect_Execute,
    Collect_Finish
};

class Collect
{
    private: 
    Collectstate State;
    
}