---
layout: post
title: "Programming: Updating Old Code to Work with this Robot"
date: 2022-01-07
author: ""
categories: Design Create
tags: Code
---

The LiftStateMachine explained in "Build Day: Motor and Rotation Sensor to Lift, Worked on Lift Code, Built Holder 1.1.1,and Mounted Radio" on 11/10/2021 for the last robot will be functionally identical when adapted for this bot. Additionally, <mark>a nearly identical state machine design was used for our ring intake and for the pneumatic holder</mark>. Because most of the code is exactly the same, we don't need to put it here. All specific changes can be seen in the code branch of the GitHub repository this notebook is hosted in.

###### Design
A significant change in the design of the code, however, was the transition to using static classes for our state machines instead of normal classes. When you make all the functions and variables of a class `static` in C++, it means there only exists one of that thing for every instance of the class. This makes sense for our case, because we only need one LiftStateMachine, one IntakeStateMachine, and one HolderStateMachine. When invoking the functions of any of these classes, it doesn't make sense for it to have to be a specific instance of the class. This would require you to create an object, then use it like so:

{% highlight c %}
LiftStateMachine liftStateMachineInstance = LiftStateMachine(); // create a LiftStateMachine instance
liftStateMachine.update() // run some function from the instance
{% endhighlight %}

This is more clunky than something like this, which better represents the real world objects the code is controlling:

{% highlight c %}
LiftStateMachine::update() // this runs the same code as above, but directly through the static function of the class.
{% endhighlight %}

###### Create
This design change was fairly easy in implement. Here are the primary changes screenshotted from the GitHub repository:

<img class="responsive-img" width="500" src="/assets/pics/motion_profiling/static changes.PNG">

Addittionally, instead of having a separate function from outside the thread that actually runs the state machine in a thread, we can have a function contained within the class, because of how multitasking is handled on the brain. This is what is changed to make this happen in main.cpp:

<img class="responsive-img" width="500" src="/assets/pics/motion_profiling/maincpp_static_changes.PNG">

