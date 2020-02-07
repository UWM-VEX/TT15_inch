#include "main.h"

#define _DIGITAL_SENSOR_PORT_ 'G'
#define lowerLeftMotor 6
#define upperLeftMotor 6
#define lowerRightMotor 6
#define upperRightMotor 6
#define backLeftMotor 6
#define frontLeftMotor 6
#define backRightMotor 6
#define frontRightMotor 6
#define angleMotor 6
#define frontGrabMotor 6
#define backGrabMotor 6

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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Controller partner(pros::E_CONTROLLER_PARTNER);

//	bool state = false;
//	pros::ADIDigitalOut pneumatic(_DIGITAL_SENSOR_PORT_, state);
//	pros::ADIDigitalOut pneumatic (_DIGITAL_SENSOR_PORT_);

	//declare chassis drive
	okapi::ChassisControllerIntegrated opcontrolDrive = RobotDrive.makeDrive();
	Lift15 * lift = new Lift15(lowerLeftMotor, lowerRightMotor, upperLeftMotor, upperRightMotor, angleMotor, backGrabMotor, frontGrabMotor);

	while(true){


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
	}
}
