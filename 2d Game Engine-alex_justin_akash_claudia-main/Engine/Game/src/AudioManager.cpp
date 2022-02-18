#include "AudioManager.hpp"
#include "TileMap.hpp"
#include "Background.hpp"
#include "CollisionComponent.hpp"
#include "ControllerComponent.hpp"
#include "TransformComponent.hpp"
#include "Sprite.hpp"

AudioManager* AudioManager::instance = 0;

AudioManager* AudioManager::GetInstance() {
    if (!instance) {
        instance = new AudioManager;
    }

    return instance;
}

void AudioManager::Start() {
    Mix_Volume(1, MIX_MAX_VOLUME);

    backgroundMusic = Mix_LoadMUS("./assets/music.wav");
    if (backgroundMusic == nullptr) {
        printf("Failed to load background music!\n");
        SDL_Quit();
    }

    jumpSFX = Mix_LoadWAV("./assets/jump.wav");
    if (jumpSFX == nullptr) {
        printf("Failed to load jump sfx!\n");
        SDL_Quit();
    }

    Mix_PlayMusic(backgroundMusic, -1);
}

void AudioManager::Shutdown() {
    Mix_FreeMusic(backgroundMusic);
    backgroundMusic = nullptr;
}

void AudioManager::Play(int clip) {
    switch (clip) {
            case 1:
                // SDL_Log("Test");
                Mix_PlayChannel(1, jumpSFX, 0);
                break;
        }
}
