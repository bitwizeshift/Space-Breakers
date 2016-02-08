# Space-Breakers
## Details
This is a small Space-Invaders-meets-Brick Break game I created for fun. It's written in C++11 using SDL2 for rendering and graphics. 
The object of the game is simple; survive while destroying the invaders. The invaders will shoot projectiles, and it is your job to 
attempt to deflect them by bouncing them off the paddle and back at them. You gain points for properly deflecting attacks and destroying
invaders. 

You begin with 10 health, and slowly lose it each time you miss a projectile. At the end of each level, you earn back 2 times the level 
difficulty life back in preparation for the next level (i.e. if you pass level 1 you get 2 health, if you pass level 2 you get 4 health, 
etc). Points are also multiplied by the level

## Controls

```
[Left]/[A]  : Move paddle left
[Right]/[D] : Move paddle right
[ESC]       : Pause/Unpause
[Shift]     : Hold to move paddle faster
```

## Compilation
This program requires SDL2 to compile. Ir requires `-lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer` as linker flags, and the appropriate
libs and shared libraries for your system.

I will be providing a CMakeList file for this shortly
