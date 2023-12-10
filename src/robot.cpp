#include "main.h"

const int LEFT_FRONT_MOTOR_PORT = 8;
const int LEFT_BACK_MOTOR_PORT = 5;
const int RIGHT_FRONT_MOTOR_PORT = 2;
const int RIGHT_BACK_MOTOR_PORT = 3;

const int INTAKE = 9;
const int CATAPULT_LEFT = 7;
const int CATAPULT_RIGHT = 6;

const char WINGS = 'H';
const char BLOCKER = 'F';

const int CATAPULT_ROTATION = 10;
const int CATAPULT_DETECT = 4;

const int GYRO = 1;

pros::Motor left_front_motor(LEFT_FRONT_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor left_back_motor(LEFT_BACK_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor right_front_motor(RIGHT_FRONT_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor right_back_motor(RIGHT_BACK_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, false);

pros::MotorGroup left_side_motors({left_front_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor});

pros::Motor intake(INTAKE);
pros::Motor catapult_left(CATAPULT_LEFT);
pros::Motor catapult_right(-CATAPULT_RIGHT);
pros::MotorGroup catapult({catapult_left, catapult_right});

pros::ADIDigitalOut wing(WINGS);
pros::ADIDigitalOut blocker(BLOCKER);
pros::Rotation cata_rotation(CATAPULT_ROTATION);
pros::Distance cata_detect(CATAPULT_DETECT);

lemlib::Drivetrain drivetrain(&left_side_motors, // left motor group
                              &right_side_motors, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              360, // drivetrain rpm is 360
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);
// inertial sensor
pros::Imu inertial_sensor(GYRO);
 
// odometry struct
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1
                            nullptr, // vertical tracking wheel 2
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2
                            &inertial_sensor // inertial sensor
);

// lateral motion controller
lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            30, // derivative gain (kD)
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             10, // derivative gain (kD)
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             20 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);