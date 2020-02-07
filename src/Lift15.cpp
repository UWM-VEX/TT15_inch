#include "Lift15.hpp"

Lift15::Lift15(int llm, int lrm, int ulm, int urm, int am, int gm)
{
  lowerLeftMotor = new okapi::Motor(llm);
  lowerLeftMotor->setGearing(okapi::AbstractMotor::gearset::green);
  lowerLeftMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  lowerRightMotor = new okapi::Motor(lrm);
  lowerRightMotor->setGearing(okapi::AbstractMotor::gearset::green);
  lowerRightMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  upperLeftMotor = new okapi::Motor(ulm);
  upperLeftMotor->setGearing(okapi::AbstractMotor::gearset::green);
  upperLeftMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  upperRightMotor = new okapi::Motor(urm);
  upperRightMotor->setGearing(okapi::AbstractMotor::gearset::green);
  upperRightMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  angleMotor = new okapi::Motor(am);
  angleMotor->setGearing(okapi::AbstractMotor::gearset::green);
  angleMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  grabberMotor = new okapi::Motor(gm);
  grabberMotor->setGearing(okapi::AbstractMotor::gearset::green);
  grabberMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

  gearRatio = .5; //the ratio between how much the angle motor needs to move releative to the
                  //lift motors

  heights[0] = 0; //zero height
  heights[1] = 190; //cube 2
  heights[2] = 330; //cube 3
  heights[3] = 470; //cube 4
  heights[4] = 620; //cube 5
  heights[5] = 840; //cube 6
  heights[6] = 730; //mid tower
  heights[7] = 550; //lower tower
  heights[8] = 50;  //raise over corner border
}

Lift15::~Lift15()
{
  delete lowerLeftMotor;
  delete lowerRightMotor;
  delete upperLeftMotor;
  delete upperRightMotor;
  delete angleMotor;
  delete grabberMotor;
}

void Lift15::moveMotorToHeight(int degrees)
{
  lowerLeftMotor->moveAbsolute(-degrees, 60);
  lowerRightMotor->moveAbsolute(-degrees, 60);
  upperLeftMotor->moveAbsolute(degrees, 60);
  upperRightMotor->moveAbsolute(degrees, 60);
  angleMotor->moveAbsolute((int)(degrees * gearRatio), 60);
}

void Lift15::grab(int power)
{
  grabberMotor->moveVoltage(power); //make sure to adjust
}
