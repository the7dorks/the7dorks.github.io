/**
 * LiftStateMachine.hpp
 *
 * This file contains the declaration of the LiftStateMachine class.
 * LiftStateMachine is a state machine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the lift.
 *
 * To use the state machine in auton, make sure you disable/reenable
 * the normal state machine tasks and run the specified action.
 */
#pragma once           // makes sure the file is only included once
#include "main.h"      // gives access to dependancies from other files
class LiftStateMachine // state machine to represent the drivetrain
{
public:
    enum class MStates // enumeration to organize possible states
    {
        off,    // not doing anything
        hold,   // hold the lift where it is
        up,     // moves the lift up
        down,   // moves the lift down
        top,    // moves the arm to the top and holds
        bottom, // moves the lift to the bottom and holds
        rings   // moves the lift to be able to get rings
    };
    static MStates getState();
    static void setState(const MStates istate);
    static bool stateChanged();
    static double getAngle(); // returns the angle of the arm

    static void engageClaw();
    static void disengageClaw();
    static bool goalInRange(double idistanceMM = def::SET_LIFT_DISTANCE_MIN_MM);

    static void enableControl();
    static void disableControl();
    static void enablePID();
    static void disablePID();

    static int getGoalLocation(bool isafe = false); // 0: center, 1: left, 2: right

    static void controlState();                     // update the state based on controller input
    static void update();                           // move the robot based on the state
    static void setLiftAngle(const double itarget); // set the target PID angle for the lift
    static void run();                              // control the state and update the robot to be run in separate task

private:
    /* ------------------------- Devices ------------------------- */
    static Motor &mmtr;
    static SolenoidWrapper mclaw;
    static RotationSensor &mrotation;
    static DistanceSensor &mdistClaw;
    static DistanceSensor &mdistLeft;
    static DistanceSensor &mdistRight;

    /* -------------------------- State -------------------------- */
    static MStates mstate, mlastState;
    static bool moverrideDistance;
    static bool mengageClaw;
    static bool mcontrolEnabled;
    static bool mpidEnabled;
    static double mpidTarget;

    /* ------------------------- Controls ------------------------ */
    static ControllerButton &mbtnToggle;     // botton to toggle the lift being up/down
    static ControllerButton &mbtnUp;         // button to raise the lift
    static ControllerButton &mbtnDown;       // button to lower the lift
    static ControllerButton &mbtnClawToggle; // button to toggle the claw actuated/not

    /* -------------------------- Other -------------------------- */
    static PID mpid;                                 // pid controller for moving the lift
    static double holdForceFromAngle(double iangle); // returns how much the motor needs to power just to hold the lift in place
};