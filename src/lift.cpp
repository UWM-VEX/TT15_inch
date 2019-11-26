#include "main.h"

Lift::Lift() {}

Lift::Lift(uint8_t leftPort, uint8_t rightPort)
{
  motorLeft = new okapi::Motor(leftPort);
  motorLeft->setGearing(okapi::AbstractMotor::gearset::red);
  motorLeft->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

  motorRight = new okapi::Motor(rightPort);
  motorRight->setGearing(okapi::AbstractMotor::gearset::red);
  motorRight->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

Lift::~Lift()
{
  delete motorRight;
  delete motorLeft;
}

void Lift::moveLift(int speed)
{
  motorLeft->move(speed);
  motorRight->move(-speed);
}

int Lift::getLiftPos() {
  return motorLeft->get_position(); //problem line
}
