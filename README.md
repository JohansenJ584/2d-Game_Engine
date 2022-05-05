## 2d Game Engine

This 2D engine supports player movement, enemy movement and collisions, collectibles, and level completion but also a runtime editor. The example game created within the engine is a single player, platformer.  This project was created within a Linux environment and is run from the command line. The engine uses Simple Direct Media Layer (SDL2) to utilize computer input and output of audio and graphics. The engine uses pybind11 to map C++ code to be executable with Python. It also multithreading to uses Pygame to host the external GUI level editor tool at the same time.

This engine has
Component based architecture of the program. Which allows for easer creation of new assets within the world by combing repetitive parts of a new object.
Mechanics
* Manages input for player movement using SDL2.
* Enemies patrol and and can kill the player.
* Collectibles allow for walls to be removed to gain accesses to new parts of the levels.
* Level Completion zones.

Editor
* Pausing of game world which allows for in-game editing of the level which allows for easer testability and buildability.
* Multithreaded program allows for editor window to run simultaneously with the application but also for the transfer of information between the applications threads.
* GUI Selection window that allows for switching of objects for level editing
* When level is paused use arrow keys for precise placement of game objects <br/>
 

We used pygame, SDL2, and pybind11 within our project, so it may need to be installed prior to building. <br/>
To build project run <br/>
  python3 \Engine\Game\linuxbuild.py <br/>
Our project is only built to run on Linux. <br/>
To run project entire comand <br/>
python3 test.py <br/>


Doxygen Webpage
https://cjodlowski.github.io/CS4850FinalProjectWebsite/
