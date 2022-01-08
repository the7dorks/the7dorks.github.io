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
    Motor mtr_dt_left_front(0);
    Motor mtr_dt_right_front(0);
    Motor mtr_dt_right_mid(0);
    Motor mtr_dt_right_back(0);
    Motor mtr_dt_left_back(0);
    Motor mtr_dt_left_mid(0);

    Motor mtr_lift(0);

    Motor mtr_intake(0);

    /* ------------------------ Pneumatics ----------------------- */
    pros::ADIDigitalOut sol_claw('0');
    pros::ADIDigitalOut sol_holder('0');

    /* ------------------------- Sensors ------------------------- */
    ADIEncoder track_encoder_forward('0', '0', false);
    ADIEncoder track_encoder_side('0', '0', false);
    pros::Imu imu1(0);
    pros::Imu imu2(0);

    RotationSensor rotation_lift(0, true);
    DistanceSensor distance_claw(0);

    /* ----------------------------------------------------------- */
    /*                           Controls                          */
    /* ----------------------------------------------------------- */
    Controller controller = Controller();

    ControllerButton btn_lift_toggle = ControllerDigital::up;
    ControllerButton btn_lift_up = ControllerDigital::L1;
    ControllerButton btn_lift_down = ControllerDigital::L2;
    ControllerButton btn_claw_toggle = ControllerDigital::X;

    ControllerButton btn_holder_toggle = ControllerDigital::B;

    ControllerButton btn_intake_toggle = ControllerDigital::left;
    ControllerButton btn_intake_in = ControllerDigital::R1;
    ControllerButton btn_intake_out = ControllerDigital::R2;

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

/*
Controls
  
  L2                R1
  L1                R2
  
    ^             X
  <   >         Y   A
    v             B
  
UP      lift toggle (ground level / platform level)
DOWN    
LEFT    intake toggle (in/off)
RIGHT   

A       
B       toggle holder
X       toggle claw
Y       

L1      lift up
L2      lift down
R1      intake in
R2      intake intake out


TODO
 - put holder somewhere
 - mutexes
 - brainstorm sensors
 - lift pid
 - investigate gps
*/