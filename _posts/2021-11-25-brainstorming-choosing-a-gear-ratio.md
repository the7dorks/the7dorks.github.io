---
layout: post
title: "Brainstorming: Choosing a Gear Ratio"
date: 2021-11-25
author: "Isaiah"
categories: Design
tags: Drivetrain-2.0.0
---
 
##### Drivetrain-2.0.0
Today we decided to plan out our drivetrain for our next robot. 

###### Design
Today we started planning drivetrain gear ratios. We decided to disregard chain, because chain can break, and it introduces additional friction and slop. Then a member from 333B made an acceleration simulation to calculate which ratio would be the fastest at rushing the mobile goals in the middle, by using information about the torque curves of V5 motors and assuming the robot weighs 15 pounds. Here are all our considerations:

- 600rpm, 7:3, 4"         @ 4.49 ft/s    <--- 333A now
- 600rpm, 5:3, 3.25"    @ 5.11 ft/s      <--- 355V now, 333A Change Up State bot; this worked for us with 4 motors, so with 6 we could do a faster ratio
- 100rpm, 1:3, 4"           @ 5.24 ft/s
- 200rpm, 1:2*, 3.25"  @ 5.67 ft/s    <--- 333A Change Up pushbot
- 200rpm, 3:5, 4"         @ 5.82 ft/s
- 100rpm, 1:5, 2.75"     @ 6.00 ft/s
- 600rpm, 5:3, 4"         @6.28 ft/s<br><br>
- For 600rpm with a 7:3 ratio on 4in wheels:      2.424s for goal rush
- For 600rpm with a 5:3 ratio on 3.25in wheels:   2.586s for goal rush
- For 100rpm with a 1:3 ratio on 4in wheels:      2.619s for goal rush
- For 200rpm with a 1:2 ratio on 3.25in wheels:   2.726s for goal rush
- For 200rpm with a 3:5 ratio on 4in wheels:      2.760s for goal rush
- For 100rpm with a 1:5 ratio on 2.75in wheels:   2.803s for goal rush
- For 600rpm with a 5:3 ratio on 4in wheels:      2.869s for goal rush

<br class='print-only'><br class='print-only'><br class='print-only'>
Given this data, we decided on the second one: 600rpm motor with a 5:3 ratio on 3.25” wheels. While this is not the theoretical fastest ratio, it would be faster for longer distances, because it has a higher top speed. <mark>Additionally, 3.25” wheels have screw holes, so we could attach the gear to the wheels, and have the whole wheel assembly be on a screw joint instead of a shaft, because screw joints are more sturdy and have less friction. This ratio also has the added benefit of using 600rpm motor cartridges, which have less slop.</mark>
