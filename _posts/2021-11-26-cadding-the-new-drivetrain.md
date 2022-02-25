---
layout: post
title: "CADding: The New Drivetrain"
date: 2021-11-26
author: "Isaiah"
categories: Design 
tags: Drivetrain-2.0.0
---
##### Drivetrain-2.0.0

Now that we had all the data about the best drivetrain for our robot we decided we should design it in 3d design software, <mark>in line with Design Goal #2 in our Design Brief at the beginning of this notebook</mark>. 

###### Design

Here is the design that we decided on:

<img class="responsive-img" style="vertical-align:top" width="49%" src="/assets/pics/building/robot-2/1x3x1_6m_drivetrain_centered_motors.png">

The 1x3x1 c-channels allow the motors to all be mounted right next to each other in a very small amount of room. This is good, because we need to have room for a ring conveyor, an intaking claw, and a Mobile Goal partially within the robot on one side. It will also give us room for tracking wheels. 

Here is the gear ratio in closer detail in the CAD:

<br class='print-only'><br class='print-only'><br class='print-only'><br class='print-only'><br class='print-only'><br class='print-only'>

<img class="responsive-img" style="vertical-align:top" width="500px" src="/assets/pics/building/robot-2/cadoftrain.png">

- This design is meant to be as thin as possible to allow us the maximum amount of space for subsystems. The motors are all together in the middle of the drivetrain and out of the way. 
- Screw joints are used whenever possible to reduce friction and extra bracing is added to these joints whenever possible to reduce rubbing and increase strength and resiliency. Reducing friction will help increase speed and allow the robot to drive straighter improving consistency.
- The longest screws we have available are 2", but to fit the wheels and gears in between these c-channels, we need more than 2" of width, so those screws cannot reach all the way across. That is why you can see raised bearings in the drivetrain: they allow the use of <2" screws while maintaining stability.
