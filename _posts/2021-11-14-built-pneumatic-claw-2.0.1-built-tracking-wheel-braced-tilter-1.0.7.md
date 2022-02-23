---
layout: post
title: "Build Day: Pneumatic Claw 2.0.1, Tracking Wheels, and Braced Holder"
date: 2021-11-14
author: "Isaiah Stumme and Porter Shawver"
categories: Create Test  
tags: Claw-2.0.1 Robot-1 Holder-1.1.2
--- 

##### Robot-1

In order to make our Autonomous more consistent we decided to use tracking wheels and odometry. This allows us to tell where our robot is on the field at all times and be able to tell our robot exact coordinates to go to on the field. 

###### Create

We used a small Omni-Directional Wheel along with a Optical Shaft Encoder in each of our two tracking wheels along with some spacing and c channels. It took a little while to get the spacing right but soon we had near frictionless tracking wheels. 

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211114_155402.jpg">

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211114_155409.jpg">

##### Claw 2.0.1
The pneumatics pull the claw in, clamping onto the goal:

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211114_155222.jpg">
     
<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211114_155230.jpg">

###### Create
We also added a distance sensor so that the robot can see when a goal is close enough in the claw to be grabbed. This will be helpful for grabbing at the right time in autonomous:

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211114_155310.jpg">

Now we also use pressure limiters to decrease the amount of compressed air used on each actuation so that we can have more total actuations:

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211114_155424.jpg">

##### Holder-1.1.2

###### Create
We added more bracing to the holder.

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211114_155327.jpg">

<img class="responsive-img" width="500" src="/assets/pics/Photos-001/20211114_155348.jpg">

###### Test
Without the motors attached, it seems much more sturdy than before.
