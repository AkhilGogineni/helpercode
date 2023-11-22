#include "main.h"
// drive motors
pros::Motor lF(7, pros::E_MOTOR_GEARSET_06); // left front motor. port 9, reversed
pros::Motor lFPto(-8, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed
pros::Motor lBPto(-9, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed
pros::Motor lB(10, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed

pros::Motor rF(-2, pros::E_MOTOR_GEARSET_06); // right front motor. port 12
pros::Motor rFPto(5, pros::E_MOTOR_GEARSET_06); // right back motor. port 16
pros::Motor rBPto(4, pros::E_MOTOR_GEARSET_06); // right back motor. port 16
pros::Motor rB(-3, pros::E_MOTOR_GEARSET_06); // right back motor. port 16
 

// motor groups
pros::MotorGroup leftMotors({lF, lFPto, lBPto, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rFPto, rBPto, rB}); // right motor group

pros::MotorGroup frontPtoLeftMotors({lF, lFPto, lB}); // left motor group
pros::MotorGroup frontPtoRightMotors({rF, rFPto, rB}); // right motor group

pros::MotorGroup backPtoLeftMotors({lF, lBPto, lB}); // left motor group
pros::MotorGroup backPtoRightMotors({rF, rBPto, rB}); // right motor group

pros::MotorGroup bothPtoLeftMotors({lF, lB}); // left motor group
pros::MotorGroup bothPtoRightMotors({rF, rB}); // right motor group

// Inertial Sensor on port 11
pros::Imu imu(14);

pros::Rotation cataTurn(6);

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::ADIDigitalOut thing('A', false);
pros::ADIDigitalOut wing1('C', false);
pros::ADIDigitalOut wing2('G', false);
pros::ADIDigitalOut blocker1('D', true);
pros::ADIDigitalOut blocker2('B', true);
pros::ADIDigitalOut frontPto('F', false);
pros::ADIDigitalOut backPto('E', true); 
pros::ADIDigitalOut blocker2ndStage('H', true);
