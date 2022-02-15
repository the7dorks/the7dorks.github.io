/**
 * definitions.hpp
 *
 * This file contains various declarations and definitions for
 * motors, sensors, controls, constants, and settings, so that
 * things that might need to be changed are all in one place.
 */
#pragma once      // makes sure the file is only included once
#include "main.h" // gives access to dependancies from other files

#define DT_STATES DrivetrainStateMachine::MStates
#define LIFT_STATES LiftStateMachine::MStates
#define INTAKE_STATES IntakeStateMachine::MStates
#define HOLDER_STATES HolderStateMachine::MStates

#define makeFunc(i) [&]() i
#define cutDrive(i)                                          \
    {                                                        \
        AsyncAction(i, makeFunc({ Drivetrain::disable(); })) \
    }
namespace def
{
    /* ----------------------------------------------------------- */
    /*                           Devices                           */
    /* ----------------------------------------------------------- */

    /* -------------------------- Motors ------------------------- */
    extern Motor mtr_dt_left_front;
    extern Motor mtr_dt_right_front;
    extern Motor mtr_dt_right_mid;
    extern Motor mtr_dt_right_back;
    extern Motor mtr_dt_left_back;
    extern Motor mtr_dt_left_mid;
    /* ----------------------------------------------------------- */
    extern Motor mtr_lift;
    /* ----------------------------------------------------------- */
    extern Motor mtr_intake;

    /* ------------------------ Pneumatics ----------------------- */
    extern pros::ADIDigitalOut sol_claw;
    extern pros::ADIDigitalOut sol_holder;

    /* ------------------------- Sensors ------------------------- */
    extern ADIEncoder track_encoder_forward;
    extern ADIEncoder track_encoder_side;
    extern ADIEncoder track_encoder_testing;
    extern pros::Imu imu1;
    extern pros::Imu imu2;

    extern RotationSensor rotation_lift;
    extern DistanceSensor distance_claw;
    extern DistanceSensor distance_eye_front_left;  // on the left side
    extern DistanceSensor distance_eye_front_right; // on the right side

    extern DistanceSensor distance_eye_back_left; // on the right side of the robot
    extern DistanceSensor distance_eye_back_center;
    extern DistanceSensor distance_eye_back_right; // on the left side of the robot

    /* ----------------------------------------------------------- */
    /*                           Controls                          */
    /* ----------------------------------------------------------- */
    extern Controller controller;

    extern ControllerButton btn_lift_toggle;
    extern ControllerButton btn_lift_up;
    extern ControllerButton btn_lift_down;
    extern ControllerButton btn_claw_toggle;

    extern ControllerButton btn_holder_toggle;

    extern ControllerButton btn_intake_toggle;
    extern ControllerButton btn_intake_in;
    extern ControllerButton btn_intake_out;

    /* ----------------------------------------------------------- */
    /*                          Constants                          */
    /* ----------------------------------------------------------- */

    /* --------------------- Tracking Wheels --------------------- */
    const QLength TRACK_WHEEL_DIAMETER = 2.838_in;
    const QLength TRACK_WHEEL_CIRCUMFERENCE = TRACK_WHEEL_DIAMETER * M_PI;
    const QLength TRACK_FORWARD_OFFSET = 2.2_in;
    const QLength TRACK_SIDE_OFFSET = 6.05_in;

    /* ------------------------ Drivetrain ----------------------- */
    const QLength DRIVE_WHEEL_DIAMETER = 3.25_in;
    const extern double DRIVE_STRAIGHT_SCALE; // converts motor degrees to meters
    const extern double DRIVE_TURN_SCALE;     // converts motor degrees to robot degrees
    const double DRIVE_WHEEL_DIAMETER_IN = DRIVE_WHEEL_DIAMETER.convert(inch);
    const QLength DRIVE_WHEEL_CIRCUMFERENCE = DRIVE_WHEEL_DIAMETER * M_PI;
    const double DRIVE_WHEEL_CIRCUMFERENCE_IN = DRIVE_WHEEL_CIRCUMFERENCE.convert(inch);
    const QLength DRIVE_OFFSET = 14_in;
    const double DRIVE_RATIO = 3.0 / 5.0;
    const double DRIVE_DEG_TO_IN = DRIVE_RATIO * DRIVE_WHEEL_CIRCUMFERENCE_IN / 360 * 3; // * 3 for 600rpm motors

    const extern QSpeed DRIVE_MAX_SPEED;        // a measured linear velocity
    const extern QAcceleration DRIVE_MAX_ACCEL; // approxamate measured linear acceleration

    /* ------------------------- Settings ------------------------ */
    const double SET_DT_MAX = 1;                          // default drivetrain max speed (1 is 100%)
    const OdomState SET_ODOM_START = {0_in, 0_in, 0_deg}; // starting position of the robot on the field

    const double SET_DT_POW_STRAIGHT = 2; // powers of the curves of the drivetrain control adjustments
    const double SET_DT_POW_STRAFE = 5;
    const double SET_DT_POW_TURN = 3;

    const double SET_LIFT_BOTTOM_DEG = 20.8;
    const double SET_LIFT_RINGS_DEG = 42;
    const double SET_LIFT_MIN_DEG = 32;
    const double SET_LIFT_TOP_DEG = 124;
    const double SET_LIFT_DISTANCE_MIN_MM = 35;

    const double SET_HOLDER_DISTANCE_MAX_MM = 32;
    const double SET_HOLDER_EYES_DISTANCE_DIFF_MAX = 200;
} // namespace def
