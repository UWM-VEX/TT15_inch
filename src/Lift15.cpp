#include "Lift15.hpp"

Lift15::Lift15(int llm, int lrm, int ulm, int urm, int am, int bgm, int fgm)
{
  lowerLeftMotor = new okapi::Motor(llm);
  lowerLeftMotor->setGearing(okapi::AbstractMotor::gearset::red);
  lowerLeftMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  lowerRightMotor = new okapi::Motor(lrm);
  lowerRightMotor->setGearing(okapi::AbstractMotor::gearset::red);
  lowerRightMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  upperLeftMotor = new okapi::Motor(ulm);
  upperLeftMotor->setGearing(okapi::AbstractMotor::gearset::red);
  upperLeftMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  upperRightMotor = new okapi::Motor(urm);
  upperRightMotor->setGearing(okapi::AbstractMotor::gearset::red);
  upperRightMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  angleMotor = new okapi::Motor(am);
  angleMotor->setGearing(okapi::AbstractMotor::gearset::green);
  angleMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  backGrabberMotor = new okapi::Motor(bgm);
  backGrabberMotor->setGearing(okapi::AbstractMotor::gearset::green);
  backGrabberMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
  frontGrabberMotor = new okapi::Motor(fgm);
  frontGrabberMotor->setGearing(okapi::AbstractMotor::gearset::green);
  frontGrabberMotor->setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);

  gearRatio = .5; //the ratio between how much the angle motor needs to move releative to the
                  //lift motors

  heights[0] = 0; //zero height
  heights[1] = 170; //max height
  heights[2] = 330; //cube 3
  heights[3] = 470; //cube 4
  heights[4] = 620; //cube 5
  heights[5] = 850; //max height

  heights[6] = 730; //mid tower
  heights[7] = 550; //lower tower
  heights[8] = 50;  //raise over corner border

  angles[0] = 0;
  angles[1] = 260; //straight down
  angles[2] = 40; //angled up.

  height = 0;
}

Lift15::~Lift15()
{
  delete lowerLeftMotor;
  delete lowerRightMotor;
  delete upperLeftMotor;
  delete upperRightMotor;
  delete angleMotor;
  delete backGrabberMotor;
  delete frontGrabberMotor;
}

void Lift15::moveMotorToHeight(int degrees)
{
  lowerLeftMotor->moveAbsolute(-degrees, 60);
  lowerRightMotor->moveAbsolute(degrees, 60);
  upperLeftMotor->moveAbsolute(degrees, 60);
  upperRightMotor->moveAbsolute(-degrees, 60);
  //angleMotor->moveAbsolute((int)(degrees * gearRatio), 60);
}

void Lift15::moveToCube()
{
  moveMotorToHeight(heights[height]);
}

void Lift15::angleGrabber(int degrees)
{
  angleMotor->moveAbsolute(degrees, 60);
}

void Lift15::grab(float power)
{
  int ipower = (int) (power * 12000);
  frontGrabberMotor->moveVoltage(ipower); //make sure to adjust
  backGrabberMotor->moveVoltage(-ipower);
}

void Lift15::moveLift(float power)
{
  int ipower = (int) (power * 12000);
  lowerLeftMotor->moveVoltage(-ipower);
  lowerRightMotor->moveVoltage(ipower);
  upperLeftMotor->moveVoltage(ipower);
  upperRightMotor->moveVoltage(-ipower);
}

void Lift15::moveUp()
{
  if(height < 5) ++height;
}

void Lift15::moveDown()
{
  if(height > 1) --height;
}
