/**
 * definitions.cpp
 *
 * This file contains various declarations and definitions for
 * motors, sensors, controls, constants, and settings, so that
 * things that might need to be changed are all in one place.
 */
#include "main.h" // gives access to definition.hpp and other dependencies

namespace def
{
    /* ----------------------------------------------------------- */
    /*                           Devices                           */
    /* ----------------------------------------------------------- */

    /* -------------------------- Motors ------------------------- */
    Motor mtr_dt_left_front(1);
    Motor mtr_dt_right_front(2);
    Motor mtr_dt_right_back(3);
    Motor mtr_dt_left_back(4);

    /* ------------------------- Sensors ------------------------- */
    ADIEncoder track_encoder_forward('A', 'B', false);
    ADIEncoder track_encoder_side('C', 'D', true);
    pros::Imu imu_top(9);
    pros::Imu imu_bottom(10);

    /* ----------------------------------------------------------- */
    /*                           Controls                          */
    /* ----------------------------------------------------------- */
    Controller controller = Controller();

    /* -------------------------------------------- */
    //ControllerButton btn_bc_in = ControllerDigital::R1;

    /* -------------------------------------------- */
    /*                   Constants                  */
    /* -------------------------------------------- */
    const double DRIVE_STRAIGHT_SCALE = 1922;
    const double DRIVE_TURN_SCALE = 17;
    const QSpeed DRIVE_MAX_SPEED = 1.3_mps;      // a measured linear velocity
    const QAcceleration DRIVE_MAX_ACCEL = 0.7_G; // approxamate measured linear acceleration

    /* ----------------------------------------------------------- */
    /*                          Constructs                         */
    /* ----------------------------------------------------------- */
    CustomOdometry customOdom = CustomOdometry(); // object that calculates position

    DrivetrainStateMachine sm_dt = DrivetrainStateMachine(); // state machine to control the drivetrain
} // namespace def
