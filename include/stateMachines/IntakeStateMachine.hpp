/**
 * IntakeStateMachine.hpp
 *
 * This file contains the declaration of the LiftStateMachine class.
 * IntakeStateMachine is a state machine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the lift.
 *
 * To use the state machine in auton, make sure you disable/reenable
 * the normal state machine tasks and run the specified action.
 */
#pragma once             // makes sure the file is only included once
#include "main.h"        // gives access to dependancies from other files
class IntakeStateMachine // state machine to represent the drivetrain
{
public:
    enum class MStates // enumeration to organize possible states
    {
        off,      // not doing anything
        in,       // intake rings
        out,      // outtake rings
        override, // should be intaking, but the lift is too low
        smart     // decide what to do based on sensors
    };
    static MStates getState();
    static void setState(const MStates istate);

    static void enableControl();
    static void disableControl();

    static void controlState(); // update the state based on controller input
    static void update();       // move the robot based on the state
    static void run();          // control the state and update the robot to be run in separate task

private:
    /* ------------------------- Devices ------------------------- */
    static Motor &mmtr;
    /* -------------------------- State -------------------------- */
    static MStates mstate;
    static bool mtoggling;
    static bool mcontrolEnabled;
    static MStates moverrideState;

    /* ------------------------- Controls ------------------------ */
    static ControllerButton &mbtnToggle; // botton to toggle in/out
    static ControllerButton &mbtnIn;     // button to turn the intakes on
    static ControllerButton &mbtnOut;    // button to turn the intakes out
};