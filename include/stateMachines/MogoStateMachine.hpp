/**
 * MogoStateMachine.hpp
 *
 * This file contains the declaration of the MogoStateMachine class.
 * MogoStateMachine is a state machine that inherits from VStateMachine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the mogo lift.
 *
 * To use the state machine in auton, make sure you disable/reenable
 * the normal state machine tasks and run the specified action.
 */
#pragma once                                  // makes sure the file is only included once
#include "main.h"                             // gives access to dependancies from other files
class MogoStateMachine : public VStateMachine // state machine to represent the drivetrain
{
public:
    MogoStateMachine(); // constructor to set defaults
    enum class MStates  // enumeration to organize possible states
    {
        off,    // not doing anything
        hold,   // hold the lift where it is
        up,     // moves the lift up
        down,   // moves the lift down
        top,    // moves the arm to the top and holds
        bottom, // moves the lift to the bottom and holds
    };
    MStates getState();
    void setState(const MStates istate);
    bool stateChanged();

    void engageClaw();
    void disengageClaw();

    void controlState() override; // update the state based on controller input
    void update() override;       // move the robot based on the state

private:
    /* -------------------------- State -------------------------- */
    MStates mstate, mlastState;

    /* ------------------------- Controls ------------------------ */
    ControllerButton &mbtnToggle; // botton to toggle the lift being up/down
    ControllerButton &mbtnUp;     // button to raise the lift
    ControllerButton &mbtnDown;   // button to lower the lift
    ControllerButton &mbtnRelax;  // button that rests the lift

    /* ------------------------- Devices ------------------------- */
    Motor &mmtr;
    RotationSensor &mrotation;
};

namespace def
{
    extern MogoStateMachine sm_mg; // declares the sm_dt object as extern, to make sure it only gets constructed once
} // namespace def
