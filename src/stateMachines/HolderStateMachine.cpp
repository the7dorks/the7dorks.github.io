/**
 * HolderStateMachine.cpp
 * 
 * This file contains the declaration of the HolderStateMachine class.
 * HolderStateMachine is a state machine.
 * It has an enumeration of different possible states to make it easy 
 * for the user to control the holder.
 * 
 * To use the state machine in auton, make sure you disable/reenable
 * the normal state machine tasks and runt the specified action.
 */
#include "main.h" // gives access to HolderStateMachine.hpp and other dependancies

/* ----------------------------------------------------------- */
/*                      Public Information                     */
/* ----------------------------------------------------------- */
HOLDER_STATES HolderStateMachine::getState() { return mstate; }
void HolderStateMachine::setState(const HOLDER_STATES istate)
{
    mstate = istate;
}

void HolderStateMachine::enableControl()
{
    mcontrolEnabled = true;
}

void HolderStateMachine::disableControl()
{
    mcontrolEnabled = false;
}

void HolderStateMachine::controlState()
{
    if (mbtnToggle.changedToPressed()) // if the toggle button is pressed
    {
        if (getState() == HOLDER_STATES::open) // if it's already open,
            setState(HOLDER_STATES::closed);   // close it.
        else                                   // otherwise,
            setState(HOLDER_STATES::open);     // open it.
    }
}

void HolderStateMachine::update()
{
    switch (mstate)
    {
    case HOLDER_STATES::open:
        if (msol.isEngaged())
            msol.toggle();
        break;
    case HOLDER_STATES::closed:
        if (!msol.isEngaged())
            msol.toggle();
        break;
    case HOLDER_STATES::smart:
        // TODO: add sensors and program this section if desired
        break;
    }
}

void HolderStateMachine::run()
{
    if (mcontrolEnabled)
        controlState();
    update();
    pros::delay(20);
}

/* ----------------------------------------------------------- */
/*                     Private Information                     */
/* ----------------------------------------------------------- */
/* ------------------------- Devices ------------------------- */
SolenoidWrapper HolderStateMachine::msol = SolenoidWrapper(def::sol_holder, false);

/* -------------------------- State -------------------------- */
HOLDER_STATES HolderStateMachine::mstate = HOLDER_STATES::open;
bool HolderStateMachine::mcontrolEnabled = false;

/* ------------------------- Controls ------------------------ */
ControllerButton &HolderStateMachine::mbtnToggle = def::btn_holder_toggle;