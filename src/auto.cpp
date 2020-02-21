#include "auto.hpp"

using namespace okapi;

std::shared_ptr<okapi::AsyncMotionProfileController> profileController;

okapi::Timer stopwatch;

Auto::Auto(std::shared_ptr<okapi::ChassisController> & m, pros::Imu * g, Lift15 * l)
{
  drive = m;
  gyro = g;
  lift = l;
  profileController =
    okapi::AsyncMotionProfileControllerBuilder()
      .withLimits({1.0, 2.0, 10.0})
      .withOutput(drive)
      .buildMotionProfileController();

  profileController->generatePath({{0_ft, 0_ft, 0_deg},
                                   {3_ft, 0_ft, 0_deg}}, "Red");
}

void Auto::turnDegrees(double degrees)
{
  double startDegrees = gyro->get_rotation();
  double finalDegrees = startDegrees + degrees;
  drive->turnAngle(okapi::QAngle(degrees));
  double d;
  while(abs(d = gyro->get_rotation() - finalDegrees) > DEGREES_MARGIN)
  {
    drive->model().rotate(turnValue(d));
    pros::delay(20);
  }
}

void Auto::redAuto()
{
  profileController->setTarget("Red");

}

void Auto::blueAuto()
{

}

void Auto::moveDistance(okapi::QLength distance)
{
  drive->moveDistance(distance);
}

void Auto::grab(double power)
{
  lift->grab(power);
}

inline double Auto::abs(double value)
{
  return value > 0 ? value : value * -1;
}

double Auto::turnValue(double diff)
{
  double result = 0;
  double absDiff = abs(diff);
  if(absDiff > 60)
  {
    result = .75;
  }
  else if(absDiff > 30)
  {
    result = .5;
  }
  else if(absDiff > 15)
  {
    result = .15;
  }
  else
  {
    result = .1;
  }

  return diff > 0 ? -result : result;
}
