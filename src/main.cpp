#include "main.h"

#define _DIGITAL_SENSOR_PORT_ 'G'
int lowerLeftMotor = 20;
int upperLeftMotor = 15;
int lowerRightMotor = 13;
int upperRightMotor = 14;
int backLeftMotor = 1;
int frontLeftMotor = 9;
int backRightMotor = 2;
int frontRightMotor = 10;
int angleMotor = 8;
int frontGrabMotor = 11;
int backGrabMotor = 12;
int visionSensor = 4;
int gyroPort = 3;

pros::Vision sensor(visionSensor);
using namespace okapi;

auto myChassis = okapi::ChassisControllerFactory::create(
	{backLeftMotor,frontLeftMotor}, {-backRightMotor,-frontRightMotor},
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
	gyro.reset();

//	lcdModeSelect();
}

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
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
	bool pUpOnLast = false, pDownOnLast = false;
	//declare chassis drive
	//okapi::ChassisControllerIntegrated opcontrolDrive = RobotDrive.makeDrive();

	while(true){

		float leftX = master.getAnalog(okapi::ControllerAnalog::leftX);
		float leftY = master.getAnalog(okapi::ControllerAnalog::leftY);
		float rightX = master.getAnalog(okapi::ControllerAnalog::rightX);
		float rightY = master.getAnalog(okapi::ControllerAnalog::rightY);

		myChassis.arcade(leftY, leftX);
		//opcontrolDrive.arcade(leftY, leftX);
		lift.grab(rightY);

		pros::lcd::print(0, "%.3f %.3f %.3f %.3f", gyro.get_rotation(),
		                 gyro.get_yaw(),
		                 gyro.get_roll(),
									 		gyro.get_pitch());

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

		// //pros::lcd::print(0, "%d " "%d " "%d", RobotLift.getLiftPos(), partner.get_analog(ANALOG_LEFT_Y), state);
		//
		// if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		// {
		// 	opcontrolDrive.tank((master.get_analog(ANALOG_LEFT_Y) * 0.33)/127.0, (master.get_analog(ANALOG_RIGHT_Y) * 0.33)/127.0);
		// }
		// else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		// {
		// 	opcontrolDrive.tank((master.get_analog(ANALOG_LEFT_Y) * 0.5)/127.0, (master.get_analog(ANALOG_RIGHT_Y) * 0.5)/127.0);
		// }
		// else
		// {
		// 	opcontrolDrive.tank((master.get_analog(ANALOG_LEFT_Y))/127.0, (master.get_analog(ANALOG_RIGHT_Y))/127.0);
		// }
		//
		// if(std::abs(partner.get_analog(ANALOG_LEFT_Y))>20)
		// {
		// 	RobotLift.moveLift(partner.get_analog(ANALOG_LEFT_Y)* 0.5);
		// }
		// else
		// {
		// 	RobotLift.moveLift(0);
		// }
		//
		// if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		// {
		// //	state = !state;
		// 	pneumatic.set_value(true);
		// //	pros::delay(5);
		// }
		// else{
		// 	pneumatic.set_value(false);
		// }

		pros::delay(20);
	}
}
