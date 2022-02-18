#ifndef SPRITE_EDITOR_HPP
#define SPRITE_EDITOR_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

/*!
    Represents the main structure of the Sprite Editor.
    Shows the animation of a chracter capped at 30FPS.
*/
class SpriteEditor {
    public:
        /*!
            Constructor for the Sprite Editor. 
            Filepath is the filepath for the Sprite bitmap.
            Width and Height are the size of the sprite.
            Start is the starting frame of the animation.
            End is the ending frame of the animation.
        */
        SpriteEditor(char* filepath, int width, int height, int start, int end);

        /*!
            Destructor.
        */
        ~SpriteEditor();

        /*!
            Initializes the Window and Renderer and Spritesheet.
        */
        void Init();
        
        /*!
            Contains the Main Loop for the Editor.
        */
        void Run();

        /*!
            Updates the editor to the next frame.
        */
        void Update();

        /*!
            Renders the current frame of the animation.
        */
        void Render();

        /*!
            Creates the texture of the spritesheet.
        */
        void LoadSpriteSheet();

    private:

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        SDL_Rect src;
        SDL_Rect dest;

        int x_pos;
        int y_pos;

        int current_frame;

        int num_cols; //number of sprites per row
        int num_rows; //number of rows in spritesheet

        SDL_Surface* m_surface;
        SDL_Texture* m_texture;

        
        char * m_filepath;

        int s_width;
        int s_height;

        int starting_frame;
        int ending_frame;
};

#endif