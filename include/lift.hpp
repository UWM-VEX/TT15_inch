#ifndef _LIFT_HPP_
#define _LIFT_HPP_

#include "main.h"

class Lift{
  okapi::Motor * motorLeft;
  okapi::Motor * motorRight;
public:
  Lift();
  ~Lift();
  Lift(uint8_t leftPort, uint8_t rightPort);
  void mMotorUp();
  void mMotorDown();
  void MotorPos1();
  void MotorPos2();
  void MotorPos3();
  void MotorPos4();
  void MotorPos5();
  void TowerLow();
  void TowerMid();
  void Jump();
  int getLiftPos();
  void moveLift(int speed);
} typedef Lift;

#endif
