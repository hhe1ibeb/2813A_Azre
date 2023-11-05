#include "main.h"
#include "config.h"

pros::Motor left_front_motor(LEFT_FRONT_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor left_back_motor(LEFT_BACK_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor right_front_motor(RIGHT_FRONT_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor right_back_motor(RIGHT_BACK_MOTOR_PORT, pros::E_MOTOR_GEARSET_06, false);

pros::MotorGroup left_side_motors({left_front_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor});

okapi::Motor intake(INTAKE);
okapi::MotorGroup catapult({-CATAPULT_LEFT, CATAPULT_RIGHT});

pros::ADIDigitalOut wing(WINGS);
pros::Rotation cata_rotation(CATAPULT_ROTATION);
pros::Distance cata_detect(CATAPULT_DETECT);

lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    10, // track width
    3.25, // wheel diameter
    360, // wheel rpm
    2, // chase power. 2-4 if no traction wheels, 8+ otherwise
};
// inertial sensor
pros::Imu inertial_sensor(GYRO);
 
// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    60, // kP
    50, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    5, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);