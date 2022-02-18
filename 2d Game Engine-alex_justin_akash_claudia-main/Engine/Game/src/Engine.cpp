#include "Engine.hpp"

// Initialization function
// Returns a true or false value based on successful completion of setup
// Takes in dimensions of window
Engine::Engine() {}

// Proper shutdown and destroy initialized objects
Engine::~Engine() {}

bool isPaused = false;
bool doQuit = false;

bool Engine::getDoQuit() {
	return doQuit;
}

// Return input
void Engine::Input(bool* quit) {
    // Event handler that handles various events in SDL that are related to input and output
    SDL_Event e;

    // Enable text input
    SDL_StartTextInput();
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        // User posts an event to quit
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            doQuit = true;
        }
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F5) {
            resourceManager->SaveState("saves/level_save");
        }
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p) {
			// resourceManager->PausedInput(e);
	        if (e.key.keysym.sym == SDLK_p && isPaused) {
				isPaused = false;
		    }
		    else if (!isPaused) {
				isPaused = true;
	        }
		}
		else if (!isPaused) {
	        resourceManager->Input(e);
	    }

		if (isPaused) {
			resourceManager->PausedInput(e);
		}
    }

    if (!isPaused && SDL_GetTicks() % 6 == 0) {
        resourceManager->Input(e);
    }
}

// Update SDL
void Engine::Update() {
	if (!isPaused) {
		resourceManager->Update();
	}
	else {
		resourceManager->PausedUpdate();
	}
}

// The render function gets called once per loop
void Engine::Render() {
    // Set the color of the empty framebuffer
    m_renderer->SetRenderDrawColor(0, 0, 0, 0xFF);

    // Clear the screen to the color of the empty framebuffer
    m_renderer->RenderClear();

    // Render each GameObject
    resourceManager->Render(m_renderer->GetRenderer());

    // Flip the buffer to render
    m_renderer->RenderPresent();
}

// Loops forever!
void Engine::MainGameLoop() {
    // Main loop flag
    bool quit = false;

    int countedFrames = 0;
    uint32_t frameStart;

    // While application is running
    while (!quit) {
        frameStart = SDL_GetTicks();

        // Get user input
        // IMPORTANT: Input must run before Update in order for collisions and physics to work correctly.
        // Doing it in the reverse order could result in the player getting stuck to surfaces.
        Input(&quit);

        // Update our scene
	    if (!isPaused) {
        	Update();
	    }
	    else {
		    resourceManager->PausedUpdate();
	    }

        // Render using OpenGL
        Render();

        // Frame capping
        float avgFPS = countedFrames / (SDL_GetTicks() / 1000.f);
        if (avgFPS > 2000000) {
            avgFPS = 0;
        }
        SDL_Log("FPS: %f", avgFPS);
        ++countedFrames;
        int frameTicks = SDL_GetTicks() - frameStart;
        if (frameTicks < frameDelay) {
            SDL_Delay(frameDelay - frameTicks);
        }
    }
    // Disable text input
    // SDL_StopTextInput();
}

void Engine::Start() {
    // Report which subsystems are being initialized
    if (m_renderer != nullptr) {
        // std::cout << "Initializing graphics subsystem\n";
    }
    else {
        std::cout << "No graphics subsystem initialized\n";
    }

    resourceManager = ResourceManager::GetInstance();
    audioManager = AudioManager::GetInstance();

    resourceManager->Start(m_renderer->GetRenderer());
    audioManager->Start();
}

void Engine::Shutdown() {
    // Shut down our tile systems
    if (m_renderer != nullptr) {
        delete m_renderer;
    }

    resourceManager->Shutdown();
    audioManager->Shutdown();
    // Disable text input
    SDL_StopTextInput();
}

void Engine::InitializeGraphicsSubSystem() {
    // Setup our renderer
    m_renderer = new GraphicsEngineRenderer(1280, 720);
    if (m_renderer == nullptr) {
        // Exit if the renderer was not set up properly
        exit(1);
    }
}
