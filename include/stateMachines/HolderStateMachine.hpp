/**
 * HolderStateMachine.hpp
 *
 * This file contains the declaration of the HolderStateMachine class.
 * HolderStateMachine is a state machine.
 * It has an enumeration of different possible states to make it easy
 * for the user to control the holder.
 *
 * To use the state machine in auton, make sure you disable/reenable
 * the normal state machine tasks and runt the specified action.
 */
#pragma once             // makes sure the file is only included once
#include "main.h"        // gives access to dependancies from other files
class HolderStateMachine // state machine to represent the holder
{
public:
    enum class MStates // enumeration to organize possible states
    {
        open,   // not holding a goal
        closed, // not holding a goal
        smart   // decide what to do based on sensors
    };
    static MStates getState();
    static void setState(const MStates istate);

    static void enableControl();
    static void disableControl();

    static int getGoalLocation(); // 0: center, 1: left, 2: right

    static void controlState(); // update the state based on controller input
    static void update();       // move the robot based on the state
    static void run();          // control the state and update the robot to run in separate task

private:
    /* ------------------------- Devices ------------------------- */
    static SolenoidWrapper msol;
    static DistanceSensor &mdistLeft;
    static DistanceSensor &mdistCenter;
    static DistanceSensor &mdistRight;

    /* -------------------------- State -------------------------- */
    static MStates mstate;
    static bool mcontrolEnabled;

    /* ------------------------- Controls ------------------------ */
    static ControllerButton &mbtnToggle; // button to toggle whether the cylinder is clamping
};