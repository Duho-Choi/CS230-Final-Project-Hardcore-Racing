# Final Project Developer
Duho Choi \
Minsu Kim

# Compilation Instruction
1. Double click `CS230_DuhoChoi.sln`.
2. Check `Solution configuration - Release` and `Solution platforms - x64`!
3. Click `Local Windows Debugger` or press `F5` to execute program!  

# License
Please Check `Assets\Mode3` folder! \
Every assets are CC0.

# Game Concept
+ Concept : police and thieves

+ Win / Lose
> Win : Reach to the goal point.
> Lose : Lose all HP.

> Police chase the player and also track has some spike.
> If player collide with that, player lose their HP.

+ Moving
> Player has their own moving (Actually, just rotate when moving left and right)
> Police moves like Mode2 

+ Collision
> AABB Collision check with spike, police, player, goal point.

+ particle
> Player rut

+ AI
> Police check player position and move that rotation.

+ Animation
> Explode when police collide with each other, or player lose all their HP.

+ Score
> Encourage the police to bump into each other, and score points when they bump into each other.
