# not-another-temple-run
## Description 
Not Another Temple Run is a 3rd running game that consists of 2 different environments (modes) developed using Opengl C++ 

## Game Modes 
### Arcade Mode
The player is running in a turning lane (that should be folllwed) with a target to collect certain amount of coins to win 
- **Collectables** : Coins that appeared randomly both in position and amount 
- **Obstacles** : Rocks that the player should avoid by leaning or jumping
### Survival Mode
The player is running endlessly with a target to live as much he/she can (no certain score to win)
- **Collectables** : Sheilds that appear rendomly and give the player a period of protection from fire
- **Obstacles** : Fire that the player should avoid by leaning or jumping

## Game Camera
The game consists of 2 modes of camera prespective (that always follows the player) 
### First Person Camera 
camera eye is the head of the player and center is a point on the ground in front of the player 
### Third Person Camera
camera eye is behind the player while camera center is the player itself

## Game Controls
### Mouse 
- `Left Click` &rarr; player jump
- `Moving arrow Right` &rarr;player leaning Right  
- `Moving arrow Left` &rarr;player leaning Left 
### Key board
- `Press D` &rarr; player turning right (to folow the ground)
- `Press A` &rarr; player turning left (to follow the ground)
- `Press space` &rarr; player jumping
- `Press Right arrow ` &rarr;player leaning right
- `Press Left arrow` &rarr; player leaning left


## Win/Lose Actions
### Arcade Mode
- **Win Action** : Collect 35 coin 
- **Lose Action** : collide with rock or falling off the ground (not following its turning)
### Survival Mode
- **Win Action** : No win Action 
- **Lose Action** : collide with fire or falling off the ground (not following its turning)

## Sound effects 
there is a sound effect generated for different actions in the game 
- Colliding with the rock in Arcade mode
- Colliding with Fire in Survival mode
- Collecting Coin in Arcade Mode
- Obtaining Sheild in Survival Mode
- Falling off the ground in both Arcade and Survival Modes

## Lights
Lights is modelled as one light source that changes its intensity and position to simulate day/night cycle

## Challenges 
- develop a dynamic way to generate the turning ground of the game 

**How we solved it** 
- store the direction of each ground (NEGATIVE_X , NEGATIVE_Z , POSITIVE_X, POSITIVE_Z) beside its center
- develop 3 methods `drawLeft` , `drawRight` , and `drawForward`  that takes the current ground object and return the new ground (its center and direction)

## Future Enhancements
- use the dynamic way of generating ground to generate the ground dynamically at runtime
- Add Magnet feature in Arcade Mode

## Authors 

