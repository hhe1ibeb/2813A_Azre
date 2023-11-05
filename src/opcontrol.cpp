#include "main.h"
using namespace okapi::literals;

void cata_once(){
    catapult.moveVelocity(200);
    pros::delay(500);
    while(cata_rotation.get_angle() > 21000){
        catapult.moveVelocity(200);
    }
    catapult.moveVelocity(0);
}

void opcontrol(){
    pros::Controller master(CONTROLLER_MASTER);
    cata_rotation.reset();
    cata_rotation.reset_position();

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

		if (master.get_digital(DIGITAL_R1)) {
			intake.moveVelocity(600);
		} else if (master.get_digital(DIGITAL_R2)) {
			intake.moveVelocity(-600);
		} else {
			intake.moveVelocity(0);
		}

        if(master.get_digital(DIGITAL_A)){
            cata_once();
        }

        if(master.get_digital(DIGITAL_Y)){
            catapult_detecting = !catapult_detecting;
        }

        if(catapult_detecting){
            if(cata_detect.get() < 10){
                cata_once();
            }
        }

        if(master.get_digital(DIGITAL_B)){
            catapult_maxed = !catapult_maxed;
        }
        if(!catapult_looping && catapult_maxed){
            if(cata_rotation.get_angle() < 27000){
                catapult.moveVelocity(-200);
            } else{
                catapult.moveVelocity(0);
            }
        }

        if(master.get_digital_new_press(DIGITAL_X)){
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

		if(master.get_digital(DIGITAL_L1)){
			wings_out = 1;
		}
        if(master.get_digital(DIGITAL_L2)){
            wings_out = 0;
        }

        std::string text = "Auto Detecting: " + std::string(catapult_detecting ? "On " : "Off");
        master.set_text(0, 0, text.c_str());
        pros::delay(10);
	}
}