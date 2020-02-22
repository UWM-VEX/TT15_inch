#include "main.h"

#define _DIGITAL_SENSOR_PORT_ 'G'
int lowerLeftMotor = 20;
int upperLeftMotor = 15;
int lowerRightMotor = 14;
int upperRightMotor = 5;
int8_t backLeftMotor = 1;
int8_t frontLeftMotor = 9;
int8_t backRightMotor = 2;
int8_t frontRightMotor = 10;
int angleMotor = 8;
int frontGrabMotor = 12;
int backGrabMotor = 13;
int visionSensor = 4;
int gyroPort = 3;

// pros::Vision sensor(visionSensor);
using namespace okapi;


auto myChassis = okapi::ChassisControllerBuilder().withMotors({backLeftMotor, frontLeftMotor}, {(std::int8_t)-backRightMotor, (std::int8_t)-frontRightMotor}).withDimensions(
	okapi::AbstractMotor::gearset::green, {{4_in, 10.75_in}, imev5GreenTPR}).build();

// okapi::Motor backLeft(backLeftMotor, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
// okapi::Motor frontLeft(frontLeftMotor, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
// okapi::Motor backRight(backRightMotor, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
// okapi::Motor frontRight(frontRightMotor, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
// okapi::MotorGroup left({backLeft, frontLeft});
// okapi::MotorGroup right({backRight, frontRight});
// okapi::SkidSteerModel drive(left, right, left.getEncoder(), right.getEncoder(), 1., 12000.);

pros::Imu gyro(gyroPort);

Lift15 lift = Lift15(lowerLeftMotor, lowerRightMotor, upperLeftMotor, upperRightMotor, angleMotor, backGrabMotor, frontGrabMotor);

Auto auton(myChassis, & gyro, & lift);

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(4, (Auton::selection == Auton::team::RED_TEAM) ? "Current alliance: Red" : "Current alliance: Blue");
	pros::lcd::set_text(5, "_____________Alliance_____________");
	pros::lcd::set_text(6, "_Red_______________________Blue_");
	pros::lcd::register_btn0_cb(left);
	pros::lcd::register_btn2_cb(right);

	//pros::lcd::register_btn1_cb(on_center_button);
	// RobotDrive.initDrive(frontLeftMotor,backLeftMotor,-frontRightMotor,-backRightMotor);
	gyro.reset();
	while(gyro.is_calibrating())
		pros::delay(50);
	pros::lcd::set_text(3, "Gyro initialized");

//	lcdModeSelect();
}

void disabled() {}


void competition_initialize() {}


void autonomous() {
	Auto a(myChassis, & gyro, & lift);
	// a.moveDistance(3_ft);
	// a.turnDegrees(90);
	// auton.driveStraight(.9);
	// pros::delay(250);
	while(gyro.is_calibrating())
		pros::delay(20);
	// lift.angleGrabber(0);
	// auton.turnDegrees(180);
	// pros::delay(1000);
	// auton.turnDegrees(-270);
	// pros::delay(1000);
	// auton.turnDegrees(90);

	auton.activate();
}


