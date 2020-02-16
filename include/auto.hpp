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
	Auto(okapi::ChassisControllerIntegrated * m, okapi::ADIGyro * g);
	void turnDegrees(double degrees);
	void moveDistance(double distance);

private:
	okapi::ChassisControllerIntegrated * drive;
	okapi::ADIGyro * gyro;
	double abs(double value);
	double turnValue(double difference);
}

#endif
