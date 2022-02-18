#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "GraphicsEngineRenderer.hpp"

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class EditorSprite{
public:

    /*!
     * Constructor
     */
    EditorSprite();
    /*!
     * Constructor
     */
    ~EditorSprite();
    /*!
     * Initialize the sprite
     */
    void SetPosition(int x, int y);
    /*!
     * Update the sprites position and frame
     */
    void Update(int x, int y, int frame);
    /*!
     * Render the sprite 
     */
    void Render(SDL_Renderer* ren);
    /*!
     * Load a sprite
     */
    void LoadImage(std::string filePath,SDL_Renderer* ren);

private:
    /*!
     * The location of the spirte top left corner
     */
         int m_xPos;
         int m_yPos;
    /*!
     *What frame in the animation and what is the last possible frame
     */ 
         unsigned int m_currentFrame{0};
         unsigned int m_lastFrame{7};
    /*!
    * An SDL Surface contains pixel data to draw an image
    */
    SDL_Surface* m_spriteSheet;
    /*!
     * A SDL texture that is used for drawing images
     */
    SDL_Texture* m_texture;
    /*!
     * Rects the whole the slice location from the spirte map and its size plus location in world and its render size
     */
         SDL_Rect m_src;
         SDL_Rect m_dest;
};

#endif
