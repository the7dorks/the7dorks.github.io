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
    : mcontrolEnabled(true), mstate(MG_STATES::off), mlastState(MG_STATES::off), /*mbtnToggle(def::btn_mg_toggle),*/ mbtnUp(def::btn_mg_up), mbtnDown(def::btn_mg_down), mbtnRelax(def::btn_mg_relax), mmtrLeft(def::mtr_mg_left), mmtrRight(def::mtr_mg_right), mrotation(def::rotation_mg)
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
    if (mcontrolEnabled)
    {
        if (mbtnUp.isPressed())
        {
            setState(MG_STATES::up);
        }
        else if (mbtnDown.isPressed())
        {
            setState(MG_STATES::down);
        }
        else
        {
            setState(MG_STATES::hold);
        }
    }
}

void MogoStateMachine::update() // move the robot based on the state
{
    printf("in update");
    switch (mstate)
    {
    case MG_STATES::off:
        if (stateChanged())
        {
            mmtrLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
            mmtrRight.setBrakeMode(AbstractMotor::brakeMode::coast);
            mmtrLeft.moveVoltage(0);
            mmtrRight.moveVoltage(0);
        }
        break;
    case MG_STATES::hold:
        def::display.setMiscData(2, std::to_string(mmtrLeft.getPosition()));
        if (stateChanged())
        {
            mmtrLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
            mmtrRight.setBrakeMode(AbstractMotor::brakeMode::hold);
            mmtrLeft.moveVoltage(0);
            mmtrRight.moveVoltage(0);
        }
        break;
    case MG_STATES::up:
        if (stateChanged())
        {
            mmtrLeft.moveVoltage(12000);
            mmtrRight.moveVoltage(12000);
        }
        break;
    case MG_STATES::down:
        if (stateChanged())
        {
            mmtrLeft.moveVoltage(-12000);
            mmtrRight.moveVoltage(-12000);
        }
        break;
    case MG_STATES::top:
        mmtrLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
        mmtrRight.setBrakeMode(AbstractMotor::brakeMode::hold);
        if (mmtrLeft.getPosition() < def::SET_MG_TOP_DEG - def::SET_MG_RANGE_DEG || mmtrLeft.getPosition() > def::SET_MG_TOP_DEG + def::SET_MG_RANGE_DEG) // if the lift is out of the target range
        {
            double voltage = (def::SET_MG_TOP_DEG - mmtrLeft.getPosition()) * 1200; // CHANGE CONSTANT
            util::chop<double>(-12000, 12000, voltage);
            mmtrLeft.moveVoltage(voltage);
            mmtrRight.moveVoltage(voltage);
        }
        else // if the lift is in range, don't move
        {
            mmtrLeft.moveVoltage(0);
            mmtrRight.moveVoltage(0);
        }
        break;
    case MG_STATES::bottom:
        mmtrLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
        mmtrRight.setBrakeMode(AbstractMotor::brakeMode::hold);
        if (mmtrLeft.getPosition() < def::SET_MG_BOTTOM_DEG - def::SET_MG_RANGE_DEG || mmtrLeft.getPosition() > def::SET_MG_BOTTOM_DEG + def::SET_MG_RANGE_DEG) // if the lift is out of the target range
        {
            double voltage = (def::SET_MG_BOTTOM_DEG - mmtrLeft.getPosition()) * 100; // CHANGE CONSTANT
            util::chop<double>(-12000, 12000, voltage);
            mmtrLeft.moveVoltage(voltage);
            mmtrRight.moveVoltage(voltage);
        }
        else // if the lift is in range, don't move
        {
            mmtrLeft.moveVoltage(0);
            mmtrRight.moveVoltage(0);
        }
        break;
    case MG_STATES::oneMogo:
        mmtrLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
        mmtrRight.setBrakeMode(AbstractMotor::brakeMode::hold);
        if (mmtrLeft.getPosition() < def::SET_MG_ONEMOGO_DEG - def::SET_MG_RANGE_DEG || mmtrLeft.getPosition() > def::SET_MG_ONEMOGO_DEG + def::SET_MG_RANGE_DEG) // if the lift is out of the target range
        {
            double voltage = (def::SET_MG_ONEMOGO_DEG - mmtrLeft.getPosition()) * 1200; // CHANGE CONSTANT
            util::chop<double>(-12000, 12000, voltage);
            mmtrLeft.moveVoltage(voltage);
            mmtrRight.moveVoltage(voltage);
        }
        else // if the lift is in range, don't move
        {
            mmtrLeft.moveVoltage(0);
            mmtrRight.moveVoltage(0);
        }
        break;
    }
}
