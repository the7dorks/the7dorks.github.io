/**
 * IntakeStateMachine.cpp
 *
 * This file contains the declaration of the LiftStateMachine class.
 * IntakeStateMachine is a state machine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the lift.
 *
 * To use the state machine in auton, make sure you disable/reenable
 * the normal state machine tasks and run the specified action.
 */
#include "main.h" // gives access to IntakeStateMachine and other dependencies

/* ----------------------------------------------------------- */
/*                      Public Information                     */
/* ----------------------------------------------------------- */
INTAKE_STATES IntakeStateMachine::getState() { return mstate; }
void IntakeStateMachine::setState(const INTAKE_STATES istate)
{
    mstate = istate;
}

void IntakeStateMachine::enableControl()
{
    mcontrolEnabled = true;
}

void IntakeStateMachine::disableControl()
{
    mcontrolEnabled = false;
}

void IntakeStateMachine::controlState() // update the state based on controller input
{
    if (LiftStateMachine::getAngle() < def::SET_LIFT_MIN_DEG && mstate != INTAKE_STATES::override)
    {
        moverrideState = mstate;
        setState(INTAKE_STATES::override);
    }
    else if (mstate == INTAKE_STATES::override && LiftStateMachine::getAngle() > def::SET_LIFT_MIN_DEG)
    {
        setState(moverrideState);
    }

    if (mbtnToggle.changedToPressed()) // if the toggle button is pressed
    {
        if (getState() == INTAKE_STATES::in) // if it's already going in,
            setState(INTAKE_STATES::off);    // make it go out.
        else                                 // otherwise,
            setState(INTAKE_STATES::in);     // make in go in.
        mtoggling = true;                    // note that the system should remain the way it was toggled
    }

    if (mbtnIn.isPressed())
    {
        setState(INTAKE_STATES::in);
        mtoggling = false; // ignore the toggled state in future loops
    }
    else if (mbtnOut.isPressed())
    {
        setState(INTAKE_STATES::out);
        mtoggling = false; // ignore the toggled state in future loops
    }
    else if (mtoggling == false && mstate != INTAKE_STATES::override) // if it's supposed to ignore toggling...
    {
        setState(INTAKE_STATES::off); // just turn off
    }
}

void IntakeStateMachine::update() // move the robot based on the state
{
    switch (mstate)
    {
    case INTAKE_STATES::off:
        mmtr.moveVoltage(0);
        break;
    case INTAKE_STATES::in:
        mmtr.moveVoltage(12000);
        break;
    case INTAKE_STATES::slowIn:
        mmtr.moveVoltage(6000);
        break;
    case INTAKE_STATES::out:
        mmtr.moveVoltage(-12000);
        break;
    case INTAKE_STATES::override:
        mmtr.moveVoltage(0);
        break;
    case INTAKE_STATES::smart:
        // TODO: add sensors and program this section if desired

        break;
    }
}

void IntakeStateMachine::run()
{
    while (true)
    {
        if (mcontrolEnabled)
            controlState();
        update();
        pros::delay(20);
    }
}

/* ----------------------------------------------------------- */
/*                     Private Information                     */
/* ----------------------------------------------------------- */
/* ------------------------- Devices ------------------------- */
Motor &IntakeStateMachine::mmtr = def::mtr_intake;

/* -------------------------- State -------------------------- */
INTAKE_STATES IntakeStateMachine::mstate = INTAKE_STATES::off;
bool IntakeStateMachine::mtoggling = false;
bool IntakeStateMachine::mcontrolEnabled = false;
INTAKE_STATES IntakeStateMachine::moverrideState = INTAKE_STATES::off;

/* ------------------------- Controls ------------------------ */
ControllerButton &IntakeStateMachine::mbtnToggle = def::btn_intake_toggle;
ControllerButton &IntakeStateMachine::mbtnIn = def::btn_intake_in;
ControllerButton &IntakeStateMachine::mbtnOut = def::btn_intake_out;
