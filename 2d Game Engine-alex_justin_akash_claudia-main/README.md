<img align="right" width="300px" src="./media/header.png">

## 2d Game Engine

This is a 2d tile platformer game engine that was created with SDL2, pybind11, pygame.
SDL2 is used to handle graphics, input and other low level mangment
pybind11 incapulates C++ and allows the methods to be called within python scripts.
Becuase of this the game can be scripted though python allowing for better implementationds and faster prototyping.
One of the majyoe functiality of this language besides the abilty to script is it allows for run-time editing of the game world.
The user can pause the game at anytime and add or delete tiles, collectibles, or eniemies.
The player can jump, collect fruits to open doors, dodge enmies and completly levels.


We used pygame, SDL2, and pybind11 within our project, so it may need to be installed prior to building.
To build project run 
  python3 \Engine\Game\linuxbuild.py
Our project is only built to run on Linux.
To run project entire comand
python3 test.py


Doxygen Webpage
https://cjodlowski.github.io/CS4850FinalProjectWebsite/