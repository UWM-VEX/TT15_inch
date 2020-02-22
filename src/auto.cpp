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
                                   {3_ft, 0_ft, 0_deg},
                                   {6_ft, 3_ft, 0_deg}}, "Red1");
}

void Auto::turnDegrees(double degrees)
{
  double startDegrees = gyro->get_rotation();
  double finalDegrees = startDegrees + degrees;
  // drive->turnAngle(okapi::QAngle(degrees));
  double d;
  while(abs(d = gyro->get_rotation() - finalDegrees) > DEGREES_MARGIN)
  {
    drive->model().rotate(turnValue(d * -.01));
    pros::delay(2);
  }

  while(abs(d = gyro->get_rotation() - finalDegrees) > DEGREES_MARGIN)
  {
    drive->model().rotate(turnValue(d * -.01));
    pros::delay(2);
  }
  drive->model().rotate(0);
}

void Auto::grabForMillis(int millis)
{
  lift->grabCube();
  pros::delay(millis);
  lift->grab(0);
}

void Auto::redAuto()
{
  driveStraight(.7);
  pros::delay(500); //go forward to tower
  driveStraight(0);
  grabForMillis(250);
}

void Auto::blueAuto()
{

}

void Auto::activate()
{
  if(Auton::selection == Auton::team::RED_TEAM)
  {
    redAuto();
  }
  else
  {
    blueAuto();
  }
}

void Auto::moveDistance(okapi::QLength distance)
{
  drive->moveDistance(distance);
}

void Auto::driveStraight(double power)
{
  double angle = gyro->get_rotation();
  drive->model().arcade(power, (gyro->get_rotation() - angle) * .04);
}

void Auto::grab(double power)
{
  lift->grab(power);
}

inline double Auto::abs(double value)
{
  return value > 0 ? value : value * -1;
}

double Auto::turnValue(double diff, double margin)
{
  if(diff > margin)
    diff = margin;
  else if(diff < -margin)
    diff = -margin;

  if(abs(diff) < .1)
  {
    if(diff < 0)
    {
      diff = .1;
    }
    else
    {
      diff = -.1;
    }
  }

  return diff;
}
