/**
 * LiftStateMachine.cpp
 *
 * This file contains the declaration of the LiftStateMachine class.
 * LiftStateMachine is a state machine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the lift.
 *
 * To use the state machine in auton, make sure you disable/reenable
 * the normal state machine tasks and run the specified action.
 */
#include "main.h" // gives access to LiftStateMachine and other dependencies

/* ----------------------------------------------------------- */
/*                      Public Information                     */
/* ----------------------------------------------------------- */
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

double LiftStateMachine::getAngle()
{
    return mrotation.get();
}

void LiftStateMachine::engageClaw()
{
    mclaw.toggle(false);
    std::cout << "claw engaged\n";
}

void LiftStateMachine::disengageClaw()
{
    mclaw.toggle(true);
    std::cout << "claw disengaged\n";
}

bool LiftStateMachine::goalInRange(double idistanceMM)
{
    return mdistClaw.get() < idistanceMM + 70 * mdistClaw.getObjectVelocity() && mdistClaw.get() > 0;
}

void LiftStateMachine::enableControl()
{
    mcontrolEnabled = true;
}

void LiftStateMachine::disableControl()
{
    mcontrolEnabled = false;
}

void LiftStateMachine::enablePID()
{
    mpidEnabled = true;
}

void LiftStateMachine::disablePID()
{
    mpidEnabled = false;
}

int LiftStateMachine::getGoalLocation(bool isafe)
{
    setState(LIFT_STATES::bottom);
    const double left = mdistLeft.get();
    const double center = mdistClaw.get();
    const double right = mdistRight.get();

    if (isafe)
    {
        if ((left != 0 && left < center + def::SET_HOLDER_EYES_DISTANCE_DIFF_MAX + 20) && (right == 0 || right > left)) // if the left sees the edge of the goal, and the right doesn't, go left
        {
            return 1;
        }
        else if ((right != 0 && right < center + def::SET_HOLDER_EYES_DISTANCE_DIFF_MAX + 20) && (left == 0 || left > right)) // if the right sees the edge of the goal and the left doesn't, go right
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

void LiftStateMachine::controlState() // update the state based on controller input
{
    if (mbtnToggle.changedToPressed())
    {
        if (mstate == LIFT_STATES::rings)
        {
            setState(LIFT_STATES::bottom);
        }
        else
        {
            setState(LIFT_STATES::rings);
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
    else if (mstate != LIFT_STATES::top && mstate != LIFT_STATES::bottom && mstate != LIFT_STATES::rings) // if the lift isn't set to a position, hold
    {
        setState(LIFT_STATES::hold);
    }

    if (mbtnClawToggle.changedToPressed()) // if pneumatics are manually toggled
    {
        moverrideDistance = true; // give manual control rights
        mclaw.toggle();
    }

    // // sensor toggler
    // if (moverrideDistance && mclaw.isEngaged() == !(mdistClaw.get() < def::SET_LIFT_DISTANCE_MIN_MM && mdistClaw.get() > 0)) // if sensor is overridden but agrees with manual instruction
    // {
    //     moverrideDistance = false; // reengage sensor
    // }

    // if (!moverrideDistance) // if the sensor isn't disabled
    // {
    //     if ((mdistClaw.get() < def::SET_LIFT_DISTANCE_MIN_MM && mdistClaw.get() > 0)) // if something is close enough to the distance sensor
    //     {
    //         mclaw.toggle(false);
    //     }
    //     else
    //     {
    //         mclaw.toggle(true);
    //     }
    // }
}

void LiftStateMachine::update() // move the robot based on the state
{
    if (stateChanged())
    {
        switch (mstate)
        {
        case LIFT_STATES::off:
            disablePID();
            mmtr.moveVoltage(0);
            break;
        case LIFT_STATES::hold:
            setLiftAngle(mrotation.get() + 10 * mrotation.getVelocity());
            break;
        case LIFT_STATES::up:
            disablePID();
            mmtr.moveVoltage(12000);
            break;
        case LIFT_STATES::down:
            disablePID();
            mmtr.moveVoltage(-12000);
            break;
        case LIFT_STATES::top:
            setLiftAngle(def::SET_LIFT_TOP_DEG);
            break;
        case LIFT_STATES::bottom:
            setLiftAngle(def::SET_LIFT_BOTTOM_DEG);
            break;
        case LIFT_STATES::rings:
            setLiftAngle(def::SET_LIFT_RINGS_DEG);
            break;
        }
    }

    if (mpidEnabled)
    {
        double pidResult = mpid.iterate(mpidTarget - mrotation.get());
        util::chop<double>(-1, 1, pidResult);
        mmtr.moveVoltage(12000 * pidResult);
    }
}

void LiftStateMachine::setLiftAngle(const double itarget)
{
    enablePID();
    mpidTarget = itarget;
}

void LiftStateMachine::run()
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
Motor &LiftStateMachine::mmtr = def::mtr_lift;
SolenoidWrapper LiftStateMachine::mclaw = SolenoidWrapper(def::sol_claw, false);
RotationSensor &LiftStateMachine::mrotation = def::rotation_lift;
DistanceSensor &LiftStateMachine::mdistClaw = def::distance_claw;
DistanceSensor &LiftStateMachine::mdistLeft = def::distance_eye_front_left;
DistanceSensor &LiftStateMachine::mdistRight = def::distance_eye_front_right;

/* -------------------------- State -------------------------- */
LIFT_STATES LiftStateMachine::mstate = LIFT_STATES::off;
LIFT_STATES LiftStateMachine::mlastState = LIFT_STATES::off;
bool LiftStateMachine::moverrideDistance = false;
bool LiftStateMachine::mengageClaw = mclaw.isEngaged();
bool LiftStateMachine::mcontrolEnabled = false;
bool LiftStateMachine::mpidEnabled = false;
double LiftStateMachine::mpidTarget = def::SET_LIFT_BOTTOM_DEG;

/* ------------------------- Controls ------------------------ */
ControllerButton &LiftStateMachine::mbtnToggle = def::btn_lift_toggle;
ControllerButton &LiftStateMachine::mbtnUp = def::btn_lift_up;
ControllerButton &LiftStateMachine::mbtnDown = def::btn_lift_down;
ControllerButton &LiftStateMachine::mbtnClawToggle = def::btn_claw_toggle;

/* -------------------------- Other -------------------------- */
PID LiftStateMachine::mpid = PID(0.06, 0.0, 0.0, 0.0, 0.0, 0.0, 500_ms);
double LiftStateMachine::holdForceFromAngle(double iangle) { return 0.0; }