#pragma once
#include "main.h"

const int LEFT_FRONT_MOTOR_PORT =19;
const int LEFT_BACK_MOTOR_PORT = 20;
const int RIGHT_FRONT_MOTOR_PORT = 11;
const int RIGHT_BACK_MOTOR_PORT = 12;

const int INTAKE = 2;
const int CATAPULT_LEFT = 4;
const int CATAPULT_RIGHT = 10;

const char WINGS = 'F';

const int CATAPULT_ROTATION = 9;

const int GYRO = 7;

extern pros::Motor left_front_motor;
extern pros::Motor left_back_motor;
extern pros::Motor right_front_motor;
extern pros::Motor right_back_motor;

extern pros::MotorGroup left_side_motors;
extern pros::MotorGroup right_side_motors;

extern lemlib::Drivetrain_t drivetrain;

extern okapi::Motor intake;
extern okapi::MotorGroup catapult;

extern pros::ADIDigitalOut wing;

extern pros::Rotation cata_rotation;

// inertial sensor
extern pros::Imu inertial_sensor;
 
// odometry struct
extern lemlib::OdomSensors_t sensors;

// forward/backward PID
extern lemlib::ChassisController_t lateralController;
 
// turning PID
extern lemlib::ChassisController_t angularController;

extern lemlib::Chassis chassis;