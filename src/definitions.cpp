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
  Motor mtr_dt_left_front(10);
  Motor mtr_dt_right_front(-14);
  Motor mtr_dt_right_mid(13);
  Motor mtr_dt_right_back(-12);
  Motor mtr_dt_left_back(8);
  Motor mtr_dt_left_mid(-9);

  Motor mtr_lift(19);

  Motor mtr_intake(18);

  /* ------------------------ Pneumatics ----------------------- */
  pros::ADIDigitalOut sol_claw('A');
  pros::ADIDigitalOut sol_holder({{3, 'H'}});

  /* ------------------------- Sensors ------------------------- */
  ADIEncoder track_encoder_forward({3, 'C', 'D'}, true);
  ADIEncoder track_encoder_side({3, 'A', 'B'}, true);
  pros::Imu imu1(17);
  pros::Imu imu2(7);

  RotationSensor rotation_lift(20, false);
  DistanceSensor distance_claw(6);
  DistanceSensor distance_eye_front_left(2);
  DistanceSensor distance_eye_front_right(1);

  DistanceSensor distance_eye_back_left(11);
  DistanceSensor distance_eye_back_center(21);
  DistanceSensor distance_eye_back_right(4); // on the left side

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