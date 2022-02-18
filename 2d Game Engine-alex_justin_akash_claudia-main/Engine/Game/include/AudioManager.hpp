#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/*!
 Manages the audio of the game.
 */
class AudioManager {
    public:
        /*!
         Gets the instance of this audio manager (there can only be one).
         */
        static AudioManager* GetInstance();

        /*!
        Starts the audio manager.
        */
        void Start();

        /*!
         Shuts down the audio manager.
         */
        void Shutdown();

        /*!
         Processes input for the audio.
         */
        void Play(int clip);

    private:
        // The static instance of the audio manager.
        static AudioManager* instance;

        // A private constructor.
        AudioManager() {};

        // A private alternate constructor that cannot be used.
        AudioManager(AudioManager const&);

        // A private copy constructor that cannot be used.
        void operator=(AudioManager const&);

        // Points to the background music for the game.
        Mix_Music* backgroundMusic;

        // Points to the jump sound effect for the player.
        Mix_Chunk* jumpSFX;
};

#endif
