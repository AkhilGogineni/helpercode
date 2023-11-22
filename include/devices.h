#include "main.h"

extern pros::Motor lF;
extern pros::Motor lFPto;
extern pros::Motor lBPto;
extern pros::Motor lB;
extern pros::Motor rF;
extern pros::Motor rFPto;
extern pros::Motor rBPto;
extern pros::Motor rB;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

extern pros::MotorGroup frontPtoLeftMotors;
extern pros::MotorGroup frontPtoRightMotors;

extern pros::MotorGroup backPtoLeftMotors;
extern pros::MotorGroup backPtoRightMotors;

extern pros::MotorGroup bothPtoLeftMotors;
extern pros::MotorGroup bothPtoRightMotors;

extern pros::Imu imu;
extern pros::Controller controller;
extern pros::Rotation cataTurn;

extern pros::ADIDigitalOut thing;
extern pros::ADIDigitalOut wing1;
extern pros::ADIDigitalOut wing2;
extern pros::ADIDigitalOut blocker1;
extern pros::ADIDigitalOut blocker2;
extern pros::ADIDigitalOut blocker2ndStage;
extern pros::ADIDigitalOut frontPto;
extern pros::ADIDigitalOut backPto;