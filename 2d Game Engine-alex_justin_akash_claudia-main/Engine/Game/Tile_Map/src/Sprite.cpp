#include "Sprite.hpp"

EditorSprite::EditorSprite(){
}

EditorSprite::~EditorSprite(){
// TODO: Make sure spritesheet and m_texture are destroyed
// but is this the right place?
    SDL_FreeSurface(m_spriteSheet);
    m_spriteSheet = nullptr;
    SDL_DestroyTexture(m_texture);
}

// Set the sprite position
void EditorSprite::SetPosition(int x, int y){
    m_xPos = x;
    m_yPos = y;
}

void EditorSprite::Update(int x, int y, int frame){
    // The part of the image that we want to render
    m_currentFrame = frame;
    if(m_currentFrame>6){
        m_currentFrame=0;
    }

    // Here I am selecting which frame I want to draw
    // from our sprite sheet. Think of this as just
    // using a mouse to draw a rectangle around the
    // sprite that we want to draw.
    m_src.x = 0;//m_currentFrame*75;
    m_src.y = 0;
    m_src.w = 32;
    m_src.h = 32;

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.	
    m_dest.x = m_xPos;
    m_dest.y = m_yPos;
    m_dest.w = 32;
    m_dest.h = 32;
}

void EditorSprite::Render(SDL_Renderer* ren){
    SDL_RenderCopy(ren, m_texture, &m_src, &m_dest);
}


void EditorSprite::LoadImage(std::string filePath, SDL_Renderer* ren){
    m_spriteSheet = SDL_LoadBMP(filePath.c_str());
    if(nullptr == m_spriteSheet){
           SDL_Log("Failed to allocate surface");
    }else{
        SDL_Log("Allocated a bunch of memory to create identical game character");
        // Create a texture from our surface
        // Textures run faster and take advantage 
        // of hardware acceleration
        m_texture = SDL_CreateTextureFromSurface(ren, m_spriteSheet);
    }
}
