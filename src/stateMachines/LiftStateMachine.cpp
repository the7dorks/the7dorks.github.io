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
/*                      Public Information                     */
/* ----------------------------------------------------------- */
LiftStateMachine::LiftStateMachine()
    : mmtr(def::mtr_lift_left), mclaw(def::sol_claw_front), mrotation(def::rotation_lift), mdistance(def::distance_lift_claw), mstate(LIFT_STATES::bottom), mlastState(LIFT_STATES::bottom), moverrideDistance(false), mengageClaw(mclaw.isEngaged()), mbtnToggle(def::btn_lift_toggle), mbtnUp(def::btn_lift_up), mbtnDown(def::btn_lift_down), mbtnPneumaticToggle(def::btn_lift_pneumatic_toggle)
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

bool LiftStateMachine::goalInRange()
{
    return mdistance.getDistance() < def::SET_LIFT_DISTANCE_MIN_MM && mdistance.getDistance() > 0;
}

void LiftStateMachine::controlState() // update the state based on controller input
{
    if (mbtnToggle.changedToPressed())
    {
        if (mstate == LIFT_STATES::top || getRotation() > def::SET_LIFT_TOP_DEG / 2) // if the lift is at the top, or closer to the top
        {
            setState(LIFT_STATES::bottom);
        }
        else // if the lift is closer to the bottom
        {
            setState(LIFT_STATES::top);
        }
    }
    else if (mbtnUp.isPressed())
    {
        setState(LIFT_STATES::up);
    }
    else if (mbtnDown.isPressed())
    {
        setState(LIFT_STATES::down);
    }
    else if (mstate != LIFT_STATES::top && mstate != LIFT_STATES::bottom) // if the lift isn't set to a position, hold
    {
        setState(LIFT_STATES::hold);
    }

    if (mbtnPneumaticToggle.changedToPressed()) // if pneumatics are manually toggled
    {
        moverrideDistance = true; // give manual control rights
        mclaw.toggle();           // toggle
    }

    // sensor toggler
    // if (moverrideDistance && mclaw.isEngaged() == (mdistance.getDistance() < def::SET_LIFT_DISTANCE_MIN_MM && mdistance.getDistance() > 0)) // if sensor is overridden but agrees with manual instruction
    // {
    //     moverrideDistance = false; // reengage sensor
    // }

    // if (!moverrideDistance) // if the sensor isn't disabled
    // {
    //     if ((mdistance.getDistance() < def::SET_LIFT_DISTANCE_MIN_MM && mdistance.getDistance() > 0)) // if something is close enough to the distance sensor
    //     {
    //         mclaw.toggle(true);
    //     }
    //     else
    //     {
    //         mclaw.toggle(false);
    //     }
    // }
}

void LiftStateMachine::update() // move the robot based on the state
{
    switch (mstate)
    {
    case LIFT_STATES::off:
        if (stateChanged())
        {
            mmtr.setBrakeMode(AbstractMotor::brakeMode::coast);
            mmtr.moveVoltage(0);
        }
        break;
    case LIFT_STATES::hold:
        if (stateChanged())
        {
            mmtr.setBrakeMode(AbstractMotor::brakeMode::hold);
            mmtr.moveVoltage(0);
        }
        break;
    case LIFT_STATES::up:
        if (stateChanged())
        {
            mmtr.moveVoltage(12000);
        }
        break;
    case LIFT_STATES::down:
        if (stateChanged())
        {
            mmtr.moveVoltage(-12000);
        }
        break;
    case LIFT_STATES::top:
        mmtr.setBrakeMode(AbstractMotor::brakeMode::hold);
        if (getRotation() < def::SET_LIFT_TOP_DEG - def::SET_LIFT_RANGE_DEG || getRotation() > def::SET_LIFT_TOP_DEG + def::SET_LIFT_RANGE_DEG) // if the lift is out of the target range
        {
            double voltage = (def::SET_LIFT_TOP_DEG - getRotation()) * 1200;
            util::chop<double>(-12000, 12000, voltage);
            mmtr.moveVoltage(voltage);
        }
        else // if the lift is in range, don't move
        {
            mmtr.moveVoltage(0);
        }
        break;
    case LIFT_STATES::bottom:
        mmtr.setBrakeMode(AbstractMotor::brakeMode::coast);
        if (getRotation() < -def::SET_LIFT_RANGE_DEG || getRotation() > def::SET_LIFT_RANGE_DEG) // if the lift is outside the target range
        {
            double voltage = -getRotation() * 1200;
            util::chop<double>(-12000, 0, voltage);
            mmtr.moveVoltage(voltage);
        }
        else // if the lift is in range, don't move
        {
            mmtr.moveVoltage(0);
        }
        break;
    }
}

/* ----------------------------------------------------------- */
/*                     Private Information                     */
/* ----------------------------------------------------------- */
double LiftStateMachine::getRotation()
{
    double temp = mrotation.get() < -10 ? mrotation.get() + 360 : mrotation.get();
    return mrotation.get() < -10 ? mrotation.get() + 360 : mrotation.get();
}