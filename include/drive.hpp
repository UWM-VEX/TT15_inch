#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"

class Drive{
private:
  int8_t middleRight;
  int8_t backRight;
  int8_t middleLeft;
  int8_t backLeft;
public:
  Drive();
  void initDrive(int8_t middleRightPort, int8_t backRightPort, int8_t middleLeftPort, int8_t backLeftPort);
  okapi::ChassisControllerIntegrated makeDrive();
};

extern Drive RobotDrive;

#endif
