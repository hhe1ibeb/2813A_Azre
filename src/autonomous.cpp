#include "main.h"

ASSET(defpath1_txt);
ASSET(defpath2_txt);
ASSET(defpath3_txt);
ASSET(defpath4_txt);

ASSET(offpath1_txt);
ASSET(offpath2_txt);
ASSET(offpath3_txt);
ASSET(offpath4_txt);

void defensive(){    
    chassis.follow(defpath1_txt, 2000, 15, true, false);
    chassis.waitUntilDist(10);
    wing.set_value(1);
    chassis.waitUntilDist(10);
    wing.set_value(0);

    chassis.follow(defpath2_txt, 6000, 15, true, true);
    intake.moveVelocity(-600);
    chassis.waitUntilDist(10);
    while(cata_rotation.get_angle() > 22000){
        catapult.moveVelocity(200);
    }
    intake.moveVelocity(0);
    chassis.waitUntilDist(30);
    intake.moveVelocity(600);
    chassis.waitUntilDist(30);
    intake.moveVelocity(0);

    chassis.follow(defpath3_txt, 3000, 15, false, false);

    chassis.turnTo(-31, -59, 1000);
    chassis.follow(defpath4_txt, 3000, 15, true, true);
    chassis.waitUntilDist(10);
    while(cata_rotation.get_angle() < 32000){
        catapult.moveVelocity(-200);
    }
}

void offensive(){
    chassis.follow(offpath1_txt, 4000, 15, true, false);
    chassis.waitUntilDist(40);
    intake.moveVelocity(-300);
    wing.set_value(1);
    chassis.waitUntilDist(20);
    intake.moveVelocity(0);
    wing.set_value(0);

    chassis.follow(offpath2_txt, 2000, 15, true, true);
    intake.moveVelocity(600);

    chassis.follow(offpath3_txt, 4000, 15, true, true);
    chassis.waitUntilDist(30);
    wing.set_value(1);

    chassis.follow(offpath4_txt, 3000, 15, true, true);
    wing.set_value(0);
    chassis.waitUntilDist(40);
    wing.set_value(1);
}

void autonomous() {
    defensive();
}