#include "main.h"
#include "config.h"

ASSET(defpath1_txt);
ASSET(defpath2_txt);

ASSET(elim_defpath1_txt);
ASSET(elim_defpath2_txt);

ASSET(offpath1_txt);
ASSET(offpath2_txt);
ASSET(offpath3_txt);
ASSET(offpath4_txt);
ASSET(offpath5_txt);

ASSET(elim_offpath5_txt);
ASSET(elim_offpath1_txt);
ASSET(elim_offpath2_txt);

ASSET(skill1_txt);
ASSET(skill2_txt);

extern void cata_once();

void defensive_qua(){
    blocker.set_value(1);
    chassis.follow(defpath1_txt, 15, 3000, false);
    chassis.waitUntilDone();

    chassis.follow(defpath2_txt, 15, 6000, true);
    chassis.waitUntil(15);
    wing.set_value(1);
    chassis.waitUntil(25);
    wing.set_value(0);
    chassis.waitUntilDone();
    blocker.set_value(0);
}

void defensive_elim(){
    blocker.set_value(1);
    chassis.follow(elim_defpath1_txt, 15, 3000, false);
    chassis.waitUntilDone();
    
    chassis.follow(elim_defpath2_txt, 15, 8000, true);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    intake.move_velocity(0);
}

void offensive_qua(){
    blocker.set_value(1);
    chassis.follow(offpath1_txt, 15, 3000, true);
    chassis.waitUntil(20);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    chassis.follow(offpath2_txt, 15, 4000, true);
    intake.move_velocity(200);
    chassis.waitUntil(20);
    intake.move_velocity(-200);
    wing.set_value(1);
    chassis.waitUntilDone();
    wing.set_value(0);
    chassis.follow(offpath3_txt, 15, 4000, true);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    chassis.follow(offpath4_txt, 15, 3000, true);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    intake.move_velocity(0);
    chassis.follow(offpath5_txt, 15, 3000, true);
    chassis.waitUntilDone();
    wing.set_value(1);
}

void offensive_elim(){
    blocker.set_value(1);
    chassis.follow(offpath1_txt, 15, 3000, true);
    chassis.waitUntil(20);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    chassis.follow(offpath2_txt, 15, 4000, true);
    intake.move_velocity(200);
    chassis.waitUntil(20);
    intake.move_velocity(-200);
    wing.set_value(1);
    chassis.waitUntilDone();
    wing.set_value(0);
    chassis.follow(offpath3_txt, 15, 4000, true);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    chassis.follow(offpath4_txt, 15, 3000, true);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
    chassis.follow(elim_offpath5_txt, 15, 3000, true);
    intake.move_velocity(200);
    chassis.waitUntilDone();
    chassis.follow(elim_offpath1_txt, 15, 2000, false);
    chassis.waitUntilDone();
    chassis.follow(elim_offpath2_txt, 15, 3000, true);
    chassis.waitUntil(5);
    wing.set_value(1);
    intake.move_velocity(-200);
    chassis.waitUntilDone();
}

void progskills(){
    blocker.set_value(1);
    chassis.follow(skill1_txt, 15, 3000, true, false);
    blocker.set_value(0);
    for(int i = 0; i < 44; i++){
        cata_once();
    }
    chassis.follow(skill2_txt, 15, 20000, true);
    intake.move_velocity(-200);
    chassis.waitUntil(50);
    wing.set_value(1);
    chassis.waitUntil(40);
    wing.set_value(0);
    chassis.waitUntilDone();
}

void autonomous() {
    if(selector::auton == 1) defensive_qua();
    if(selector::auton == -1) defensive_elim();
    if(selector::auton == 2) offensive_qua();
    if(selector::auton == -2) offensive_elim();
    if(selector::auton == 0) progskills();
}