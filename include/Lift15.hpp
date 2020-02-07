#include "api.h"
#include "okapi/api.hpp"
#include "pros/api_legacy.h"

class Lift15
{
public:
  Lift15(int llm, int lrm, int ulm, int urm, int am, int bgm, int fgm);
  ~Lift15();
  void moveMotorToHeight(int degrees);
  void grab(double power);

private:
  int heights[9];
  okapi::Motor * lowerLeftMotor;
  okapi::Motor * lowerRightMotor;
  okapi::Motor * upperLeftMotor;
  okapi::Motor * upperRightMotor;
  okapi::Motor * angleMotor;
  okapi::Motor * backGrabberMotor;
  okapi::Motor * frontGrabberMotor;
  double gearRatio;

} typedef Lift15;
