#include <Pixy2.h>
#include "DrivesController.h"

#ifndef objectdetection_h
#define objectdetection_h

enum Objectstate
{
  Objectstate_Searching,
  Objectstate_found,
  Objectstate_Idle,
  Objectstate_initialize,
};
class IModuleState
{
  public:
  virtual int ActiveState();
};
class Objectdetection: public IModuleState
{
private:
  int nearest;
  int nearest_index;
  int index;
  bool FirstCubeFound;
  Objectstate state;
  Pixy2 *Camera;
  DrivesController *Drivecontroller;

public:
  void Setup(DrivesController *drivecontroller, Pixy2 *pixy);
  void ExecuteStateMachine();
  void FirstRound();
  int ActiveState();
};

#endif