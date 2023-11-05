#include "main.h"

extern int auton;

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
    chassis.waitUntilDist(1000);

    // chassis.follow(defpath2_txt, 5000, 15, true, true);
    chassis.moveTo(-35, -35, 45, 3000, true);
    chassis.waitUntilDist(10);
    intake.moveVelocity(-600);
    chassis.waitUntilDist(1000);
    chassis.moveTo(-23, -6, 0, 6000, true);
    intake.moveVelocity(0);
    chassis.waitUntilDist(10);
    intake.moveVelocity(600);
    chassis.waitUntilDist(1000);
    pros::delay(2000);
    chassis.moveTo(-5, -30, 90, 5000, true);
    intake.moveVelocity(0);
    chassis.waitUntilDist(20);

    // chassis.follow(defpath3_txt, 5000, 15, true, true);
    wing.set_value(1);
    intake.moveVelocity(-200);
}

void offensive(){
    chassis.follow(offpath1_txt, 5000, 15, true, false);
    chassis.waitUntilDist(20);
    wing.set_value(1);
    chassis.waitUntilDist(30);
    wing.set_value(0);
    chassis.waitUntilDist(1000);

    chassis.moveTo(12, -24, -90, 3000, true, true);
    chassis.waitUntilDist(15);
    intake.moveVelocity(300);
    chassis.waitUntilDist(1000);

    chassis.moveTo(13, -12, 45, 2000, false, true);
    wing.set_value(1);

    chassis.moveTo(41, -12, 90, 2000, true, true);
    chassis.waitUntilDist(10);
    intake.moveVelocity(-300);
    chassis.waitUntilDist(1000);

    wing.set_value(0);
    intake.moveVelocity(0);
    chassis.moveTo(9, -40, -90, 3000, false, true);
    wing.set_value(1);
}

void autonomous() {
    if(auton == 1) defensive();
    if(auton == 2) offensive();
}