# Not Another Temple Run
## Description 
Not Another Temple Run is a 3D running game that consists of 2 different environments (modes) developed using Opengl C++ 

## Game Modes 
### Arcade Mode
The player is running in a turning lane (that should be followed) with a target to collect certain amount of coins to win 
- **Collectables** : Coins that appear randomly both in position and amount.
- **Obstacles** : Rocks that the player should avoid by leaning or jumping.

![image](https://user-images.githubusercontent.com/8184424/210840534-f47af3df-ad6f-4360-892b-d1925dd07c55.png)


### Survival Mode
The player is running endlessly with a target to live as much he/she can (no certain score to win)
- **Collectables** : Shields that appear randomly and give the player a period of protection from fire
- **Obstacles** : Fire that the player should avoid by leaning or jumping

![image](https://user-images.githubusercontent.com/8184424/210840803-2d1080b0-6efb-464b-b70a-6cdda160fad5.png)


## Video
https://user-images.githubusercontent.com/8184424/210841475-dcafe007-d27a-4ed2-bb3f-a9291c30d361.mp4


## Game Camera
The game consists of 2 modes of camera prespective (that always follows the player) 
### First Person Camera 
Camera eye is the head of the player and center is a point on the ground in front of the player 
### Third Person Camera
Camera eye is behind the player while camera center is the player itself

## Game Controls
### Mouse 
- `Left Click` &rarr; Player jump
- `Moving arrow Right` &rarr;Player lean right  
- `Moving arrow Left` &rarr;player lean left 
### Key board
- `Press D` &rarr; Player turn right (to folow the ground)
- `Press A` &rarr; Player turn left (to follow the ground)
- `Press space` &rarr; Player jumping
- `Press Right arrow ` &rarr;Player leaning right
- `Press Left arrow` &rarr; Player leaning left


## Win/Lose Actions
### Arcade Mode
- **Win Action** : Collect 35 coin 
- **Lose Action** : Collide with rock or falling off the ground (not following its turning)
### Survival Mode
- **Win Action** : No win Action 
- **Lose Action** : Collide with fire or falling off the ground (not following its turning)

## Sound effects 
There is a sound effect generated for different actions in the game 
- Colliding with the rock in Arcade mode
- Colliding with Fire in Survival mode
- Collecting Coin in Arcade Mode
- Obtaining Sheild in Survival Mode
- Falling off the ground in both Arcade and Survival Modes

## Lights
Lights is modelled as one light source that changes its intensity and position to simulate day/night cycle

## Challenges 
Develop a dynamic way to generate the turning ground of the game.

**How we solved it** 
- Store the direction of each ground (NEGATIVE_X , NEGATIVE_Z , POSITIVE_X, POSITIVE_Z) beside its center.
- Develop 3 methods `drawLeft` , `drawRight` , and `drawForward`  that takes the current ground object and return the new ground (its center and direction).

## Future Enhancements
- Use the dynamic way of generating ground to generate the ground dynamically at runtime.
- Add magnet feature in Arcade Mode.

## Authors 
-   [Elshimaa Betah](https://github.com/ShimaaBetah)
-   [Ahmed Elwasefi](https://github.com/Ahmad45123)
-   [Abdulaziz Hassan](https://github.com/Abdulaziz-Hassan)
-   [Mohamed Almarsafy](https://github.com/mokhallid80)
