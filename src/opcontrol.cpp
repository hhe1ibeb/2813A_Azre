#include "main.h"
#include "config.h"

void cata_once(){
    catapult.move_velocity(200);
    pros::delay(500);
    while(cata_rotation.get_angle() > 21000){
        catapult.move_velocity(200);
    }
    catapult.move_velocity(0);
}

void celebrate(){
    right_side_motors.move_velocity(500);
    left_side_motors.move_velocity(-500);
    catapult.move_velocity(200);
}

void opcontrol(){
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    cata_rotation.reset();
    cata_rotation.reset_position();

    bool wings_out = 0;
    bool catapult_looping = 0;
    bool catapult_maxed = 0;
    bool catapult_detecting = 0;
    bool blocking = 0;
    bool celebrating = 0;
    catapult.set_brake_modes(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);

    wing.set_value(0);

	while (true) {
        float leftY = master.get_analog(ANALOG_LEFT_Y);
        float rightX = master.get_analog(ANALOG_RIGHT_X);
        
        // Move the left side of the robot
        left_side_motors.move(leftY + rightX);
        
        // Move the right side of the robot 
        right_side_motors.move(leftY - rightX);

		if (master.get_digital(DIGITAL_R1)) {
			intake.move_velocity(600);
		} else if (master.get_digital(DIGITAL_R2)) {
			intake.move_velocity(-600);
		} else {
			intake.move_velocity(0);
		}

        if(master.get_digital(DIGITAL_A)){
            cata_once();
        }

        if(master.get_digital_new_press(DIGITAL_Y)){
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
                catapult.move_velocity(-200);
            } else{
                catapult.move_velocity(0);
            }
        }

        if(master.get_digital_new_press(DIGITAL_X)){
            catapult_looping = !catapult_looping;
        }
        if(catapult_looping){
            catapult.move_velocity(200);
        } else{
            if(cata_rotation.get_angle() > 21000){
                catapult.move_velocity(200);
            } else{
                catapult.move_velocity(0);
            }
        }

        if(master.get_digital_new_press(DIGITAL_UP) && master.get_digital_new_press(DIGITAL_DOWN)){
            celebrating = !celebrating;
        }
        if(celebrating){
            celebrate();
        }

        if(master.get_digital_new_press(DIGITAL_L2)){
            wings_out = !wings_out;
        }

        if(master.get_digital_new_press(DIGITAL_L1)){
            blocking = !blocking;
        }

        std::string text = "Auto Detecting: " + std::string(catapult_detecting ? "On " : "Off");
        master.set_text(0, 0, text.c_str());
        wing.set_value(wings_out);
        blocker.set_value(blocking);
        pros::delay(10);
	}
}