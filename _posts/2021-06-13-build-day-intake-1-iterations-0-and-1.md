---
layout: post
title: "Build Day: Intake-1 Iterations 0 and 1"
date: 2021-06-13
author: "Porter Shawver"
categories: Create Test Reflect 
tags: Intake-1.0.0 Intake-1.1.0
---
##### Intake-1.0
Now that the lift was done, it was time for the intake. Really, we wanted to try the rubber band roller because they had worked well for other game elements in previous years, but we still did not know how well it would work for Rings, so we decided to try multiple options.

###### Create
We used an old rubber band roller from one of our Change Up robots that was a little too small, but adequate for testing:

<img class="responsive-img" width="500" src="/assets/pics/building/robot-1/intake-1.0.0.jpg">

###### Test
Today we started testing intake designs by attaching the lift to a 1x5x1 c-channel. It made it much easier to keep the intake at the right height off the ground:

<img class="responsive-img" width="500" src="/assets/pics/building/robot-1/temporary-test-base.jpg">

We also measured the distance between the two lift bars when it is all the way lowered in the CAD, and added a standoff with the right spacing to ensure the lift stopped at the right place when lowering for our testing:

<img class="responsive-img" width="500" src="/assets/pics/building/robot-1/temporary-lift-stop.jpg">

Then we tried spinning the rubber band roller and slowly pushing a ring into the intake to emulate the robot driving into it. Our observations:
- The Ring would reach the spinning roller and not get pulled in initially. This must mean that the force of friction from the ground was greater than the force of friction from the roller.
- <mark>Once the Ring got most of the way into the roller, it would shoot through very quickly</mark>.

Finally, we added a bent metal plate underneath the rubber band roller to allow the Rings to go up, not just sideways. When we tried spinning the roller again, the only change was that the Ring would not shoot through the intake like before, it would move some, but <mark>it seemed like it was getting jammed against the ramp</mark>. The ramp could not have been farther back, because then the Ring would not reach the rubber bands.

###### Reflect
> Because of the unique shape of the Rings, and the unique requirement of this design that the Rings need to go straight up immediately after being gathered, it seems like rubber band rollers are not going to be effective on this robot, even though they could work very well if we did not need the Rings to rapidly change direction. Regardless, we need a different solution.

##### Intake-1.1
###### Design
Because the Rings need to go up immediately after going in, anything that moves the rings by rubbing them like rubber bands probably wont work very well, so <mark>we decided to try hooking the Rings with standoffs instead</mark>. This does not require very much modification of the current design, just a slightly smaller sprocket.

###### Create
We used 18 tooth sprockets with chain attachment links for attaching standoffs:

<img class="responsive-img" width="49%" src="/assets/pics/building/robot-1/intake-1.1.0.jpg">

###### Test
We tested this new intake the same as the version 1.0, and noticed that:
- As soon as the Ring got to the standoffs, it would shoot into the robot immediately, unlike before.
- The Ring would get flung into the robot a little harder than with the rubber band roller.
- Not only would it go into the robot, sometimes <mark>the Ring would stay hooked to the standoff and fly up into the air</mark>.

###### Reflect
The fact that the Ring would go into the air is very promising, because it meets the requirement of going up right away. However, <mark>this design might cause problems when we try to funnel the Rings</mark>: we want the intake to pick up Rings from a wide range, then funnel them to line up with the Mobile Goal's post. With rubber band rollers, this would be easy, because the Rings could just slide towards the middle, but with standoffs, the Rings are hooked, so they cannot move laterally. To fix this, we could either find another solution or create a funnel on the outside of the robot, which would be the worst case scenario, and still not much of an issue, so will will ignore this for now.