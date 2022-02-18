#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "GraphicsEngineRenderer.hpp"

GraphicsEngineRenderer::GraphicsEngineRenderer(int w, int h) : m_screenWidth(w), m_screenHeight(h) {
    // Initialize random number generation
   	srand(time(nullptr));

    // Initialization flag
    bool success = true;

    // String to hold any errors that occur
    std::stringstream errorStream;

    // The window we'll be rendering to
    m_window = nullptr;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
    else {
		// Create window
		m_window = SDL_CreateWindow("Platformer Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN);

		// Check if window was not created
		if (m_window == nullptr) {
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Create a renderer to draw on
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

		// Check if renderer was not created
		if (m_renderer == nullptr) {
			errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
	}

    // If initialization did not work, then print out a list of errors in the constructor
    if (!success) {
    	errorStream << "Failed to initialize graphics engine!\n";
    	std::string errors = errorStream.str();
    	std::cout << errors << "\n";
    }
    else {
    	// std::cout << "No SDL errors detected during initialization\n\n";
    }
}

GraphicsEngineRenderer::~GraphicsEngineRenderer() {
    // Destroy renderer
    SDL_DestroyRenderer(m_renderer);

    // Destroy window
    SDL_DestroyWindow( m_window );

    // Point them to nullptr to ensure they are not deleted again
    m_renderer = nullptr;
    m_window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void GraphicsEngineRenderer::SetRenderDrawColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void GraphicsEngineRenderer::RenderClear() {
    SDL_RenderClear(m_renderer);
}

void GraphicsEngineRenderer::RenderPresent() {
    SDL_RenderPresent(m_renderer);
}

// Get pointer to window
SDL_Window* GraphicsEngineRenderer::GetWindow() {
    return m_window;
}

// Get pointer to renderer
SDL_Renderer* GraphicsEngineRenderer::GetRenderer() {
    return m_renderer;
}
