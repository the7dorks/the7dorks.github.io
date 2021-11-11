/**
 * LiftStateMachine.hpp
 *
 * This file contains the declaration of the LiftStateMachine class.
 * LiftStateMachine is a state machine that inherits from VStateMachine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the drivetrain.
 *
 * To use the state machine in auton, make sure you disable/reenable
 * the normal state machine tasks and run the specified action.
 */
#pragma once                                  // makes sure the file is only included once
#include "main.h"                             // gives access to dependancies from other files
class LiftStateMachine : public VStateMachine // state machine to represent the drivetrain
{
public:
    LiftStateMachine(); // constructor to set defaults
    enum class MStates  // enumeration to organize possible states
    {
        off,    // not doing anything
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

    SolenoidWrapper mclaw;

    /* ------------------------- Controls ------------------------ */
    ControllerButton &mbtnDown; // reference to the button to raise the lift
    ControllerButton &mbtnUp;   // reference to the button to raise the lift

    /* ------------------------- Devices ------------------------- */
    Motor &mmtrLeft;
    RotationSensor &mrotation;
};

namespace def
{
    extern LiftStateMachine sm_lift; // declares the sm_dt object as extern, to make sure it only gets constructed once
} // namespace def
