#include "main.h"

#define _DIGITAL_SENSOR_PORT_ 'G'
#define lowerLeftMotor 17
#define upperLeftMotor 16
#define lowerRightMotor 13
#define upperRightMotor 14
#define backLeftMotor 1
#define frontLeftMotor 9
#define backRightMotor 2
#define frontRightMotor 10
#define angleMotor 18
#define frontGrabMotor 11
#define backGrabMotor 12

void initialize() {
	//pros::lcd::initialize();
	//pros::lcd::set_text(1, "Hello PROS User!");

	//pros::lcd::register_btn1_cb(on_center_button);
	RobotDrive.initDrive(frontLeftMotor,backLeftMotor,-frontRightMotor,-backRightMotor);

//	lcdModeSelect();
}


void disabled() {}


void competition_initialize() {}


void autonomous() {}


void opcontrol() {
	okapi::Controller master(okapi::ControllerId::master);
	okapi::Controller partner(okapi::ControllerId::partner);

	//declare chassis drive
	okapi::ChassisControllerIntegrated opcontrolDrive = RobotDrive.makeDrive();
	Lift15 * lift = new Lift15(lowerLeftMotor, lowerRightMotor, upperLeftMotor, upperRightMotor, angleMotor, backGrabMotor, frontGrabMotor);

	while(true){

		double leftX = master.getAnalog(okapi::ControllerAnalog::leftX);
		double leftY = master.getAnalog(okapi::ControllerAnalog::leftY);
		double rightX = master.getAnalog(okapi::ControllerAnalog::rightX);
		double rightY = master.getAnalog(okapi::ControllerAnalog::rightY);

		opcontrolDrive.arcade(leftX, leftY);
		lift->grab(rightY);

		double pLeftY= partner.getAnalog(okapi::ControllerAnalog::leftY);
		lift->moveLift(pLeftY);

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

		pros::delay(50);
	}
}
