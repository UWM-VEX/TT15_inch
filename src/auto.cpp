#include "auto.hpp"

Auto::Auto(okapi::ChassisControllerIntegrated * m, pros::Imu * g, Lift15 * l)
{
  drive = m;
  gyro = g;
  lift = l;
}

void Auto::turnDegrees(double degrees)
{
  double startDegrees = gyro->get_rotation();
  double finalDegrees = startDegrees + degrees;
  drive->turnAngle(degrees);
  double d;
  while(abs(d = gyro->get_rotation() - finalDegrees) > DEGREES_MARGIN)
  {
    drive->rotate(turnValue(d));
    pros::delay(20);
  }
}

void Auto::moveDistance(okapi::QLength distance)
{
  drive->moveDistance(distance);
}

void Auto::grab(double power)
{
  lift->grab(power);
}

double Auto::abs(double value)
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
