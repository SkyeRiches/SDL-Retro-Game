# Retro Game Recreation
This project was created as part of a university assignment. The aim of the assignment was to use a combination of external libraries with C++, to develop a 2d retro game engine that would then be used to create a 2d retro game. For this project I used the 2d engine to create the classic arcade game; PacMan.

To Play the game, open the exe file within the 'Release' folder.

# Functionality
Upon loading the game, a splashscreen will play and then the menu will load. The menu is navigated by pressing the number key relating to the option on the menu. 

Gameplay: 
The gameplay is very much like the classic arcade game, except its controlled with 'wasd' rather than arcade controls. The pacman character can be moved round the maze picking up the pellets. A tilebased collision system is implemented using rudimentary methods of having an array of which tiles are colliders.
There are also the ghosts moving around different parts of the maze, and colliding with them will cause you to lose a life. However, like the classic game, you can collect power pellets to turn on the ghosts and be able to eat them instead.
At the end of the game (be it through success or failure), your score is saved to the leaderboard.

# Video
https://www.youtube.com/watch?v=oAaZ2XBBSu8

# Possible Improvements
- I could change the ghost ai to actually chase the player rather than just staying on their path
- I could add difficulty levels so each time you complete a maze it gets harder
- I could create menus that are navigatable by mouse

# External Libraries Used

SDL: https://www.libsdl.org/
