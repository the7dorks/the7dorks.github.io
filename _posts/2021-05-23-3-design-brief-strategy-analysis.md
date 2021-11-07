---
layout: post
title: "Design Brief: Strategy Analysis"
date: 2021-05-23
author: "Porter Shawver"
categories: Analyze
---
##### Scoring Analysis
###### Maximum Point Calculations
Based on the VEX Field CAD models, we believe four Rings can safely fit on Neutral Mobile Goal Branches: 

<img class="responsive-img" width="400" src="/assets/pics/game_analysis/four-rings-on-branch-cad.png">

With that, the maximum scoring potential of all the goals is:

| Mobile Goal Type | Score from Maximum Rings | Total Potential Score | Total Potential Score from All Mobile Goals |
|------------------|--------------------------|-----------------------|---------------------------------------------|
| <strong>Alliance Mobile Goal</strong>| 10 Rings * 3 points = 30 points | 30 points/Mobile Goal + 40 points from Elevating = <mark>70 points/Mobile Goal</mark>  | 2 Mobile Goals * 70 points of potential = <mark>140 points</mark> |
| <strong>Opposing Alliance Mobile Goal</strong> | 0 points (30 points in Robot Skills) | 0 points/Mobile Goal (<mark>70 points/Mobile Goal in Robot Skills</mark>)| 0 points (<mark>140 points in Robot Skills</mark>) |
| <strong>Short Neutral Mobile Goal</strong> | 2 Branches * 4 Rings * 3 Points = 24 points | 24 points per Mobile Goal + 40 points from Elevating = <mark>64 points/Mobile Goal</mark> | 2 Mobile Goals * 64 points of potential = <mark>128 points</mark> |
| <strong>Tall Neutral Mobile Goal</strong> | 2 Low Branches * 4 Rings * 3 points + 2 Low Branches * 4 Rings * 10 points = 104 points | 104 points + 40 points from Elevating = <mark>144 points</mark> | -> <mark>144 points</mark> |

In total, the maximum scores are:
- 20 (Autonomous Bonus) + 140 (Alliance Mobile Goals) + 0 (Opposing Alliance Mobile Goal) + 128 (Short Neutral Mobile Goals) + 144 (Tall Neutral Mobile Goal) + 60 (2 * 30 for Elevated Robot) = <mark>492 points for an Alliance in a head-to-head Match</mark>.
- 280 (Alliance Mobile Goals) + 128 (Short Neutral Mobile Goals) + 144 (Tall Neutral Mobile Goal) + 30 (for Elevated Robot) = <mark>582 points for Skills Matches</mark>.

###### Point Distributions
In determining where to direct our efforts, it is helpful to understand from where the most points can be earned:

<img class="responsive-img" width="800" src="/assets/pics/game_analysis/point-distribution-by-mobile-goal-potential-pie-chart.png">
<div style="page-break-inside:avoid"><img class="responsive-img" width="800" src="/assets/pics/game_analysis/point-distribution-by-scoring-type-pie-chart.png"></div>

> Notably, the most points are available from elevating Mobile Goals, but scoring Rings on the tall Neutral Mobile Goal is the next best option, because there is such a high Ring capacity on that individual goal.

##### Match Strategy
###### Game Theory
> When thinking through strategy, it is important to consider not only the points every action earns our Alliance, but also the effect it has on the opposing Alliance's scoring opportunities.

To do this analysis, we use the following game theory terms: 
- Zero-sum: when our Alliance does something that scores an equal number of points as it descores from the opposing Alliance. 
- Positive-sum: when scoring points for our Alliance does not take anything away from the opposing Alliance.
- Negative-sum: when our Alliance takes points from the opposing Alliance without earning any points.

For this game, we will use these terms to analyze the effects our Alliance can have on the opposing Alliance's score and potential score. For example, if we steal an empty Scored short Neutral Mobile Goal from the opposing Alliance's Home Zone, we are reducing their score by 20 points and their <strong>potential score</strong> by another 44 points (`8 * 3 + 20`), because they can no longer score Rings on that Mobile Goal or choose to Elevate it later in the game (<mark>moving a Mobile Goal from a "Scored" position to an "Elevated" position is only an increase of 20 points, not 40</mark>). Additionally, in taking the Mobile Goal, we increase our <strong>potential score</strong> by 64 points, because we now have the option to Elevate the Mobile Goal with eight Rings (`40 + 8 * 3`). In this example, the score <strong>difference</strong> only changed by 20 points, but the total potential score difference changed by 128 points (`20 + 44 + 64`). <mark>Because the amount our Alliance gained was equal to the amount taken from the opposing Alliance, it was a zero-sum interaction.</mark>

