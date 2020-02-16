#include "auto.hpp"

Auto::Auto(okapi::ChassisControllerIntegrated * m, okapi::ADIGyro * g)
{
  drive = m;
  gyro = g;
}

void Auto::turnDegrees(double degrees)
{
  double startDegrees = gyro->get();
  drive->turnAngle(degrees);
  double d;
  while(abs(d = gyro->get() - startDegrees) > DEGREES_MARGIN)
  {
    drive->rotate(turnValue(d));
    pros::delay(20);
  }
}


void Auto::moveDistance(double distance)
{

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
    result = 1;
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