void opcontrol() {
	okapi::Controller master;
	okapi::Controller partner(okapi::ControllerId::partner);
	//declare chassis drive
	//okapi::ChassisControllerIntegrated opcontrolDrive = RobotDrive.makeDrive();

	bool r1OnLast = false, r2OnLast = false;

	int control = 4;
	if(!partner.isConnected())
		control = 3;


	while(true){


		pros::lcd::print(1, "%d %d %d", (int)gyro.get_pitch(), (int)gyro.get_yaw(), (int)gyro.get_rotation());
		pros::lcd::print(2, "%d", lift.degrees());

		bool r1On = master.getDigital(ControllerDigital::R1);
		bool r2On = master.getDigital(ControllerDigital::R2);

		// if(!r1OnLast && r1On)
		// {
		// 	if(control < 4) ++control;
		// 	r1OnLast = true;
		// }
		// else if(!r1On && r1OnLast)
		// {
		// 	r1OnLast = false;
		// }
		//
		// if(!r2OnLast && r2On)
		// {
		// 	if(control > 1) --control;
		// 	r2OnLast = true;
		// }
		// else if(!r2On && r2OnLast)
		// {
		// 	r2OnLast = false;
		// }

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

	myChassis->model().tank(leftY, rightY);

	//opcontrolDrive.arcade(leftY, leftX);
	if(master.getDigital(ControllerDigital::A))
		lift.grabCube();
	else if(master.getDigital(ControllerDigital::Y))
		lift.releaseCube();
	else
		lift.grab(0);


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

	static bool pUpOnLast = false, pDownOnLast = false;

	float leftX = master.getAnalog(okapi::ControllerAnalog::leftX);
	float leftY = master.getAnalog(okapi::ControllerAnalog::leftY);
	float rightX = master.getAnalog(okapi::ControllerAnalog::rightX);
	float rightY = master.getAnalog(okapi::ControllerAnalog::rightY);

	// myChassis->model().tank(leftY, rightY)
	myChassis->model().arcade(leftY, leftX);
	//opcontrolDrive.arcade(leftY, leftX);

	double pLeftY= partner.getAnalog(okapi::ControllerAnalog::leftY);
	lift.moveLift(pLeftY);

	if(master.getDigital(ControllerDigital::A))
		lift.grabCube();
	else if(master.getDigital(ControllerDigital::Y))
		lift.releaseCube();
	else
		lift.grab(0);

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

void control3(okapi::Controller & master, okapi::Controller & partner)
{

	static bool pUpOnLast = false, pDownOnLast = false;

	float leftX = master.getAnalog(okapi::ControllerAnalog::leftX);
	float leftY = master.getAnalog(okapi::ControllerAnalog::leftY);
	float rightX = master.getAnalog(okapi::ControllerAnalog::rightX);
	float rightY = master.getAnalog(okapi::ControllerAnalog::rightY);

	myChassis->model().arcade(leftY, leftX);

	lift.moveLift(rightY);

	if(master.getDigital(okapi::ControllerDigital::up))
	{
		lift.cubeGrabEasy();
		return;
	}

	if(master.getDigital(ControllerDigital::Y))
		lift.grabCube();
	else if(master.getDigital(ControllerDigital::X))
		lift.releaseCube();
	else
		lift.grab(0);

	int deg = 0;
	if(master.getDigital(okapi::ControllerDigital::A))
	{
		deg = 40;
	}
	else if(master.getDigital(okapi::ControllerDigital::B))
	{
		deg = 260;
	}
	lift.angleGrabber(deg);
}

void control4(okapi::Controller & master, okapi::Controller & partner)
{
 //master:
 //left stick: turning
 //right stick: forward/backward
 //r2: slow mode

 //parter:
 //left stick: precise control ~
 //right stick: control angle ~
 //letter buttons: exact ~
 //r1: grab ~
 //r2: release ~

 	static bool pUpOnLast = false, pDownOnLast = false, goingToCube = false;
	static double degrees = 0;

 	float leftX = master.getAnalog(okapi::ControllerAnalog::leftX);
 	float leftY = master.getAnalog(okapi::ControllerAnalog::leftY);
 	float rightX = master.getAnalog(okapi::ControllerAnalog::rightX);
 	float rightY = master.getAnalog(okapi::ControllerAnalog::rightY);

	if(master.getDigital(ControllerDigital::R2))
	{
		rightY *= .5;
		leftX *= .5;
	}

 	myChassis->model().arcade(rightY, rightX);

 	double pLeftY= partner.getAnalog(okapi::ControllerAnalog::leftY);
	if(std::abs(pLeftY) > .1)
	{
 		lift.moveLift(pLeftY);
		goingToCube = false;
		degrees = lift.degrees();
	}
	else if(partner.getDigital(ControllerDigital::B))
	{
		lift.moveToCube(1);
		goingToCube = true;
	}
	else if(partner.getDigital(ControllerDigital::A))
	{
		lift.moveToCube(2);
		goingToCube = true;
	}
	else if(partner.getDigital(ControllerDigital::Y))
	{
		lift.moveToCube(3);
		goingToCube = true;
	}
	else if(partner.getDigital(ControllerDigital::X))
	{
		lift.moveToCube(6);
		goingToCube = true;
	}
	else if (!goingToCube)
		lift.moveMotorToHeight((int)std::abs(degrees));

	bool pR1On = partner.getDigital(ControllerDigital::R1);
  bool mR2On = master.getDigital(ControllerDigital::R2);
 	if(pR1On)
 		lift.grabCube();
 	else if(mR2On)
 		lift.releaseCube();
 	else
 		lift.grab(0);

	double pRightY = partner.getAnalog(okapi::ControllerAnalog::rightY);
	if(pRightY > 0.07)
	{
 		// lift.angleGrabber(std::abs(partner.getAnalog(okapi::ControllerAnalog::rightY) * 260));
		// lift.skipBack();

		if(pRightY > .9) pRightY = 260;
		else pRightY *= 260;
		if(partner.getDigital(okapi::ControllerDigital::R2)) pRightY+=30;
		lift.angleGrabber(pRightY);
	}
	else if(pRightY < -0.07)
	{
		lift.skipForward();
		// lift.angleGrabber(10);
	}
	else
		lift.angleGrabber(0);
}

void left()
{
	Auton::selection = Auton::team::RED_TEAM;
	pros::lcd::set_text(4, "Current alliance: Red");

}

void right()
{
	Auton::selection = Auton::team::BLUE_TEAM;
	pros::lcd::set_text(4, "Current alliance: Blue");

}
