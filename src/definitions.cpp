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
    Motor mtr_dt_left_front(-7);
    Motor mtr_dt_right_front(4);
    Motor mtr_dt_right_back(3);
    Motor mtr_dt_left_back(-17);

    Motor mtr_lift_left(-10);
    Motor mtr_lift_right(6);

    Motor mtr_mg_left(18);
    Motor mtr_mg_right(-12);

    /* ------------------------ Pneumatics ----------------------- */
    pros::ADIDigitalOut sol_claw_front('H');

    /* ------------------------- Sensors ------------------------- */
    ADIEncoder track_encoder_forward('C', 'D', false);
    ADIEncoder track_encoder_side('E', 'F', false);
    pros::Imu imu1(5);
    pros::Imu imu2(13);
    RotationSensor rotation_lift(2, true);
    RotationSensor rotation_mg(15, true);
    pros::Distance distance_lift_claw(16);

    /* ----------------------------------------------------------- */
    /*                           Controls                          */
    /* ----------------------------------------------------------- */
    Controller controller = Controller();

    ControllerButton btn_lift_toggle = ControllerDigital::Y;
    ControllerButton btn_lift_up = ControllerDigital::R1;
    ControllerButton btn_lift_down = ControllerDigital::R2;
    ControllerButton btn_lift_pneumatic_toggle = ControllerDigital::A;

    // ControllerButton btn_mg_toggle = ControllerDigital::L1;
    ControllerButton btn_mg_up = ControllerDigital::L1;
    ControllerButton btn_mg_down = ControllerDigital::L2;
    ControllerButton btn_mg_relax = ControllerDigital::left;

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
    MogoStateMachine sm_mg = MogoStateMachine();             // state machine to control the mogo lift
} // namespace def
