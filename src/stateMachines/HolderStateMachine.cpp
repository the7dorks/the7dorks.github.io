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

int HolderStateMachine::getGoalLocation(bool isafe)
{
    const double left = mdistLeft.get();
    const double center = mdistCenter.get();
    const double right = mdistRight.get();

    if (isafe)
    {
        if ((left != 0 && left < center + def::SET_HOLDER_EYES_DISTANCE_DIFF_MAX) && (right == 0 || right > left)) // if the left sees the edge of the goal, and the right doesn't, go left
        {
            return 1;
        }
        else if ((right != 0 && right < center + def::SET_HOLDER_EYES_DISTANCE_DIFF_MAX) && (left == 0 || left > right)) // if the right sees the edge of the goal and the left doesn't, go right
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (left == 0)
        {
            if (right == 0)
            {
                return 0; // center (neither see it)
            }
            else
            {
                return 2; // right (only right sees it)
            }
        }
        else if (right == 0) // left (only left sees it)
        {
            return 1; // left
        }
        else
        {
            if (left < right)
            {
                return 1; // left
            }
            else
            {
                return 2; // right
            }
        }
    }
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
    // AUTO GRABBER
    // if (mdistCenter.get() < def::SET_HOLDER_DISTANCE_MAX_MM && mdistCenter.get() != 0)
    // {
    //     setState(HOLDER_STATES::closed);
    // }
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
SolenoidWrapper HolderStateMachine::msol = SolenoidWrapper(def::sol_holder, false);
DistanceSensor &HolderStateMachine::mdistLeft = def::distance_eye_back_left;
DistanceSensor &HolderStateMachine::mdistCenter = def::distance_eye_back_center;
DistanceSensor &HolderStateMachine::mdistRight = def::distance_eye_back_right;

/* -------------------------- State -------------------------- */
HOLDER_STATES HolderStateMachine::mstate = HOLDER_STATES::open;
bool HolderStateMachine::mcontrolEnabled = false;

/* ------------------------- Controls ------------------------ */
ControllerButton &HolderStateMachine::mbtnToggle = def::btn_holder_toggle;