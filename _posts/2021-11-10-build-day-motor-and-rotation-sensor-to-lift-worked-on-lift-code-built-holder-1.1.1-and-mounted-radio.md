---
layout: post
title: "Build Day: Motor and Rotation Sensor to Lift, Worked on lift Code, Built Holder 1.1.1,and Mounted Radio"
date: 2021-11-10
author: "Isaiah Stumme and Porter Shawver"
categories: Create Test
tags: Lift-1.0.1 Code Robot-1 Holder-1.1.1
---
##### Lift-1.0.1

We now wanted to try to test and practice driving with our robot. To do this we needed to add the motor to the lift. 
 
###### Create
 
- We added the motor to the side of our lift.
- We mounted a Rotational Sensor to the lift, allowing us to know its position at all times.
- Worked on new code for the lift using the Rotational Sensor.
- Added a triangle of rubber bands to the lift to help counteract gravity's uneven pull on the lift. Because torque is given by r\*f\*sin(theta), the torque due to gravity acting on the lift changes as the lift changes height. The triangle banding creates a nonlinear torque that oppositely matches the force of gravity. This is a trick we picked up in Tower Takeover.  

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211110_214504.jpg">
<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211110_214457.jpg">

###### Test 

The lift worked great and was very much improved by the rubber bands.

##### Code
To set up control of the lift, we can use a state machine to set the state of the lift (like top, bottom, etc--what the lift should be doing) with the controlState() function, then actually make the robot execute the state with the update() function. The organizational paradigm is very useful for keeping everything straight. 

###### LiftStateMachine.hpp
{% highlight c linenos %}

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
    /* ------------------------- Devices ------------------------- */
    Motor &mmtr;
    SolenoidWrapper mclaw;
    RotationSensor &mrotation;
    DistanceSensorWrapper mdistance;

    /* -------------------------- State -------------------------- */
    MStates mstate, mlastState;
    bool moverrideDistance;
    bool mengageClaw;

    /* ------------------------- Controls ------------------------ */
    ControllerButton &mbtnToggle;          // botton to toggle the lift being up/down
    ControllerButton &mbtnUp;              // button to raise the lift
    ControllerButton &mbtnDown;            // button to lower the lift
    ControllerButton &mbtnPneumaticToggle; // button to toggle the claw actuated/not
};

namespace def
{
    extern LiftStateMachine sm_lift; // declares the sm_dt object as extern, to make sure it only gets constructed once
} // namespace def

{% endhighlight %}

###### controlState() and update() in LiftStateMachine.cpp
{% highlight c linenos %}

void LiftStateMachine::controlState() // update the state based on controller input
{
    if (mbtnToggle.changedToPressed())
    {
        if (mstate == LIFT_STATES::top || mrotation.get() > def::SET_LIFT_TOP_DEG / 2) // if the lift is at the top, or closer to the top
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

    if (moverrideDistance && mclaw.isEngaged() == mdistance.getDistance() < def::SET_LIFT_DISTANCE_MIN_MM) // if sensor is overridden but agrees with manual instruction
    {
        moverrideDistance = false; // reengage sensor
    }

    if (!moverrideDistance) // if the sensor isn't disabled
    {
        if (mdistance.getDistance() < def::SET_LIFT_DISTANCE_MIN_MM) // if something is close enough to the distance sensor
        {
            mclaw.toggle(true);
        }
        else
        {
            mclaw.toggle(false);
        }
    }
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
        if (mrotation.get() < def::SET_LIFT_TOP_DEG - def::SET_LIFT_RANGE_DEG) // if the lift is below the minimum height
        {
            mmtr.moveVoltage(12000);
        }
        else if (mrotation.get() > def::SET_LIFT_TOP_DEG + def::SET_LIFT_RANGE_DEG) // if the lift is above the maximum height
        {
            mmtr.moveVoltage(-12000);
        }
        else // if the lift is in range, don't move
        {
            mmtr.moveVoltage(0);
        }
        break;
    case LIFT_STATES::bottom:
        mmtr.setBrakeMode(AbstractMotor::brakeMode::coast);
        if (mrotation.get() < -def::SET_LIFT_RANGE_DEG) // if the lift is below the minimum height
        {
            mmtr.moveVoltage(12000);
        }
        else if (mrotation.get() > def::SET_LIFT_RANGE_DEG) // if the lift is above the maximum height
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

{% endhighlight %}


##### Robot-1
 
We also had to add the radio in order to start practicing.
 
###### Create
 
- We added the Radio to the top of our robot
- We decided to mount the Radio on standoffs with rubber from Omni-Directional Wheels
- The rubber can absorb vibrations to prevent problems communicating with the Controller
- The rubber also prevents static from reaching the Radio by creating a break in conductors. 
 
<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211110_214425.jpg">

##### Holder-1.1.1

After we added a Lexan ramp in Holder 1.1.0 to allow us to hold 3 mobile goals we where happy by the results but realized we lost some range. We found the lexon was blocking the Mobile Goal from going all the way into our grabber before the holder was powered. 

###### Build

We found the most effective way to do this was to add two Standoffs in order to extend the range and stop Mobile Goals from slipping out of the unpowerd grabber.

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211110_214440.jpg">

###### Test

The Grabber worked a lot better with the Standoffs and fixed our range problem.

