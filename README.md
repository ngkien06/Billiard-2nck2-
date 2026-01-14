# Billiard -2nck2-

## Introduction?

This is a personal project of Nguyen Cong Kien. This will probably only last until the end of 2026.
The point of this project is just to make sure I have an fundamental base for development if I ever decide to work.

## Plans

My initial list of feature that I currently have plan for:
- Implement different type/variation of billard such as 8-ball, 9-ball, maybe even some carom.
- A training area, where player can set the ball
- Replay system
- Clock / Timer
- Bots for difference variation
- 3D?

## Logs

This will serve as a personal log book, any meaningful update to the project will be stated here.

* 8/1/2026: The cue ball can now be shoot and have actual collision with the rail. So this now resemble something that actually not useless/meaningless. 

So one thing I learn about collision system, there 2 thing to remember when working a collision: 
**make sure the 2 objects are seperated from eachother** (i.e. no overlapping) and
**let the object reponse** (not the system set everything)

* 12/1/2026: There is now drag and energy loss (when hit the rail), so now the ball not roll forever. 

## Backlog

This will serve as a list of small tasks, so I can just choose one if I want to.

- Ball collision
- Impact highlight
- Direction indicator
- Ghost ball 
- Cue ball placing
- Tracer
- Change Rail struct, so the side have 2 part
- Triangle (for rail)
- Triangle collision
- Pocket graphic
- Pocket collision
- Constructor for Rail/Pocket based on Table dimension (rec)
- Change the collision to Visitor pattern
- Make that ball dimension come from the table, not screen