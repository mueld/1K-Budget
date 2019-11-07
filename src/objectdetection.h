#include <Pixy2.h>
#include <DrivesController.h>

#ifndef objectdetection_h
#define objectdetection_h

enum Objectstate
{
  Objectstate_Searching,
  Objectstate_found,
  Objectstate_Idle,
  Objectstate_NewPosition,
  Objectstate_Select,
  Objectstate_initialize,
  Objectstate_FirstRound
};

class Objectdetection
{
private:
  int nearest;
  int nearest_index;
  Objectstate state;
  Pixy2 *Camera;
  DrivesController *Drivecontroller;
  Command DrivesControllerCommmand;

public:
  void Setup(DrivesController drivecontroller, Pixy2 pixy);
  Objectstate activestate();
  void ExecuteStateMachine();
};

#endif