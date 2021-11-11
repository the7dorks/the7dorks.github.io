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
    Motor mtr_dt_right_front(11);
    Motor mtr_dt_right_back(3);
    Motor mtr_dt_left_back(4);

    Motor mtr_lift_left(9);
    Motor mtr_lift_right(6);

    Motor mtr_mg_left(7);
    Motor mtr_mg_right(8);

    /* ------------------------ Pneumatics ----------------------- */
    pros::ADIDigitalOut sol_claw_front('H');

    /* ------------------------- Sensors ------------------------- */
    ADIEncoder track_encoder_forward('A', 'B', false);
    ADIEncoder track_encoder_side('C', 'D', true);
    pros::Imu imu_top(5);
    pros::Imu imu_bottom(10);
    RotationSensor rotation_lift(2, true);

    /* ----------------------------------------------------------- */
    /*                           Controls                          */
    /* ----------------------------------------------------------- */
    Controller controller = Controller();
    ControllerButton btn_lift_down = ControllerDigital::L2;
    ControllerButton btn_lift_up = ControllerDigital::L1;

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
    LiftStateMachine sm_lift = LiftStateMachine();           // state machine to control the lift
} // namespace def
