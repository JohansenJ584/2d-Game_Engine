#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

#include "GraphicsEngineRenderer.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"

/*!
 Stores the sprite for a game object, acts as a component.
 */
class Sprite : public Component {
    public:
        /*!
         Constructor
         Texture is the texture to be rendered.
         Transform is a reference to the transform of the GameObject this Component belongs to.
         img_w and img_h are the width and height of the sprite.
         */
        Sprite(SDL_Texture* texture, TransformComponent* transform, int img_w, int img_h);

        /*!
        Destructor.
        */
        ~Sprite();

        /*!
         Update the sprite to the next frame.
         */
        virtual void Update();

        /*!
         Renders the sprite.
         */
        virtual void Render(SDL_Renderer* ren);

    private:
        // Points to the transform of the game object this component is attached to.
        TransformComponent* transform;

        // The current frame of this sprite.
        unsigned int m_currentFrame;

        // Points to the texture of the spritesheet.
        SDL_Texture* m_texture;

        // Source and destination rectangles for rendering.
        SDL_Rect m_src, m_dest;
};

#endif
