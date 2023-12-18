#include "main.h"
#include "config.h"

#define WING_ON() { left_wing.set_value(1); right_wing.set_value(1); }
#define WING_OFF() { left_wing.set_value(0); right_wing.set_value(0); }

ASSET(defpath1_txt);
ASSET(defpath2_txt);

ASSET(elim_defpath2_txt);

ASSET(offpath1_txt);
ASSET(offpath2_txt);
ASSET(offpath3_txt);
ASSET(offpath4_txt);
ASSET(offpath5_txt);

ASSET(elim_offpath5_txt);
ASSET(elim_offpath6_txt);
ASSET(elim_offpath7_txt);

ASSET(skills1_txt);
ASSET(skills1_rev_txt);
ASSET(skills2_txt);
ASSET(skills3_txt);
ASSET(skills4_txt);
ASSET(skills5_txt);
ASSET(skills6_txt);

void defensive_qua(){
    blocker.set_value(1);
    chassis.follow(defpath1_txt, 15, 3000, false);
    chassis.waitUntilDone();

    chassis.turnTo(-57, 0, 1000, true);
    chassis.waitUntilDone();

    chassis.follow(defpath2_txt, 15, 6000, false);
    chassis.waitUntil(10);
    WING_ON();
    chassis.waitUntil(20);
    WING_OFF();
    chassis.waitUntilDone();
}

void defensive_elim(){
    chassis.follow(defpath1_txt, 15, 1000, false);
    chassis.waitUntilDone();

    chassis.turnTo(-57, 0, 1000, true);
    chassis.waitUntilDone();
    
    chassis.follow(elim_defpath2_txt, 15, 8000, false);
    chassis.waitUntil(40);
    WING_ON();
    chassis.waitUntilDone();
    WING_OFF();
}

void offensive_qua(){
    blocker.set_value(1);
    // chassis.follow(offpath1_txt, 15, 2000, false);
    chassis.moveTo(33, -27, 180, 2000, false, 10, 0.6, 150);
    chassis.waitUntilDone();
    // chassis.follow(offpath2_txt, 15, 2000, true);
    chassis.moveTo(5, -27, 270, 2000, true, 10, 0.6, 130);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    intake.move_velocity(0);
    chassis.turnTo(32, -10, 1000, true);
    chassis.waitUntilDone();
    intake.move_velocity(-200);
    pros::delay(300);
    // chassis.moveTo(0, -3, 270, 2500, true);
    // chassis.follow(offpath3_txt, 15, 2000, true);
    // intake.move_velocity(200);
    // chassis.waitUntilDone();
    // pros::delay(300);
    chassis.moveTo(50, -5, 270, 2000, false, 10, 0.6, 140);
    chassis.waitUntil(10);
    WING_ON();
    chassis.waitUntilDone();
    chassis.moveTo(40, -5, 270, 1000, true, 10, 0.6, 140, false);
    WING_OFF();
    // chassis.turnTo(50, -5, 1000, true);
    // // chassis.waitUntilDone();
    // chassis.moveTo(50, -5, 90, 1000, true);
    // // intake.move_velocity(-600);
    // // chassis.waitUntilDone();
    // intake.move_velocity(-200);
    // chassis.follow(offpath5_txt, 15, 3000, false);
    // chassis.moveTo(8, -36, 90, 3000, false, 2, 0.6, 140, true);
    // chassis.waitUntilDone();
    // WING_ON();
    // pros::delay(500);
    // chassis.turnTo(40, -60, 1000, true);
    // chassis.waitUntilDone();
    // chassis.moveTo(37, -60, 180, 2000, true, 10, 0.6, 140);
    // chassis.waitUntilDone();
    // chassis.follow(elim_offpath7_txt, 15, 3000, false);
    // chassis.waitUntil(20);
    // WING_ON();
    // chassis.waitUntilDone();
}

void offensive_elim(){
    blocker.set_value(1);
    chassis.follow(offpath1_txt, 15, 3000, false);
    chassis.waitUntilDone();
    chassis.follow(offpath2_txt, 15, 3000, true);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    intake.move_velocity(-100);
    pros::delay(500);
    chassis.moveTo(5, 0, 315, 1000, true);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveTo(50, -5, 270, 3000, false, 2, 0.6, 127);
    chassis.waitUntil(10);
    WING_ON();
    chassis.waitUntilDone();
    WING_OFF();
    chassis.moveTo(30, -5, 270, 1000, true);
    chassis.turnTo(50, -5, 1000, true);
    chassis.waitUntilDone();
    chassis.moveTo(50, -5, 90, 1000, true);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    intake.move_velocity(0);
    chassis.follow(elim_offpath5_txt, 15, 3000, true);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    chassis.follow(elim_offpath6_txt, 15, 3000, false);
    chassis.waitUntil(50);
    WING_ON();
    chassis.waitUntil(55);
    WING_OFF();
    chassis.waitUntilDone();
    chassis.follow(elim_offpath7_txt, 15, 1000, true);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    intake.move_velocity(0);
}

void progskills(){
    blocker.set_value(1);
    chassis.follow(skills1_txt, 15, 2000, false);
    chassis.waitUntil(10);
    blocker.set_value(0);
    chassis.waitUntilDone();
    chassis.follow(skills1_rev_txt, 15, 2000, true);
    chassis.waitUntil(5);
    flywheel.move_velocity(600);
    chassis.waitUntilDone();
    right_wing.set_value(1);
    chassis.turnTo(25, -15, 1000, true);
    chassis.waitUntilDone();
    chassis.moveTo(chassis.getPose().x-5, chassis.getPose().y-5, chassis.getPose().theta, 1000, false);
    chassis.waitUntilDone();
    pros::delay(7000);
    right_wing.set_value(0);
    flywheel.move_velocity(0);
    chassis.turnTo(-30, -65, 1000, false);
    chassis.waitUntilDone();
    chassis.follow(skills2_txt, 15, 9000, false);
    chassis.waitUntil(150);
    WING_ON();
    chassis.waitUntilDone();
    // chassis.follow(skills3_txt, 15, 3000, true);
    chassis.moveTo(11, -7, 270, 3000, true, 10, 0.6, 140);
    chassis.waitUntilDone();
    // chassis.follow(skills4_txt, 15, 5000, false);
    chassis.moveTo(40, -20, 270, 3000, false, 10, 0.6, 140);
    chassis.waitUntilDone();
    // chassis.follow(skills5_txt, 15, 3000, true);
    chassis.moveTo(45, -55, 180, 4000, true, 10, 0.6, 140);
    chassis.waitUntilDone();
    // chassis.follow(skills6_txt, 15, 4000, false);
    chassis.moveTo(80, -20, 180, 4000, false, 10, 0.6, 140);
    chassis.waitUntilDone();
    WING_OFF();
}

void autonomous() {
    if(selector::auton == 1) defensive_qua();
    if(selector::auton == -1) defensive_elim();
    if(selector::auton == 2) offensive_qua();
    if(selector::auton == -2) offensive_elim();
    if(selector::auton == 0) progskills();
}