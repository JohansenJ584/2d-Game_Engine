#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SDL2/SDL.h>
#include <string>

#include "Component.hpp"
#include "TransformComponent.hpp"

/*!
The background for the game, acts as a component.
*/
class Background : public Component {
    public:
        /*!
         Constructor. Texture is the background texture.
         */
        Background(SDL_Texture* texture);

        /*!
        Destructor.
        */
        ~Background();

        /*!
         Does nothing.
         */
        virtual void Update();

        /*!
            Renders the background.
        */
        virtual void Render(SDL_Renderer* renderer);

    private:
        // Points to the texture of the background.
        SDL_Texture* m_texture;

        // Source and destination rectangles for rendering.
        SDL_Rect src, dest;

        // Offset tick interval.
        int ticks = 0;

        // Scrolling offset.
        int offset = 0;
};

#endif
