#include "main.h"

ASSET(defpath1_txt);
ASSET(defpath2_txt);

ASSET(elim_defpath1_txt);
ASSET(elim_defpath2_txt);

ASSET(offpath1_txt);
ASSET(offpath2_txt);
ASSET(offpath3_txt);
ASSET(offpath4_txt);

ASSET(elim_offpath1_txt);
ASSET(elim_offpath2_txt);

ASSET(skills1_txt);

extern void cata_once();

void defensive_qua(){
    blocker.set_value(1);
    // chassis.moveTo(-56, -32, 180, 3000, false);
    chassis.follow(defpath1_txt, 15, 5000, false);
    chassis.waitUntilDone();

    chassis.follow(defpath2_txt, 15, 5000, true);
    chassis.waitUntil(15);
    wing.set_value(1);
    chassis.waitUntil(22);
    wing.set_value(0);
    chassis.waitUntilDone();
    blocker.set_value(0);
}

void defensive_elim(){
    blocker.set_value(1);
    wing.set_value(1);
    chassis.moveTo(-23, -14, 0, 3000, true, 0.6, 180.0);
    chassis.waitUntil(10);
    wing.set_value(0);
    chassis.waitUntil(15);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    wing.set_value(1);
    chassis.moveTo(-12, -12, 135, 2000, true);
    intake.move_velocity(0);
    chassis.moveTo(-18, -27, 180, 3000, true);
    chassis.follow(elim_defpath1_txt, 5000, 15, true);
    chassis.waitUntil(20);
    wing.set_value(0);
    chassis.waitUntilDone();
    chassis.moveTo(-10, -59, 90, 2000, true);
    intake.move_velocity(-200);
    pros::delay(1000);
    intake.move_velocity(0);
}

void offensive_qua(){
    blocker.set_value(1);
    chassis.follow(offpath1_txt, 15, 2000, true);
    wing.set_value(1);
    chassis.waitUntil(5);
    wing.set_value(0);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    intake.move_velocity(0);

    chassis.follow(offpath2_txt, 15, 3000, true);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    wing.set_value(1);
    chassis.follow(offpath3_txt, 15, 2000, true);
    intake.move_velocity(-200);
    chassis.waitUntilDone();

    chassis.follow(offpath4_txt, 15, 3000, true);
    chassis.waitUntilDone();
}

void offensive_elim(){
    blocker.set_value(1);
    intake.move_velocity(600);
    pros::delay(700);
    chassis.moveTo(50, -30, -135, 3000, false, 0, 0.6, 180, false);
    chassis.moveTo(47, -50, 45, 2000, true, 0, 0.6, 180.0, false);
    intake.move_velocity(0);
    wing.set_value(1);
    chassis.moveTo(55, -25, -30, 2000, true, 0, 0, 180.0);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    wing.set_value(0);
    intake.move_velocity(0);
    chassis.moveTo(40, -30, -90, 3000, true);
    chassis.moveTo(12, 0, -45, 3000, true);
    chassis.waitUntil(15);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    wing.set_value(1);
    chassis.moveTo(45, 0, 90, 3000, true);
    chassis.waitUntil(10);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    chassis.moveTo(0, -15, -135, 2000, true);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    chassis.moveTo(45, 0, 90, 2000, true);
    chassis.waitUntil(10);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
}

void progskills(){
    chassis.moveTo(-59, -32, 180, 3000, false);
    chassis.moveTo(-60, -42, 90, 2000, true);
    for(int i = 0; i < 44; i++){
        cata_once();
    }
    chassis.follow(skills1_txt, 15, 15000, true);
    chassis.waitUntil(100);
    wing.set_value(1);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
}

void autonomous() {
    if(selector::auton == 1) defensive_qua();
    if(selector::auton == -1) defensive_elim();
    if(selector::auton == 2) offensive_qua();
    if(selector::auton == -2) offensive_elim();
    if(selector::auton == 0) progskills();
}