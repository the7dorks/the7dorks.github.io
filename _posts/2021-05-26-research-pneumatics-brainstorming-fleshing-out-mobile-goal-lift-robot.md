---
layout: post
title: "Research: Pneumatics | Brainstorming: Fleshing Out Mobile Goal Lift Robot"
date: 2021-05-26
author: "Porter Shawver"
categories: Research Brainstorming
tags:
---
##### Research
###### Understanding Pneumatics
We know that pneumatics are a source of extra power that we think we should use, but we also do not want to make our Robots too complicated. Because we were not familiar with pneumatics, they seemed very complicated, so we did some research, watching the following videos on YouTube:

<img class="responsive-img" src="/assets/pics/research/pneumatics-components-video.png">
<img class="responsive-img" src="/assets/pics/research/pneumatics-programming-video.png">

The programming video was fairly outdated and not very helpful, so we consulted the PROS documentation, which showed that we only need one function for controlling pneumatics:

{% highlight c linenos %}
pros::ADIDigitalOut piston (DIGITAL_SENSOR_PORT); // initialize the piston
piston.set_value(true); // extend the piston
piston.set_value(false); // retract the piston
{% endhighlight %}

###### Pneumatic Part Breakdown
For storing compressed air, we can use up to two <strong>air reservoirs</strong> each charged to 100 psi. Air reservoirs have an input valve for charging it with compressed air, then an output valve for sending air to other components. We can charge the reservoirs with a bike pump.

<img class="responsive-img" width="400" src="/assets/pics/research/pneumatics/air-reservoir.png">

To control whether or not the air is being sent to components, we can use a <strong>shut off valve</strong> that either lets air pass through, or blocks air from the reservoir and discharges air from the charged components:

<img class="responsive-img" width="400" src="/assets/pics/research/pneumatics/shut-off-valve.png">

The two pneumatic actuators are single- and double-acting pistons. Single-acting pistons (right) have a spring that pulls them in, then uses a single input of compressed air to push against the spring to extend the rod. Double-acting pistons (left) have no spring, but rather two input valves at other ends of the chamber. Air is let into one end at a time, and released from the other end to push the rod in both directions. Double-acting pistons can be more powerful because they do not need to work against a spring, but they also use more compressed air, needing it for both actuation directions.

<img class="responsive-img" width="400" src="/assets/pics/research/pneumatics/both-pistons.png">

To control when and where to send compressed air, we can use electronically controlled single- and double-acting solenoids, which each take one input and control when to send compressed air to either one or two output valves respectively. 

<img class="responsive-img" width="400" src="/assets/pics/research/pneumatics/both-solenoids.png">

Single-acting solenoids get pressure from the "P" valve, connected to the reservoir. When they are powered by the Brain, they allow pressure to flow to "A." When they are not powered, all pressure from "A is allowed to flow to "R:"

<img class="responsive-img" width="400" src="/assets/pics/research/pneumatics/single-solenoid-diagram.png">

Double-acting solenoids also get pressure from the "P" valve, connected to the reservoir. When they are powered by the Brain, they allow pressure to flow to "A," and all pressure from "B" is allowed to flow to "R." When they are not powered, they allow pressure to flow to "B," and all pressure from "A" is allowed to flow to "R."

<img class="responsive-img" width="400" src="/assets/pics/research/pneumatics/double-solenoid-diagram.png">

The reservoir only has one output, so to be able to use more than one component, we can use "t fittings," which take one input and output the pressure to two other paths. For this particular part, it does not matter which valve is used as an input.

<img class="responsive-img" width="400" src="/assets/pics/research/pneumatics/t-fitting.png">

We might not always want to use the pressure of the reservoir at full power, so we can use pressure control valves to reduce the pressure coming from the reservoir, by rotating the setting knob (shown at the left):

<img class="responsive-img" width="400" src="/assets/pics/research/pneumatics/pressure-control-valve.png">

###### 86868R Test Intake
On Instagram today, we found a video posted of a team testing an intake concept on a 3D printed Ring. They attached standoffs to chain attachment links and used lock bars for scooping up Rings:

<img class="responsive-img" width="400" src="/assets/pics/research/86868R-test-intake.png">

It appeared to pick up the Ring very well, however, it looked like it only would work if the Ring was in the perfect spot, which is unlikely to happen in Matches.

##### Brainstorming
###### Fleshing Out Robot-0.2.3
Today we made a better plan of <strong>Robot-0.2.3</strong> from yesterday:

<img class="responsive-img" width="400" src="/assets/pics/brainstorming/cad-mobile-goal-lifting-robot.png">

- Use a conveyor Ring lift in the back (shown with floating sprocket) to score Rings on the inner Mobile Goal. (Similar to VIQC Ringmaster team 21549A and <strong>Robot-0.2.0</strong>)
- Use a chainlift with a forklift on the front to lift goals in the air while keeping them level with the ground so they can be placed onto Platforms easily.
- Use a horizontal four bar like many In the Zone teams did to intake the inner Mobile Goal. It might be necessary to lift the chainlift out of the way when we do this.
- It might be possible to make the four bar place Mobile Goals directly into the forklift on the chainlift and vice versa, to prevent awkward situations where we need to put a Mobile Goal down and pick it up with the other Mobile Goal intake.

###### Not Using This Design
<mark>After thinking through how we think we would build this concept in the CAD above (in accordance with Design Goal #2 from "Design Brief: Set Team Goals," 5/23/2021), we do not think it would be a good idea to build a robot like this, <strong>because it would be too complicated</strong>, going against Design Goal #1 (Design Brief: Set Team Goals, 5/23/2021).</mark> The CAD showed us that, for the design to work, we would need the forklift to deploy, and possibly even the Ring intake because it needs to stick so far back. Even if that did work, we would need the Rings to move at a series of difficult angles with very little room. We are going to continue looking for other alternatives.
