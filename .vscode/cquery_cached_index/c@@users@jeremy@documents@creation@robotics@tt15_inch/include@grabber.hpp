#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

#define INTAKE_IN 0
#define INTAKE_OUT 1
#define INTAKE_STOP 2

#include "main.h"

class Intake{
private:
  pros::Motor* grabber;
public:
  Intake();
  void initIntake(int grabberPort);
  void set(int speed);
  void printMotorTemps();
};

extern Intake robotIntake;

#endif
