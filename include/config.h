#pragma once
#include "main.h"

// chassis
extern pros::MotorGroup left_side_motors;
extern pros::MotorGroup right_side_motors;

extern lemlib::Drivetrain drivetrain;

// components
extern pros::Motor intake;
extern pros::Motor flywheel;

extern pros::ADIDigitalOut left_wing;
extern pros::ADIDigitalOut right_wing;
extern pros::ADIDigitalOut blocker;
extern pros::ADIDigitalOut side_hang;

// inertial sensor
extern pros::Imu inertial_sensor;

extern lemlib::Chassis chassis;