Classification of Interactions:
<table>
<thead>
  <tr>
    <th>Zero-Sum</th>
    <th>Positive-Sum</th>
    <th>Negative-Sum</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>
      <ul>
        <li>Autonomous Bonus</li>
        <li>Anything using Neutral Mobile Goals</li>
        <li>Rings "Scored" on Neutral Mobile Goals</li>
      </ul>
    </td>
    <td>
      <ul>
        <li>Scoring Rings</li>
        <li>Anything using Alliance Mobile Goals</li>
        <li>Elevating Robots</li>
      </ul>
    </td>
    <td>
      <ul>
        <li> Hoarding opposing Alliance Mobile Goals</li>
      </ul>
    </td>
  </tr>
</tbody>
</table>

Notes:
- It is possible to score a total of 72 Rings on Mobile Goal Branches&mdash;an amount equal to the total number of Rings each Match. Therefore, <mark>it seems unlikely to be able to limit the opposing Alliance's access to Rings, especially considering they have guaranteed access to 15 Rings each Match as Match Loads</mark>. Because of this fact, we are not going to consider the scoring of Rings to take potential score away from the opposing Alliance.
- Classification of the Autonomous Bonus is slightly more complicated, because it is awarded after the Autonomous period and it is possible to tie, so winning does not directly take anything away from the opposing Alliance. The reason we classify it as a zero-sum interaction is because, in the event of a tie, the Autonomous Bonus has no effect on the difference in score between the two Alliances, so it can be ignored. After neglecting ties, one Alliance must win and one must lose. If an Alliance were to win, they would be effectively taking the Autonomous Bonus from the opposing Alliance, because the opposing Alliance would win the Autonomous Bonus otherwise. Therefore, <mark>when won, the Autonomous Bonus is zero-sum, and thus worth 40 points&mdash;double its 20 point value</mark>.
- <mark>Points scored by Rings can be switched between Alliances depending on which Home Zone it is in</mark>, meaning they sometimes behave as zero-sum objects. Importantly, <mark>scoring Rings on Neutral Mobile Goals increases the Mobile Goal's actual value</mark>.

###### Application of Game Theory to Strategy
> Game theory does not stop with the simple classification of interactions; it allows us to better understand the true values of all the game elements. Every element is worth as many points it gives our Alliance <strong>in addition to</strong> the amount of points the opposing Alliance would get if they had it instead. Because positive-sum scoring methods do not take anything away from the opposing Alliance, their values are exactly what they seem. However, <strong>negative- and zero-sum scoring methods are usually worth more than the values assigned to them in the Game Manual</strong>.

True values of Mobile Goals:

| Mobile Goal Type              | Assigned Value        | Point Type   | True Value*            | Total True Value from All Mobile Goals* |
|-------------------------------|-----------------------|--------------|------------------------|----------------------------------------|
| Alliance Mobile Goal          | 70 points/Mobile Goal | Positive-sum | 70 points/Mobile Goal  | 140 points                             |
| Opposing Alliance Mobile Goal | 0 points/Mobile Goal  | Negative-sum | 70 points/Mobile Goal  | 140 points                             |
| Short Neutral Mobile Goal     | 64 points/Mobile Goal | Zero-sum     | 128 points/Mobile Goal | 256 points                             |
| Tall Neutral Mobile Goal      | 144 points            | Zero-sum     | 288 points             | 288 points                             |

*This "true value" is only true if the opposing Alliance would use <strong>all</strong> the points of a given Mobile Goal you did not take. In reality, this value is likely going to be lower than listed (especially early-season when robots cannot reach the maximum score), and varies a lot depending on the capabilities of the opposing Alliance. These values are still useful, but should be considered in the context of the opposing Alliance's abilities.

