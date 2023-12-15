#include "main.h"
#include "config.h"

#define WING_ON() { left_wing.set_value(1); right_wing.set_value(1); }
#define WING_OFF() { left_wing.set_value(0); right_wing.set_value(0); }

void celebrate(){
    right_side_motors.move_velocity(500);
    left_side_motors.move_velocity(-500);
}

void opcontrol(){
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    bool wings_out = 0;
    bool blocking = 0;
    bool celebrating = 0;
    bool matchloading = 0;
    side_hang.set_value(0);


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

        if(master.get_digital_new_press(DIGITAL_A)){
            matchloading = !matchloading;
        } 

        if(matchloading){
            flywheel.move_velocity(600);
        } else{
            flywheel.move_velocity(0);
        }

        if(master.get_digital_new_press(DIGITAL_UP) && master.get_digital_new_press(DIGITAL_DOWN)){
            celebrating = !celebrating;
        }
        if(celebrating){
            celebrate();
        }

        if(master.get_digital_new_press(DIGITAL_L2)){
            wings_out = !wings_out;
            if(!wings_out){
                WING_ON();
            } else{
                WING_OFF();
            }  
        }

        if(master.get_digital_new_press(DIGITAL_L1)){
            blocking = !blocking;
        }

        if(master.get_digital_new_press(DIGITAL_RIGHT)){
            side_hang.set_value(1);
        }
        if(master.get_digital_new_press(DIGITAL_LEFT)){
            side_hang.set_value(0);
        }

        blocker.set_value(blocking);
        pros::delay(10);
	}
}