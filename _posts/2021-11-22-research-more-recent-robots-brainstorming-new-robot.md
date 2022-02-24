---
layout: post
title: "Research: Looking at More Recent Robots | Brainstorming: New Robot?"
date: 2021-11-22
author: "Jac Copeland"
categories: Analyze Research Design
tags:
---

##### Robot Design Determination
###### Analyze
We decided to approach this robot with the intention of scoring more points, more efficiently. To start we determined that rings were going to be at the center of our design process because rings accompanied mobile goals hold more scoring potential than mobile goals alone. 

This chart displays the thought that went into the scoring potential of various robot designs. 


| Scoring *non-objective scores are on a 1-4 scale, 4 being best 1 being worst* | 3 mobile goal robot                     | 2 mobile goal ring robot                |
|-------------------------------------------------------------------------------|-----------------------------------------|-----------------------------------------|
| **Max skills score:                                                           | Driver: 310 Programming: 310 Total: 620 | Driver: 370 Programming: 370 Total: 740 |
| ***Autonomous potential score                                                 | 2                                       | 4                                       |
| ****Driver potential score                                                    | 3                                       | 4                                       |
| Overall judgement                                                             |                                         | Winner                                  |


**Note: Skills scores are assumed maximums in both driver and programming. The robot with the 2 mobile goal would have to have scored 10 rings on 2 alliance goals as well as elevating all 7 goals and parking in order to reach a score of 370 for each field. This is fairly unrealistic, but comparatively to the 310 point cap that a mobile goal only robot has, it is more wise to construct a robot with better scoring potential in skills.
__________________________

***Note: The autonomous potential score is judged on a robot's ability to score during the 15 second autonomous period at the beginning of every match. A "3 mobile goal robot" can only, in the best case, score a total of 60 points by moving each of the yellow neutral goals to the robot's scoring zone. Due to the fact that robots cannot score additional points by elevating goals during the autonomous period, it is more effective and reliable to score a combination of mobile goals and rings during the autonomous period. Also unrealistic, the potential for scoring of a "2 mobile goal ring robot" during the autonomous period would be 120 if 10 rings were scored on both alliance goals and all neutral goals were brought to the alliance's scoring zone. This is an unrealistic act to perform during the autonomous period due to the 15 second time limitation, however, due to the necessity of ring interaction to gain the Win Point within autonomous as well as the overall scoring capability of scoring rings as well as getting a neutral goal, makes the overall autonomous potential with a "2 mobile goal ring robot" far greater than that of a "3 mobile goal robot." Because of this, the alliance can gain an advantage with win points, autonomous points, and the autonomous bonus. 

___________________________

****Note: The driver potential score is judged on a robot’s ability to score during the 1:45 driver control period. With a robot that can do more, more scoring is possible. By adding ring capabilities the “2 mobile goal ring robot” can interact and score more game elements than the “3 mobile goal robot” making it have a higher scoring potential and a more versatile robot overall earning it the higher score on the rubric.

___________________________

#### After deciding which robot we wanted to approach, we began the design process.

##### Design
We shared the github repository that this notebook is hosted in with 333B to make it easier for us to share CAD designs, because sharing with Inventor is difficult otherwise.

##### Research
###### 9181W Skills Video
Today we  analyzed 9181W’s programming skills video and got several ideas for designs to explore. The first is to use a combination of standoffs and zipties to hold a Mobile Goal in the robot shown below. This could prove useful for a more efficient Mobile Goal holder.

<img class="responsive-img" width="600" src="/assets/pics/Photos-001/22112021-9181robot.png">


- The lift on this robot sticks out a lot farther than ours does which allows them to stick farther over the lip of the Platform and elevate Mobile Goals much more quickly.

> - Finally their layout of a Ring intake and Mobile Goal lift on one end with a Mobile Goal holder on the other for loading Rings seems very optimal because it allows them to fill a Mobile Goal with Rings while also holding and then elevating a Mobile Gaol with the other side. It also leaves

###### Drivetrain Research and Brainstorming
- After seeing robots with powerful drivetrains dominate by being able to beat other robots to the center Mobile Goals at the beginning, we decided we need to be faster and stronger, probably by using a 6 motor drivetrain.

- To be able to use 6 motors on the drivetrain and still be able to build a robot similar to 9181W (which only uses four motors on the drivetrain), we need some way to share motors, or use additional pneumatics.

- We could use a drivetrain differential, which could allow the drivetrain motors to power a Mobile Goal hoarder that works by spinning motors against each other.


- Here is an example of a 4 motor drivetrain differential from the Apex Alliance: 
<img class="responsive-img" width="500" src="/assets/pics/building/robot-1/ExsampleOfBot.png">

- This might not be the best, because it can only move either the drivetrain or Mobile Goal holder, but not both at once, which could make our robot slower. After doing some research, we discovered that it also might not work with 6 motors, so this differential is not the solution for motor sharing.

- Using an example from this video, it would be possible to make a differential that allows the robot to both drive and power the Mobile Goal holder at the same time, just a little slower for each. https://www.youtube.com/watch?v=2NL3bhBeIWk&start=230
> - Ultimately, using any sort of differential is promising, but potentially very complicated, which we need to avoid, because additional complexity makes robots harder to build, and less likely to work as consistently.
- We could have the ring intake powered by the drivetrain, but ratcheted so that it doesn’t go down when we reverse. This could work, because we only need to intake Rings when the robot drives forward, however, we would not have the option to move the intake without also moving the drivetrain, which could potentially be problematic.

###### Mobile Goal Holder Research and Brainstorming

We could make the Mobile Goal holder be powered by pneumatics. Adding more pneumatics might make us run out of air, but this was not at all an issue for our last robot, and we will likely only actuate the pneumatics a few times per match. <mark>Because this is the simplest to design and build, we are choosing to go with this pneumatic holder design (at least until we test it in the coming days). This will allow us to be fast, like 355V at our last competition, with a 6 motor drivetrain, as well as intaking rings and lifting goals like 9181W.</mark>
