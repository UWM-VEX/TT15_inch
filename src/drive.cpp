#include "main.h"
//#include <cmath>

using namespace okapi;

Drive RobotDrive;

Drive::Drive() {}

void Drive::initDrive(int8_t middleLeftPort, int8_t backLeftPort, int8_t middleRightPort, int8_t backRightPort)
{
  middleLeft = middleLeftPort;
  backLeft = backLeftPort;

  middleRight = middleRightPort;
  backRight = backRightPort;
}

okapi::ChassisControllerIntegrated Drive::makeDrive()
{
  return ChassisControllerFactory::create(
    {middleLeft, backLeft}, {middleRight, backRight},
    AbstractMotor::gearset::green,
    {4_in, 10.5_in}
  );
}
