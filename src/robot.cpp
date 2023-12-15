#include "main.h"

const int L1 = 14;
const int L2 = 15;
const int L3 = 16;
const int R1 = 17;
const int R2 = 18;
const int R3 = 19;

const int FLYWHEEL = 20;

const int INTAKE = 11;

const char LEFT_WING = 'D';
const char RIGHT_WING = 'C';
const char BLOCKER = 'A';
const char SIDE_HANG = 'B';

const int GYRO = 4;

pros::Motor left1_motor(L1, pros::E_MOTOR_GEARSET_06, true);
pros::Motor left2_motor(L2, pros::E_MOTOR_GEARSET_06, true);
pros::Motor left3_motor(L3, pros::E_MOTOR_GEARSET_06, true);
pros::Motor right1_motor(R1, pros::E_MOTOR_GEARSET_06, false);
pros::Motor right2_motor(R2, pros::E_MOTOR_GEARSET_06, false);
pros::Motor right3_motor(R3, pros::E_MOTOR_GEARSET_06, false);


pros::MotorGroup left_side_motors({left1_motor, left2_motor, left3_motor});
pros::MotorGroup right_side_motors({right1_motor, right2_motor, right3_motor});

pros::Motor intake(INTAKE);
pros::Motor flywheel(FLYWHEEL, pros::E_MOTOR_GEARSET_06, true);

pros::ADIDigitalOut left_wing(LEFT_WING);
pros::ADIDigitalOut right_wing(RIGHT_WING);
pros::ADIDigitalOut blocker(BLOCKER);
pros::ADIDigitalOut side_hang(SIDE_HANG);

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