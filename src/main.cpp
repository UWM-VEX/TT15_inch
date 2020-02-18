#include "main.h"

#define _DIGITAL_SENSOR_PORT_ 'G'
int lowerLeftMotor = 20;
int upperLeftMotor = 15;
int lowerRightMotor = 13;
int upperRightMotor = 14;
int8_t backLeftMotor = 1;
int8_t frontLeftMotor = 9;
int8_t backRightMotor = 2;
int8_t frontRightMotor = 10;
int angleMotor = 8;
int frontGrabMotor = 11;
int backGrabMotor = 12;
int visionSensor = 4;
int gyroPort = 3;

// pros::Vision sensor(visionSensor);
using namespace okapi;

auto myChassis = okapi::ChassisControllerFactory::create(
	{backLeftMotor,frontLeftMotor}, {(int8_t)-backRightMotor,(int8_t)-frontRightMotor},
	okapi::AbstractMotor::gearset::green,
	{4_in, 10.75_in}
);

pros::Imu gyro(gyroPort);

Lift15 lift = Lift15(lowerLeftMotor, lowerRightMotor, upperLeftMotor, upperRightMotor, angleMotor, backGrabMotor, frontGrabMotor);

void initialize() {
	pros::lcd::initialize();
	//pros::lcd::initialize();
	//pros::lcd::set_text(1, "Hello PROS User!");

	//pros::lcd::register_btn1_cb(on_center_button);
	RobotDrive.initDrive(frontLeftMotor,backLeftMotor,-frontRightMotor,-backRightMotor);
	// gyro.reset();

//	lcdModeSelect();
}

void disabled() {}


void competition_initialize() {}


void autonomous() {
	Auto a(& myChassis, & gyro, & lift);
	a.moveDistance(3_ft);
	a.turnDegrees(90);
}


void opcontrol() {
	okapi::Controller master;
	okapi::Controller partner(okapi::ControllerId::partner);
	//declare chassis drive
	//okapi::ChassisControllerIntegrated opcontrolDrive = RobotDrive.makeDrive();

	int control = 1;


	while(true){

		pros::lcd::print(0, "%d %d", lift.getHeight(), lift.degrees());

		pros::lcd::print(1, "%d %d %d", (int)gyro.get_pitch(), (int)gyro.get_yaw(), (int)gyro.get_roll());

		switch (control) {
			case 1:
				control1(master, partner);
				break;
			case 2:
				control2(master, partner);
				break;
			case 3:
				control3(master, partner);
				break;
			case 4:
				control4(master, partner);
				break;
		}

		pros::delay(20);
	}
}

void control1(okapi::Controller & master, okapi::Controller & partner)
{

	static bool pUpOnLast = false, pDownOnLast = false;

	float leftX = master.getAnalog(okapi::ControllerAnalog::leftX);
	float leftY = master.getAnalog(okapi::ControllerAnalog::leftY);
	float rightX = master.getAnalog(okapi::ControllerAnalog::rightX);
	float rightY = master.getAnalog(okapi::ControllerAnalog::rightY);

	myChassis.arcade(leftY, leftX);
	//opcontrolDrive.arcade(leftY, leftX);
	lift.grab(rightY);


	double pLeftY= partner.getAnalog(okapi::ControllerAnalog::leftY);
	// lift.moveLift(pLeftY);
	// lift.moveMotorToHeight((partner.getDigital(okapi::ControllerDigital::A)) ? 850 : 0);

	bool upOn = partner.getDigital(ControllerDigital::up);
	bool downOn = partner.getDigital(ControllerDigital::down);

	if(!pUpOnLast && upOn)
	{
		lift.moveUp();
		pUpOnLast = true;
	}
	else if(!upOn && pUpOnLast)
	{
		pUpOnLast = false;
	}

	if(!pDownOnLast && downOn)
	{
		lift.moveDown();
		pDownOnLast = true;
	}
	else if(!downOn && pDownOnLast)
	{
		pDownOnLast = false;
	}

	lift.moveToCube();
	int deg = 0;
	if(partner.getDigital(okapi::ControllerDigital::X))
	{
		deg = 40;
	}
	else if(partner.getDigital(okapi::ControllerDigital::B))
	{
		deg = 260;
	}
	lift.angleGrabber(deg);
}

void control2(okapi::Controller & master, okapi::Controller & partner)
{

}

void control3(okapi::Controller & master, okapi::Controller & partner)
{

}

void control4(okapi::Controller & master, okapi::Controller & partner)
{

}