###### Average Scoring Pace Perspective
To win a head-to-head Match, our Alliance will need to score more points than the opposing Alliance. To score more total points than the opposing Alliance, we need to score more points on average for the entire duration of the Match. For this to be true, our Alliance needs to score at least as many points as the opposing Alliance at every moment in the Match; if we score less than the opposing Alliance at any time, we either need to have a strong enough lead already or make up the discrepancy later in the Match. Because both Alliances have access to the same scoring objects and the VRC is continuous (opposed to turn-based), it makes more sense to put this in terms of pace: <mark>our Alliance needs to score points faster on average than the opposing Alliance to win</mark>.

To take best advantage of this fact, we should keep in mind the amount of time it takes to score a certain amount of points. For example, if, on average, it takes 15 seconds to elevate one Mobile Goal, and three seconds to score one Ring on an Alliance Mobile Goal Branch, scoring a Mobile Goal would give ~2.67 points/second (`40 points / 15 seconds`) while the Ring would give 1 point/second (`3 points / 3 seconds`). In this case, scoring Mobile Goals is much more time-effective. This is not to say, however, that Mobile Goals are always a better scoring method, for a number of reasons:
- The amount of time each action takes each robot to complete will be very different.
- This scenario does not take into account the effect on the opposing Alliance. (Although, opposing Alliance and Neutral Mobile Goals, as zero-sum scoring elements, will generally have a much greater negative effect on the opposing Alliance when compared to positive-sum Rings.)
- <mark>The actions and abilities of the opposing Alliance might have a significant impact on the amount of time it takes to do certain actions.</mark> For example, it would likely take much longer to take Mobile Goals from inside an opposing Robot. 

###### Guaranteed Win Methods
<mark>If we had a theoretically unbeatable strategy at competitions, we would win every time.</mark> While such a strategy would likely be unreasonable to execute against competent opponents, a failed "guaranteed-win" strategy could still win. <mark>It would also be good to be aware of what the opposing Alliance might attempt, so we can more easily counter their strategy.</mark>

"Guaranteed-win" strategies must make it impossible for the opposing Alliance to earn more points than our Alliance. In these examples, we assume that the opposing Alliance will score <strong>all</strong> the remaining points to show that the strategy is unbeatable.
<table>
  <thead>
    <tr>
      <th>Strategy</th>
      <th>Alliance Score</th>
      <th>Opposing Alliance Score</th>
      <th>Counter Strategy</th>
      <th>Feasibility</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Elevate two Robots and all five scorable Mobile Goals.</td>
      <td>2 * 30 + 5 * 40 = <mark>260</mark></td>
      <td>2 * 30 + 2 * 70 + 20 = <mark>220</mark></td>
      <td>Take and elevate any one Neutral Mobile Goal to win by 40 points.</td>
      <td>It is not likely for our Alliance to guarantee the possession of all three Neutral Mobile Goals, so this likely is not going to happen often.</td>
    </tr>
    <tr>
      <td>Elevate two filled Alliance Mobile Goals, two Robots, the filled tall Neutral Mobile Goal, and tie Autonomous.</td>
      <td>2 * 70 + 2 * 30 + 144 + 10 = <mark>354</mark></td>
      <td>2 * 70 + 2 * 30 + 2 * 64 + 10 = <mark>338</mark></td>
      <td>The opposing Alliance could either win Autonomous or beat our Alliance to getting the tall Neutral Mobile Goal.</td>
      <td>This strategy might be possible, but it requires that our Alliance gets the most valuable Mobile Goal, and at least tying Autonomous, which would both be very hard to guarantee.</td>
    </tr>
    <tr>
      <td>Elevate all three filled Alliance Mobile Goals and two Robots.</td>
      <td>2 * 64 + 144 + 2 * 30 = <mark>332</mark></td>
      <td>2 * 70 + 2 * 30 + 20 = <mark>220</mark></td>
      <td>Take and elevate any one Neutral Mobile Goal.</td>
      <td>Again, it is not likely to be able to guarantee possession of all three Neutral Mobile Goals. </td>
    </tr>
  </tbody>
</table>

