/**
 * LiftStateMachine.cpp
 *
 * This file contains the definitions of the LiftStateMachine class.
 * LiftStateMachine is a state machine that inherits from VStateMachine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the drivetrain.
 *
 * To use the state machine in auton, be sure to disable/reenable
 * the normal state machine tasks and run the specified action.
 */
#include "main.h" // gives access to LiftStateMachine and other dependencies

/* ----------------------------------------------------------- */
/*                     Private Information                     */
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/*                      Public Information                     */
/* ----------------------------------------------------------- */
LiftStateMachine::LiftStateMachine()
    : mstate(LIFT_STATES::off), mlastState(LIFT_STATES::off), mclaw(def::sol_claw_front), mbtnDown(def::btn_lift_down), mbtnUp(def::btn_lift_up), mmtrLeft(def::mtr_lift_left), mrotation(def::rotation_lift)
{
} // constructor to set defaults

LIFT_STATES LiftStateMachine::getState() { return mstate; }
void LiftStateMachine::setState(const LIFT_STATES istate)
{
    mstate = istate;
}
bool LiftStateMachine::stateChanged()
{
    if (mstate == mlastState)
    {
        return false;
    }
    else
    {
        mlastState = mstate;
        return true;
    }
}

void LiftStateMachine::engageClaw()
{
    mclaw.toggle(true);
}

void LiftStateMachine::disengageClaw()
{
    mclaw.toggle(false);
}

void LiftStateMachine::controlState() // update the state based on controller input
{
    if (mbtnUp.changedToPressed())
    {
        if (mrotation.get() > def::SET_LIFT_TOP_DEG - def::SET_LIFT_RANGE_DEG && mrotation.get() < def::SET_LIFT_TOP_DEG + def::SET_LIFT_RANGE_DEG) // if the lift is in the target range for the top
        {
            setState(LIFT_STATES::top); // hold
        }
        else
        {
            setState(LIFT_STATES::up); // go up
        }
    }
    else if (mbtnDown.changedToPressed())
    {
        if (mrotation.get() > -def::SET_LIFT_RANGE_DEG && mrotation.get() < def::SET_LIFT_RANGE_DEG) // if the lift is in the target range for the top
        {
            setState(LIFT_STATES::bottom); // hold
        }
        else
        {
            setState(LIFT_STATES::down); // go down
        }
    }

    if (getState() == LIFT_STATES::up && mrotation.get() > def::SET_LIFT_TOP_DEG - def::SET_LIFT_RANGE_DEG)
    {
        setState(LIFT_STATES::top);
    }
    else if (getState() == LIFT_STATES::down && mrotation.get() < def::SET_LIFT_RANGE_DEG)
    {
        setState(LIFT_STATES::bottom);
    }
}

void LiftStateMachine::update() // move the robot based on the state
{
    if (stateChanged())
    {
        switch (mstate)
        {
        case LIFT_STATES::off:
            mmtrLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
            mmtrLeft.moveVoltage(0);
            break;
        case LIFT_STATES::up:
            mmtrLeft.moveVoltage(12000);
            break;
        case LIFT_STATES::down:
            mmtrLeft.moveVoltage(-12000);
            break;
        case LIFT_STATES::top:
            mmtrLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
            break;
        case LIFT_STATES::bottom:
            mmtrLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
            break;
        }
    }
}
