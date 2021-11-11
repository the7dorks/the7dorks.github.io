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
    extern Motor mtr_dt_right_back;
    extern Motor mtr_dt_left_back;
    /* ----------------------------------------------------------- */
    extern Motor mtr_lift_left;
    extern Motor mtr_lift_right;
    /* ----------------------------------------------------------- */
    extern Motor mtr_mg_left;
    extern Motor mtr_mg_right;

    /* ------------------------ Pneumatics ----------------------- */
    extern pros::ADIDigitalOut sol_claw_front;

    /* ------------------------- Sensors ------------------------- */
    extern ADIEncoder track_encoder_forward;
    extern ADIEncoder track_encoder_side;
    extern pros::Imu imu_top;
    extern pros::Imu imu_bottom;
    extern RotationSensor rotation_lift;

    /* ----------------------------------------------------------- */
    /*                           Controls                          */
    /* ----------------------------------------------------------- */
    extern Controller controller;
    extern ControllerButton btn_lift_down;
    extern ControllerButton btn_lift_up;

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
    const double SET_LIFT_TOP_DEG = 100;
    const double SET_LIFT_RANGE_DEG = 3;
} // namespace def
