#ifndef GRAPHICS_ENGINE_RENDERER_HPP
#define GRAPHICS_ENGINE_RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// The game's graphics engine and renderer.
class GraphicsEngineRenderer {
    public:
    	/*!
         * Constructor given the w and h for the renderer.
    	 */
        GraphicsEngineRenderer(int w, int h);

    	/*!
    	 * Destructor.
    	 */
        ~GraphicsEngineRenderer();

    	/*!
        * Sets the background color whenever the screen is cleared.
    	* Given r g b for light hue and a for alpha level.
    	*/
        void SetRenderDrawColor(int r, int g, int b, int a);

    	/*!
        * Clears the screen.
    	*/
        void RenderClear();

        /*!
        * Renders the backbuffer to the screen.
	    */
        void RenderPresent();

	    /*!
        * Gets a pointer to the window.
        */
        SDL_Window* GetWindow();

        /*!
        * Gets a pointer to the renderer.
	    */
        SDL_Renderer* GetRenderer();

    private:
    	/*!
        * The dimensions of the screen.
    	*/
    	int m_screenHeight, m_screenWidth;

    	/*!
        * Points to the window.
    	*/
        SDL_Window* m_window;

    	/*!
        * Points to the renderer.
    	*/
        SDL_Renderer* m_renderer = nullptr;
};

#endif
