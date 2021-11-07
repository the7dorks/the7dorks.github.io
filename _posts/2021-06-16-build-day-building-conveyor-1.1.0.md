---
layout: post
title: "Build Day: Building Conveyor-1.1"
date: 2021-06-16
author: "Porter Shawver"
categories: Design Create Test Reflect
tags: Conveyor-1.1.0 Conveyor-1.1.1
---
##### Conveyor-1.1
###### Design
We determined yesterday that the next biggest issue to solve is the sprocket at the bottom of the conveyor that prevents the transfer of Rings. We think moving the sprocket forward and down in the direction of the chain so that the chain remains in the same place, but the sprocket is farther away from the transition point, to allow for more chain flex. To make this change, we can just move the sprocket shaft into pillow blocks on the front of its c-channel.

###### Create
Moving the sprocket did not take long, however, we realized the flaps on each stretch of chain contact the flaps on the other stretch, generating a lot of friction.

<img class="responsive-img" width="600" src="/assets/pics/building/robot-1/conveyor-1.1.0-flaps-hit.png">

###### Patch (Conveyor-1.1.1)
To account for this, we decided to synchronize the rotation of the chain so that each flap would pass through the gaps between flaps on the other. To do this, we needed to make sure each all of the flaps on both lengths of chain were the same distance apart. We chose eight links between each flap because the chain around the intakes is 32 links long, and 32 is easily divisible by eight. On the conveyor, there were 74 links, and because we could not reduce the length of chain, we increased it to 80 by adding a vertical half-cut c-channel to tension out the extra distance:

<img class="responsive-img" width="600" src="/assets/pics/building/robot-1/conveyor-1.1.1.jpg">

###### Test
<mark>The Rings no longer get jammed on the bottom sprocket of the conveyor.</mark> Sometimes, they get momentarily caught on various edges throughout the intake/conveyor system.

###### Reflect
The manipulation of Rings is not perfect, but it works fairly consistently. When something does go wrong&mdash;like a Ring stopping at the funnel and not going into the conveyor&mdash;the issue usually fixes itself within one second. <mark>This sort of reliability will give us a competitive edge at competition, where everything that can go wrong usually goes wrong ("Murphy's Law").</mark>