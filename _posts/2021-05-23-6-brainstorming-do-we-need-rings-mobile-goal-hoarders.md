---
layout: post
title: "Brainstorming: Do We Need Rings? Mobile Goal Hoarders"
date: 2021-05-23
author: "Porter Shawver"
categories: Design Research
tags: Robot-0.0.0 Robot-0.0.1 Robot-0.1.0 Robot-0.1.1 Robot-0.1.2 Robot-0.1.3 Robot-0.2.0 Robot-0.2.1
---
> To meet Design Goal #1 (Design Brief: Set Team Goals, 5/23/2021), we want our first robot to be simple, so it is easy to build, repair, and improve on.

Because Mobile Goals account for 40% of all available points, we would be able to have a big impact if we only focused on elevating Mobile Goals. However, the AWP is still very important and it requires Rings, which Jac pointed out is not likely a major issue:

<img class="responsive-img" src="/assets/pics/brainstorming/jac-discord-only-rings-for-awp.png">
 
##### Goal Hoarding Robot Ideas
- Manipulating Mobile Goals probably will not be too difficult, but we will need a fast drivetrain to beat other Robots to Mobile Goals and to carry all the weight. To have an even number of drivetrain motors, and still have some left over to manipulate Mobile Goals, we could consider a six motor drivetrain.

###### Robot-0.0.0: Row of Mobile Goals
- Noah thought we could have a Mobile Goal intake that piles Mobile Goals in the back of the Robot: <br><img class="responsive-img" src="/assets/pics/brainstorming/noah-discord-store-mobile-goals.png">
- Like Noah, Lukas suggested carrying multiple Mobile Goals, but not stacked on top of each other to have a lower center of gravity:<br><img class="responsive-img" src="/assets/pics/brainstorming/lukas-discord-low-mobile-goals.png"><br>He compared it to a tow truck with cars in one long row:<br><img class="responsive-img" src="/assets/pics/brainstorming/lukas-tow-truck.png"><br>Jac compared it to a VIQC team holding a row of cubes:<br><img class="responsive-img" src="/assets/pics/brainstorming/jac-viqc-row-of-cubes.png">
- <strong>Robot-0.0.1</strong>: to get Mobile Goals in a row on our Robot, Jac suggested a forklift that lifts Mobile Goals high enough in the air to slide down a track to the back of the Robot:<br><img class="responsive-img" width="400" src="/assets/pics/brainstorming/jac-discord-forklift-sliding-mobile-goals.png">

- We started to realize how long a row of Mobile Goals would be. <mark>Holding three in a row is already beyond the expansion limit (3 * 13" = 39"), so we need a new idea.</mark>

###### Robot-0.1.0: "Shingling" Mobile Goals
- <mark>Jac suggested storing mobile goals stacked on top of each other, or "shingled," like shingles on a roof.</mark>
- In CAD, we found that a method like this would be very space efficient, only taking up 25 inches lengthwise:<br><img class="responsive-img" width="49%" src="/assets/pics/brainstorming/vertical-stacked-mobile-goals-horizontal-dimention.png"><img class="responsive-img" width="49%" src="/assets/pics/brainstorming/vertical-stacked-mobile-goals-vertical-dimention.png">
- <strong>Robot-0.1.1</strong>: modifying Jac’s sketched design above to include "shingled" Mobile Goals in CAD showed that something like that could be compact enough:<br><img class="responsive-img" width="400" src="/assets/pics/brainstorming/cad-shingled-mobile-goal-robot.png">
- <strong>Robot-0.1.2</strong>: Porter suggested using a four bar linkage to pick up Mobile Goals and move them to the back of the bot, then use a pneumatic platform in the middle of the Robot to hold up a third Mobile Goal like a pyramid, laid out in CAD:<br><img class="responsive-img" width="400" src="/assets/pics/brainstorming/cad-pyramid-mobile-goal.png">
- <strong>Robot-0.1.3</strong>: it also might even be possible to build a robot similar to the one in the Tipping Point game reveal video, but with a Mobile Goal lift on either side that can slide a Mobile Goal towards the middle, to hold three like this:<br><img class="responsive-img" width="400" src="/assets/pics/brainstorming/cad-double-forklift-mobile-goal-robot.png">

##### We Think We Should Use Rings
- > Even though the three "shingling" designs above might work well, they might not be good enough strategically. Elevating four Mobile Goals is not enough to guarantee a win, so only being able to hold three might not be a good idea. It also would be much harder to build a robot that could hold four/five, and the opposing Alliance would likely beat us to at least one Neutral Mobile Goal.
- Lukas also pointed out that <mark>the best skills teams are going to use Rings</mark> (simply because scoring seven Mobile Goals will take less than one minute), but we still need to be able to use Mobile Goals as well:<br><img class="responsive-img" src="/assets/pics/brainstorming/lukas-discord-skills-robots-need-rings.png">

###### VEXForum Research (Robot-0.2.0)
Team 21417B posted a CAD of a Ring / Mobile Goal Combination Robot that can hold one Mobile Goal off the back, then lifts Rings up with a tank tread conveyor:

<img class="responsive-img" width="400" src="/assets/pics/research/vf-cad-one-mobile-goal-and-ring-conveyor.png">

###### Robot-0.2.1: Ring / Mobile Goal Combination Robot Idea
- We might be able to make a Robot similar to this, but with a Mobile Goal forklift on three sides. Then, we could tilt the Mobile Goals different amounts so that only one Branch pokes under the conveyor. This way, we could hold three Mobile Goals, and put Rings on all three, including Neutral Mobile Goals. To be able to use the Mobile Goal lifts on the side, we might want the ability to strafe, so we should consider using an x-drive with angled wheels as shown:<br><img class="responsive-img" width="49%" src="/assets/pics/brainstorming/cad-three-mobile-goal-tilter-concept.png"><img class="responsive-img" width="49%" src="/assets/pics/brainstorming/cad-three-mobile-goal-tilter-concept-with-neutral.png"><br>However, <mark>we learned in Change Up that x-drives need to have good weight distribution to be able to drive well, and the angled wheels might not be able to get onto the platform</mark>.
