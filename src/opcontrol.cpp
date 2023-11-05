#include "main.h"
using namespace okapi::literals;

std::shared_ptr<okapi::ChassisController> drive = 
    okapi::ChassisControllerBuilder()
        .withMotors({LEFT_FRONT_MOTOR_PORT, LEFT_BACK_MOTOR_PORT},
                    {-RIGHT_FRONT_MOTOR_PORT, -RIGHT_BACK_MOTOR_PORT})
        .withDimensions(okapi::AbstractMotor::gearset::blue, {{3.25_in, 10_in}, okapi::imev5BlueTPR})
        .build();

void cata_once(){
    catapult.moveVelocity(200);
    pros::delay(500);
    while(cata_rotation.get_angle() > 21000){
        catapult.moveVelocity(200);
    }
    catapult.moveVelocity(0);
}

void opcontrol(){
    okapi::Controller controller;

    pros::Controller master(CONTROLLER_MASTER);

    okapi::ControllerButton intake_in(okapi::ControllerDigital::R1);
    okapi::ControllerButton intake_out(okapi::ControllerDigital::R2);
    okapi::ControllerButton catapult_control(okapi::ControllerDigital::A);
    okapi::ControllerButton catapult_loop(okapi::ControllerDigital::X);
    okapi::ControllerButton catapult_max(okapi::ControllerDigital::B);
    okapi::ControllerButton catapult_detect(okapi::ControllerDigital::Y);
    okapi::ControllerButton wing_in(okapi::ControllerDigital::L1);
    okapi::ControllerButton wing_out(okapi::ControllerDigital::L2);
    okapi::ControllerButton tune_pid(okapi::ControllerDigital::up);
    okapi::ControllerButton tune_pid_ang(okapi::ControllerDigital::right);
    cata_rotation.reset();
    cata_rotation.reset_position();

    double catapult_position = 0;
    bool wings_out = 0;
    bool catapult_looping = 0;
    bool catapult_maxed = 0;
    bool catapult_detecting = 0;
    catapult.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    wing.set_value(0);

	while (true) {
        float leftY = master.get_analog(ANALOG_LEFT_Y);
        float rightX = master.get_analog(ANALOG_RIGHT_X);
        
        // Move the left side of the robot
        left_side_motors.move(leftY + rightX);
        
        // Move the right side of the robot 
        right_side_motors.move(leftY - rightX);

		// drive->getModel()->arcade(controller.getAnalog(okapi::ControllerAnalog::rightX),
        //                           controller.getAnalog(okapi::ControllerAnalog::leftY));
        
		if (intake_in.isPressed()) {
			intake.moveVelocity(600);
		} else if (intake_out.isPressed()) {
			intake.moveVelocity(-600);
		} else {
			intake.moveVelocity(0);
		}

        if(catapult_control.isPressed()){
            cata_once();
        }

        if(catapult_detect.changedToPressed()){
            catapult_detecting = !catapult_detecting;
        }

        if(catapult_detecting){
            if(cata_detect.get() < 10){
                cata_once();
            }
        }

        if(catapult_max.changedToPressed()){
            catapult_maxed = !catapult_maxed;
        }
        if(!catapult_looping && catapult_maxed){
            if(cata_rotation.get_angle() < 27000){
                catapult.moveVelocity(-200);
            } else{
                catapult.moveVelocity(0);
            }
        }

        if(catapult_loop.changedToPressed()){
            catapult_looping = !catapult_looping;
        }
        if(catapult_looping){
            catapult.moveVelocity(200);
        } else{
            if(cata_rotation.get_angle() > 21000){
                catapult.moveVelocity(200);
            } else{
                catapult.moveVelocity(0);
            }
        }

		if(wing_out.isPressed()){
			wings_out = 1;
		}
        if(wing_in.isPressed()){
            wings_out = 0;
        }

        if(tune_pid.changedToPressed()){
            chassis.moveTo(chassis.getPose().x+10, chassis.getPose().y, chassis.getPose().theta, 5000);
        }
        if(tune_pid_ang.changedToPressed()){
            chassis.moveTo(chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta+60, 5000);
        }

        std::string text = "Auto Detecting: " + std::string(catapult_detecting ? "On " : "Off");
        controller.setText(0, 0, text.c_str());
        pros::delay(10);
	}
}