There certainly are many more "guaranteed-win" strategies, but these three can give us some important insight:
- Because it is not likely our Alliance will be able to all five scorable Mobile Goals, we should not plan on winning only by elevating Mobile Goals; <mark>Rings are definitely going to be very important</mark>.
- It is not a good idea to rely on getting the tall Neutral Mobile Goal, because there is a good chance that the opposing Alliance would try to do the same. <mark>We should always have a backup plan</mark>.
- In these scenarios that assume the opposing Alliance is perfect, <mark>the "true value" of goals is <strong>very</strong> important</mark>. The first scenario above has the lowest scores, but still guarantees a win because it takes so much scoring opportunity from the opposing Alliance.

###### Defense
When we play defense, our Alliance would score less points than it would if we were to play offense. The goal of defense is to decrease the amount of points the opposing Alliance would score. Defense is only helpful if it decreases the opposing Alliance's score by more that it does our Alliance's score. From an average scoring pace perspective, defense is helpful when our Alliance can spend a small amount of time to set the opposing Alliance back a larger amount of time.

Defensive ideas:
- Tip Mobile Goals on their sides. If the opposing Alliance is unable to right tipped over Mobile Goals, we could easily reduce their scoring capacity by a lot. It should be noted that our Alliance cannot cause Rings Scored on the opposing Alliance's Alliance Mobile Goals to no longer meet the definition of "Scored."
- Push Mobile Goals underneath the opposing Alliance's platform to prevent it from becoming Balanced. This could potentially be a violation of SG3 ("Platforms are 'safe' during the endgame."), but seems to be open to interpretation and requiring an official ruling. <br><img class="responsive-img" width="400" src="/assets/pics/game_analysis/mobile-goal-under-platform.png">
- Bump into opposing Robots holding Neutral Mobile Goals with Rings to try to knock them off. It also might be possible to directly take Rings off of the Branches with a dedicated mechanism.

###### Autonomous Win Point
During Change Up, the Autonomous Win Point was very important (because of AWPs, we ranked first in Illinois State Qualifiers despite not having the best record). This year, we expect the same to be true, so <mark>we should try to earn the AWP every Match</mark>. 

> ###### Conclusion
- Points scored on Neutral Mobile Goals can change Alliances. This means if our Alliance scores on a Neutral Mobile Goal, we should have a way to prevent the opposing Alliance from taking it. Conversely, it is a good idea to take Neutral Mobile Goals with Scored Rings from the opposing Alliance.
- The value of scoring objects change depending on the abilities of the opposing Alliance.
- If an Alliance wins the Autonomous Bonus, it is effectively worth 40 points.
- Moving a Mobile Goal from "Scored" to "Elevated" is only an increase of 20 points.
- When execution of a particular strategy fails, we need to shift our focus to having a higher average scoring pace than the opposing Alliance.
- Rings will be important, despite their relatively low point values.
- Neutral Mobile Goals are <strong>very</strong> important, especially the tall one. There will likely be a rush to get Neutral Mobile Goals during Autonomous.
- To be versatile enough to win every match, Robots are likely going to be able to hold and score on multiple Mobile Goals late season.
- Some matches will be decided by the Autonomous Bonus, especially when Neutral Mobile Goals are shared more evenly (which will likely happen most of the time).
- We should try to get the AWP as much as possible.

##### Robot Skills Strategy
###### Miscellaneous Observations
In Robot Skills, the effect of our actions on the opposing Alliance does not need to be considered, because there is no opposing Alliance. Instead, our average scoring pace is the most important. With this observation, we can realize that the tall Neutral Mobile Goal is possibly much less important in Robot Skills than in head-to-head Matches. Filling the top Branches with Rings yields 80 points, while elevating a full Alliance Mobile Goal yields 70, without the need to lift Rings high into the air. Furthermore, there are four available Alliance Mobile Goals opposed to the one tall Neutral Mobile Goal.

Also, the ability to lift Mobile Goals onto the Platform without driving onto it is going to be very useful, because we can use both Platforms, and all seven Mobile Goals cannot fit onto one platform. Additionally, lifting Mobile Goals onto the platform takes less time than driving each one up. 

To best maximize our average scoring pace, we should prioritize the elevation of Mobile Goals onto Platforms, because it takes far less time to lift a Mobile Goal onto the Platform than it takes to score 40 points worth of Rings on Mobile Goal Branches. We should only consider scoring Rings during Robot Skills if we can elevate all seven Mobile Goals, or it takes no additional time (i.e. we can do it on the way to elevating a Mobile Goal).
