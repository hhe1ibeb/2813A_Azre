#include "main.h"

ASSET(defpath1_txt);
ASSET(defpath2_txt);

ASSET(elim_defpath1_txt);
ASSET(elim_defpath2_txt);

ASSET(offpath1_txt);

ASSET(elim_offpath1_txt);

ASSET(skills_txt);

extern void cata_once();

void defensive_qua(){
    blocker.set_value(1);
    chassis.follow(defpath1_txt, 5000, 15, true, false);
    chassis.waitUntilDist(10);
    wing.set_value(1);
    chassis.waitUntilDist(20);
    wing.set_value(0);
    chassis.waitUntilDist(1000);

    chassis.follow(defpath2_txt, 3000, 15, false, true);

    chassis.moveTo(-14, -59, 90, 5000, false, true);
    blocker.set_value(0);
}

void defensive_elim(){
    chassis.follow(elim_defpath1_txt, 3000, 15, false, false);

    chassis.follow(elim_defpath2_txt, 10000, 15, true, true);
    chassis.waitUntilDist(25);
    wing.set_value(1);
    chassis.waitUntilDist(10000);
}

void offensive_qua(){
    blocker.set_value(1);
    chassis.follow(offpath1_txt, 2000, 15, true, true);
    wing.set_value(1);
    chassis.waitUntilDist(5);
    wing.set_value(0);
    intake.move_velocity(-200);
    chassis.waitUntilDist(1000);

    chassis.moveTo(47, -46, -90, 2000, false, false);

    chassis.moveTo(12, -24, -90, 3000, true, true);
    chassis.waitUntilDist(15);
    intake.move_velocity(300);
    chassis.waitUntilDist(1000);

    chassis.moveTo(13, -12, 45, 2000, true, true);
    wing.set_value(1);
    chassis.waitUntilDist(1000);

    chassis.moveTo(48, -10, 90, 2000, true, true);
    chassis.waitUntilDist(10);
    intake.move_velocity(-300);
    chassis.waitUntilDist(1000);

    wing.set_value(0);
    intake.move_velocity(0);
    chassis.moveTo(9, -34, -90, 3000, false, true);
    wing.set_value(1);
}

void offensive_elim(){
    
}

void progskills(){
    for(int i = 0; i < 44; i++){
        cata_once();
    }

}

void autonomous() {
    if(selector::auton == 1 || selector::auton == -1) defensive_qua();
    if(selector::auton == 2 || selector::auton == -2) offensive_qua();
    // offensive();
}