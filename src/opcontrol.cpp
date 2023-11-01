#include "main.h"
using namespace okapi::literals;

std::shared_ptr<okapi::ChassisController> drive = 
    okapi::ChassisControllerBuilder()
        .withMotors({LEFT_FRONT_MOTOR_PORT, LEFT_BACK_MOTOR_PORT},
                    {-RIGHT_FRONT_MOTOR_PORT, -RIGHT_BACK_MOTOR_PORT})
        .withDimensions(okapi::AbstractMotor::gearset::blue, {{3.25_in, 10_in}, okapi::imev5BlueTPR})
        .build();

void opcontrol(){
    okapi::Controller controller;

    okapi::ControllerButton intake_in(okapi::ControllerDigital::R1);
    okapi::ControllerButton intake_out(okapi::ControllerDigital::R2);
    okapi::ControllerButton catapult_control(okapi::ControllerDigital::A);
    okapi::ControllerButton catapult_loop(okapi::ControllerDigital::X);
    okapi::ControllerButton wing_in(okapi::ControllerDigital::L1);
    okapi::ControllerButton wing_out(okapi::ControllerDigital::L2);
    cata_rotation.reset();
    cata_rotation.reset_position();

    double catapult_position = 0;
    bool wings_out = 0;
    bool catapult_looping = 0;
    catapult.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    wing.set_value(0);

	while (true) {
		drive->getModel()->arcade(controller.getAnalog(okapi::ControllerAnalog::rightX),
                                  controller.getAnalog(okapi::ControllerAnalog::leftY));
        
		if (intake_in.isPressed()) {
			intake.moveVelocity(600);
		} else if (intake_out.isPressed()) {
			intake.moveVelocity(-600);
		} else {
			intake.moveVelocity(0);
		}

        // if (catapult_control.isPressed()) {
        //     catapult.moveVelocity(200);
        // } else {
        //     int32_t angle = cata_rotation.get_angle();
        //     if(angle > 26000){
        //         catapult.moveVelocity(200);
        //     } else{
        //         catapult.moveVelocity(0);
        //     }
        // }

        if(catapult_loop.changedToPressed()){
            catapult_looping = !catapult_looping;
        }
        if(catapult_looping){
            catapult.moveVelocity(200);
        } else{
            int32_t angle  = cata_rotation.get_angle();
            if(angle > 22000){
                catapult.moveVelocity(200);
            } else{
                catapult.moveVelocity(0);
            }
        }

        // if(catapult_control.isPressed()){
        //     catapult.moveVelocity(100);
        // } else{
        //     if(cata_rotation.get_position() < catapult_position){
        //         catapult.moveVelocity(100);
        //     } else{
        //         catapult.moveVelocity(0);
        //     }
        // }

		if(wing_out.isPressed()){
			wings_out = 1;
		}
        if(wing_in.isPressed()){
            wings_out = 0;
        }
        wing.set_value(wings_out);
        pros::delay(10);
	}
}