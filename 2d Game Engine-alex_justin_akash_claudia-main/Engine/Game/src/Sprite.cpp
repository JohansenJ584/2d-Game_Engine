#include "Sprite.hpp"

Sprite::Sprite(SDL_Texture* texture, TransformComponent* transform, int img_w, int img_h) {
    this->transform = transform;
    m_texture = texture;
    m_src.w = img_w;
    m_src.h = img_h;
    // printf("Sprite Transform Address %p\n", (void*)transform);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(m_texture);
}

void Sprite::Update() {
    // The part of the image that we want to render
    m_currentFrame++;
    if (m_currentFrame > 11) {
        // THIS IS HARD CODED CHANGED it when need
        // SDL_Log("THIS IS WHAT FRAME %d", m_currentFrame);
        m_currentFrame = 0;
    }

    // Selecting the frame to be drawn from the spritesheet
    m_src.x = m_currentFrame * m_src.w;
    m_src.y = 0;

    // Where we want the rectangle to be rendered at
    std::pair<int, int> pos = transform->GetPosition();
    m_dest = {pos.first, pos.second, 32, 32};
}

void Sprite::Render(SDL_Renderer* ren) {
    std::pair<int, int> curVel = transform->GetVelocity();
    if (curVel.first >= 0) {
        // Character is moving right
        SDL_RenderCopy(ren, m_texture, &m_src, &m_dest);
    }
    else {
        // Character is moving left, flip render
        SDL_RenderCopyEx(ren, m_texture, &m_src, &m_dest, 0, 0, SDL_FLIP_HORIZONTAL);
    }
}
