#include "api.h"
#include "okapi/api.hpp"
#include "pros/api_legacy.h"

class Lift15
{
public:
  Lift15(int llm, int lrm, int ulm, int urm, int am, int bgm, int fgm);
  ~Lift15();
  void moveMotorToHeight(int degrees);
  void grab(float power);
  void moveLift(float power);
  void angleGrabber(int degrees);
  void moveUp();
  void moveDown();
  void moveToCube();
<<<<<<< HEAD
  int getHeight() { return height; };
  int degrees() { return (int)lowerLeftMotor->getPosition(); }
=======
>>>>>>> 8d8e88a30b701457b2358be0021aa312ed7beea0

private:
  int heights[9];
  int angles[4];
  okapi::Motor * lowerLeftMotor;
  okapi::Motor * lowerRightMotor;
  okapi::Motor * upperLeftMotor;
  okapi::Motor * upperRightMotor;
  okapi::Motor * angleMotor;
  okapi::Motor * backGrabberMotor;
  okapi::Motor * frontGrabberMotor;
  double gearRatio;
  int height;

} typedef Lift15;
