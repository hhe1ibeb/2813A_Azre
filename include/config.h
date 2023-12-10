#pragma once
#include "main.h"

// chassis motors
extern pros::Motor left_front_motor;
extern pros::Motor left_back_motor;
extern pros::Motor right_front_motor;
extern pros::Motor right_back_motor;

extern pros::MotorGroup left_side_motors;
extern pros::MotorGroup right_side_motors;

extern lemlib::Drivetrain drivetrain;

// components
extern pros::Motor intake;
extern pros::MotorGroup catapult;

extern pros::ADIDigitalOut wing;
extern pros::ADIDigitalOut blocker;

// catapult sensors
extern pros::Rotation cata_rotation;
extern pros::Distance cata_detect;

// inertial sensor
extern pros::Imu inertial_sensor;

extern lemlib::Chassis chassis;