#ifndef SDL_GRAPHICS_PROGRAM_HPP
#define SDL_GRAPHICS_PROGRAM_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "GraphicsEngineRenderer.hpp"
#include "ResourceManager.hpp"
#include "AudioManager.hpp"
#include "GameObject.hpp"

/*!
 The main game engine.
 */
class Engine {
    public:
        /*!
         Constructor.
         */
        Engine();

        /*!
         Destructor.
         */
        ~Engine();

        /*!
        Checks for user input.
        Quit is whether or not the game has received a quit command.
        */
        void Input(bool *quit);

        /*!
        Updates each game object in the game.
        */
        void Update();

        /*!
         Renders each game object in the game.
         */

        void Render();

        /*!
         The main game loop that runs until a quit operation occurs.
         */
        void MainGameLoop();

        /*!
         Starts and initializes variables in the game engine.
         */
        void Start();

        /*!
         Shuts down the game engine.
         */
        void Shutdown();

	/*!
	 *sees if we need to quit the game.
	 */
	bool getDoQuit();

        /*!
         Initializes the graphics subsystems.
         */
    	void InitializeGraphicsSubSystem();

    private:
        // The target frame delay based on a specified FPS.
        const int frameDelay = 1000 / 60;

        // Points to the renderer once it has been set up.
        GraphicsEngineRenderer* m_renderer = nullptr;

        // Points to the resource manager.
        ResourceManager* resourceManager;

        // Points to the audio manager.
        AudioManager* audioManager;
};


#endif
