#ifndef AUTO_H_
#define AUTO_H_

#include "main.h"

struct AutonomousInfo {

	int mode;
	int alliance;

}typedef AutonomousInfo;

extern AutonomousInfo autonomousInfoStruct;
namespace Auton
{
	enum class team {RED_TEAM, BLUE_TEAM};
	static team selection = team::RED_TEAM;
}

#define DO_NOTHING 0
#define TEST 1
#define TOWERS 2
#define DEGREES_MARGIN 1

class Auto
{
public:
	Auto(std::shared_ptr<okapi::ChassisController> & d, pros::Imu * g, Lift15 * l);
	void turnDegrees(double degrees);
	void moveDistance(okapi::QLength distance);
	void grab(double power);
	void redAuto();
	void blueAuto();
	void driveStraight(double power);
	void activate();
	void grabForMillis(int millis, int power = 12000);

private:
	std::shared_ptr<okapi::ChassisController> drive;
	pros::Imu * gyro;
	double abs(double value);
	double turnValue(double difference, double margin = .7);
	Lift15 * lift;
};


#endif
