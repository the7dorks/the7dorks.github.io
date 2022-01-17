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
  Motor mtr_dt_left_front(9);
  Motor mtr_dt_right_front(-13);
  Motor mtr_dt_right_mid(14);
  Motor mtr_dt_right_back(-12);
  Motor mtr_dt_left_back(8);
  Motor mtr_dt_left_mid(-10);

  Motor mtr_lift(17);

  Motor mtr_intake(16);

  /* ------------------------ Pneumatics ----------------------- */
  pros::ADIDigitalOut sol_claw('A');
  pros::ADIDigitalOut sol_holder({{4, 'H'}});

  /* ------------------------- Sensors ------------------------- */
  ADIEncoder track_encoder_forward({4, 'C', 'D'}, true);
  ADIEncoder track_encoder_side({4, 'A', 'B'}, true);
  pros::Imu imu1(6);
  pros::Imu imu2(7);

  RotationSensor rotation_lift(20, false);
  DistanceSensor distance_claw(18);

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