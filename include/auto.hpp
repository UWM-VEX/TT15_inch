#ifndef AUTO_H_
#define AUTO_H_

#include "main.h"

struct AutonomousInfo {

	int mode;
	int alliance;

}typedef AutonomousInfo;

extern AutonomousInfo autonomousInfoStruct;

#define DO_NOTHING 0
#define TEST 1
#define TOWERS 2
#define DEGREES_MARGIN 3

class Auto
{
public:
	Auto(okapi::ChassisControllerIntegrated * m, pros::Imu * g, Lift15 * l);
	void turnDegrees(double degrees);
	void moveDistance(okapi::QLength distance);
	void grab(double power);

private:
	okapi::ChassisControllerIntegrated * drive;
	pros::Imu * gyro;
	double abs(double value);
	double turnValue(double difference);
	Lift15 * lift;
};

#endif
