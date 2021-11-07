---
layout: post
title: "Build Day: Building Conveyor-1.0 and Intake-1.5 | Game Manual Update"
date: 2021-06-15
author: "Porter Shawver"
categories: Analyze Design Create Test Reflect
tags: Conveyor-1.0.0 Conveyor-1.0.1 Intake-1.5.0 Intake-1.5.1
---

##### Conveyor-1.0
###### Create
The basic idea for the conveyor that brings Rings to the top of Mobile Goal Branches was designed in CAD, but its specific implementation was left to interpretation, because we did not know how the Rings would behave in real life. <mark>Now that we know flaps are the best overall at moving Rings, we can easily build the conveyor.</mark>

We used a 1x3x1 c-channel for the ramp instead of a 1x2x1 so it could be centered. We used a hinge to attach it at the base, because it will be easier to adjust in the future if we need to. For now, it is only attached with the hinge.

<img class="responsive-img" width="49%" src="/assets/pics/building/robot-1/conveyor-1.0.0.jpg">
<img class="responsive-img" style="vertical-align:top" width="49%" src="/assets/pics/building/robot-1/conveyor-1.0.0-top.jpg">

###### Test
To test Conveyor-1, we put Rings into the bottom of the intake and let them go up through the conveyor. This did not work very well, because the Rings would fall out of the sides of the intake and conveyor or get jammed in the transition between the intake and conveyor. Additionally, the shaft joint at the top of the conveyor had a lot of friction.

###### Reflect
While flaps are good at moving Rings, they are not as good at controlling them on their own as standoffs, so we need to build more assistive control. The friction of the top roller appeared to be coming from the pillow block-standoff connection; because pillow blocks are designed to be attached flush with c-channels, attaching them to standoffs can make them crooked. Lastly, the conveyor was very unstable because it was only attached with a flexible hinge. Both the intake and conveyor need work, but we will focus on the conveyor for now, because it should be an easier fix, and we are already working on it.

##### Conveyor-1.0.1
###### Design
We need walls to prevent the Rings from falling out the sides, and <mark>we believe it would be best to make them out of lexan so they add only negligible friction and weight</mark>. To do this, we need to modify the top of the conveyor to have holes open to mount lexan vertically, so we can also solve the pillow block-standoff connection issue <strong>at the same time</strong>. We will add more bracing to the conveyor as well. It must be braced close to the bottom, because when the lift raises, the only available brace points are at the bottom.

###### Create
We switched the standoffs to a vertical c-channel to attach the lexan walls and shaft joint to. To brace the conveyor at the bottom, we added a c-channel with a standoff that we could also use to brace the lexan. There was still a very big gap between the 1x3x1 ramp and lexan walls, so we wrapped chain lengthwise around the standoffs to prevent Rings from falling through.

<img class="responsive-img" width="400" src="/assets/pics/building/robot-1/conveyor-1.0.1.png">

###### Test
The intake was still mostly unable to successfully bring Rings to the conveyor, so we mostly had to put Rings directly into the conveyor manually. Once in the conveyor, Rings would smoothly move very quickly through, often shooting multiple feet out of the end.

###### Reflect
Obviously the intake did not improve, but the conveyor works very well. We met our requirements of creating a lightweight wall with minimal friction, especially with the addition of chain as Ring support that can deform to help support the Rings without resistance in all orientations. However, we still need to fix the issue of Rings falling out of the sides of the intake and getting caught in the transition between the intake and conveyor as shown below.

<img class="responsive-img" width="600" src="/assets/pics/building/robot-1/conveyor-1.0.1-jammed-ring.jpg">

##### Intake-1.5
###### Analyze
The Rings appear to have such a tendency to fall out of the sides of the intake because of the width of the lexan wall. When the Rings are oriented as shown below, the sides ride on the edge of the wall (labeled with red), which is very unstable, because the curvature of the Rings contact the wall at an angle (shown with blue) to create a component of normal force parallel with the wall, that pushes the Rings towards the sides. <mark>Essentially, the lexan edges make the Rings slip to the sides.</mark>

<img class="responsive-img" width="600" src="/assets/pics/building/robot-1/intake-1.4.0-top.jpg">

###### Design
To increase stability, we could replace the existing wall with a larger wall whose edges cannot interfere with Rings (labelled with green in the image above). When we had this idea, we also realized we could add more sets of chain on the intake to increase the range it can intake Rings from. We did not do this on Intake-1.4, because Intake-1.3 only had rollers on the side and did not work well, but with a bigger wall, it might be more effective, and is worth trying to increase the range of the intake. We will also add a funnel to move Rings to the middle now that the intake is wider than the conveyor.

###### Create
Increasing the size of the wall was as simple as cutting a larger piece of lexan (labelled with blue), adding more chain was as simple as replacing the old spacing with more sprockets (labelled with green), and creating a funnel only took 2 conveniently placed 45 degree angle gussets (labelled with red):

<img class="responsive-img" width="600" src="/assets/pics/building/robot-1/intake-1.5.0.png">

###### Test
When intaking Rings, a wider range of positions worked. <mark>The Rings moved to the center and did not fall out the sides like before.</mark> As the intake design gets more refined, we are starting to test increasingly difficult situations. For example, we have now discovered that the Rings only intake well when the are oriented with the curve wrapping around the sprocket, because they can get lifted up the wall easily, but when they are oriented the other way, they get pushed towards the bottom of the wall, and do not go up. <mark>The Rings still get jammed in the transition from intake to conveyor.</mark>

###### Patch (Intake 1.5.1)
To fix the intake's Ring orientation issue, we simply added a lexan hook at the bottom of the wall:

<img class="responsive-img" width="600" src="/assets/pics/building/robot-1/intake-1.5.1.png">

###### Reflect
<mark>The intakes could use some more work, but could be good enough for early competitions, so we are going to move on for now.</mark> The next big issue is the jamming of Rings at the transition from intake to conveyor. We think this issue is from the position of the sprocket at the bottom of the conveyor, as can be seen in the third image of this post. Usually, the chain can deform to account for the awkward shape of the Rings, but the sprocket at the bottom of the conveyor prevents this enough to completely prevent the intaking of Rings in certain orientations.

##### Game Manual Update
There was a Game Manual Update today. The only notable change was a correction to a contradiction in the Robot Skills scoring rules as noted in "Design Brief: Understand the Problem." The correction is as follows: "A blue Alliance Mobile Goal that ends the Match in the red Alliance Home Zone is not worth any points. However, it would still receive the points for any Rings which are Scored on / in it."