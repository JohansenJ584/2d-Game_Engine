#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "GraphicsEngineRenderer.hpp"

/**
 * This class sets up the main game engine
 */
class EditorEngine{
public:
    /*!
     * Constructor of Engine
     */
    EditorEngine();
    /*!
     * Destructor
     */
    ~EditorEngine();
    /*!
     * Input engine
     */
    void Input(bool *quit);
    /*!
     * Per frame update
     */
    void Update();
    /*!
     * Per frame render. Renders everything
     */
    void Render();
    /*!
     * Main Game Loop that runs forever
     */
    void MainGameLoop();
    /*!
     * Initialization and shutdown pattern
     * Explicitly call 'Start' to launch the engine
     */
    void Start(std::string str1);
    /*!
     * Initialization and shutdown pattern
     * Explicitly call 'Shutdown' to terminate the engine
     */
    void Shutdown();
    /*!
     * Request to startup the Graphics Subsystem
     */
	void InitializeGraphicsSubSystem();


private:
     /*!
     * Engine Subsystem
     * Setup the Graphics Rendering Engine
     */
    EditorGraphicsEngineRenderer* m_renderer = nullptr;
};

#endif
