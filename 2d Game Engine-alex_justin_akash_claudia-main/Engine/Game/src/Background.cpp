#include "Background.hpp"

Background::Background(SDL_Texture* texture) {
    m_texture = texture;
}

Background::~Background() {
    SDL_DestroyTexture(m_texture);
}

void Background::Update() {
    ticks++;
    if (ticks > 3) { // This is the scrolling speed of the background
        ticks = 0;
        offset++;
    }
}

void Background::Render(SDL_Renderer* renderer) {
    if (offset > 720) {
        offset = 0;
    }

    SDL_Rect dst1 = {0, offset, 1280, 720};
    SDL_Rect dst2 = {0, offset - 720, 1280, 720};

    SDL_RenderCopy(renderer, m_texture, nullptr, &dst1);
    SDL_RenderCopy(renderer, m_texture, nullptr, &dst2);
}
