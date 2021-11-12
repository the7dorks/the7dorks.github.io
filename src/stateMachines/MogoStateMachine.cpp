/**
 * MogoStateMachine.cpp
 *
 * This file contains the definitions of the MogoStateMachine class.
 * MogoStateMachine is a state machine that inherits from VStateMachine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the mogo lift.
 */
#include "main.h" // gives access to MogoStateMachine and other dependencies

/* ----------------------------------------------------------- */
/*                      Public Information                     */
/* ----------------------------------------------------------- */
MogoStateMachine::MogoStateMachine()
    : mstate(MG_STATES::off), mlastState(MG_STATES::off), mbtnToggle(def::btn_mg_toggle), mbtnUp(def::btn_mg_up), mbtnDown(def::btn_mg_down), mbtnRelax(def::btn_mg_relax), mmtr(def::mtr_mg_left), mrotation(def::rotation_mg)
{
} // constructor to set defaults

MG_STATES MogoStateMachine::getState() { return mstate; }
void MogoStateMachine::setState(const MG_STATES istate)
{
    mstate = istate;
}
bool MogoStateMachine::stateChanged()
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

void MogoStateMachine::controlState() // update the state based on controller input
{
    if (mbtnToggle.changedToPressed())
    {
        if (mstate == MG_STATES::top || mrotation.get() > def::SET_MG_TOP_DEG / 2) // if the lift is at the top, or closer to the top
        {
            setState(MG_STATES::bottom);
        }
        else // if the lift is closer to the bottom
        {
            setState(MG_STATES::top);
        }
    }
    else if (mbtnUp.isPressed())
    {
        setState(MG_STATES::up);
    }
    else if (mbtnDown.isPressed())
    {
        setState(MG_STATES::down);
    }
    else if (mbtnRelax.changedToPressed())
    {
        setState(MG_STATES::off);
    }
    else if (mstate != MG_STATES::top && mstate != MG_STATES::bottom && mstate != MG_STATES::off) // if the lift isn't set to a position, hold
    {
        setState(MG_STATES::hold);
    }
}

void MogoStateMachine::update() // move the robot based on the state
{
    switch (mstate)
    {
    case MG_STATES::off:
        if (stateChanged())
        {
            mmtr.setBrakeMode(AbstractMotor::brakeMode::coast);
            mmtr.moveVoltage(0);
        }
        break;
    case MG_STATES::hold:
        if (stateChanged())
        {
            mmtr.setBrakeMode(AbstractMotor::brakeMode::hold);
            mmtr.moveVoltage(0);
        }
        break;
    case MG_STATES::up:
        if (stateChanged())
        {
            mmtr.moveVoltage(12000);
        }
        break;
    case MG_STATES::down:
        if (stateChanged())
        {
            mmtr.moveVoltage(-12000);
        }
        break;
    case MG_STATES::top:
        mmtr.setBrakeMode(AbstractMotor::brakeMode::hold);
        if (mrotation.get() < def::SET_MG_TOP_DEG - def::SET_MG_RANGE_DEG) // if the lift is below the minimum height
        {
            mmtr.moveVoltage(12000);
        }
        else if (mrotation.get() > def::SET_MG_TOP_DEG + def::SET_MG_RANGE_DEG) // if the lift is above the maximum height
        {
            mmtr.moveVoltage(-12000);
        }
        else // if the lift is in range, don't move
        {
            mmtr.moveVoltage(0);
        }
        break;
    case MG_STATES::bottom:
        mmtr.setBrakeMode(AbstractMotor::brakeMode::coast);
        if (mrotation.get() < -def::SET_MG_RANGE_DEG) // if the lift is below the minimum height
        {
            mmtr.moveVoltage(12000);
        }
        else if (mrotation.get() > def::SET_MG_RANGE_DEG) // if the lift is above the maximum height
        {
            mmtr.moveVoltage(-12000);
        }
        else // if the lift is in range, don't move
        {
            mmtr.moveVoltage(0);
        }
        break;
    }
}
