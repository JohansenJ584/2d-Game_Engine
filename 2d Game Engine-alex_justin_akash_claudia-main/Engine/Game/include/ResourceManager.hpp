#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include <sstream>

#include "GameObject.hpp"
#include "GameManager.hpp"

/*!
 Manages all the resources in the game.
 */
class ResourceManager {
    public:
        /*!
         Gets the instance of this resource manager (there can only be one).
         */
        static ResourceManager* GetInstance();

        /*!
        Starts the resource manager by creating all objects.
        */
        void Start(SDL_Renderer* m_renderer);

        /*!
        Shuts down the resource manager by freeing all objects.
        */
        void Shutdown();

        /*!
         Makes a save with the given save name.
         */
        void SaveState(const char* name);

        /*!
         Loads enemy information from a file.
         */
        void LoadEnemies(const char* filename);

        /*!
         Loads collectible information from a file.
         */
        void LoadCollectibles(const char* filename);

        /*!
         Adds a game object.
         */
        void AddGameObject(std::string name, GameObject* object);

        /*!
         Gets a game object.
         */
        GameObject* GetGameObject(std::string name);

        /*!
         Gets all game objects.
         */
        std::unordered_map<std::string, GameObject*> GetGameObjects();

        /*!
         Removes the specified game object.
         */
        void RemoveGameObject(std::string name);

        /*!
         Processes input for all game objects.
         */
        void Input(SDL_Event e);

    	/*!
    	 * Processes input for the game while it is paused.
    	 */
    	void PausedInput(SDL_Event e);

        /*!
         Updates all game objects.
         */
        void Update();

    	/*!
    	 * Updates the games information while paused.
    	 */
    	void PausedUpdate();

        /*!
        Renders all game objects.
        */
        void Render(SDL_Renderer* m_renderer);

        // Makes an enemy.
        GameObject* MakeEnemy(int x, int y, int range, int type);
        GameObject* MakeFruit(int xpos, int ypos, int width, int height, int type);
        /*
    	 * Choses whitch mode of placing is done in editing mode.
    	 */
        void ChangePlaceWhat(int to);

    	/*!
    	 *Allows for the gui to edit what brick is being edited.
    	 */
    	void changeBlock(int valueBlock);

        int currentTile = 0;

    	SDL_Renderer* the_renderer;

        ResourceManager() {};
    private:
        int show = 0;
        // The static instance of the resource manager.
        static ResourceManager* instance;

    	/*!
    	 * When the editor is on and deletes any fruit or enemy below it.
    	 */
        void DeleteFruitEnemy(int placeX, int placeY);

        // A private alternate constructor that cannot be used.
        ResourceManager(ResourceManager const&);

        // A private copy constructor that cannot be used.
        void operator=(ResourceManager const&);

        // A list of all game objects.
        std::unordered_map<std::string, GameObject*> gameObjects;

        //Makes an enemy
        //GameObject* MakeEnemy(int x, int y, int range, TileMap* tm, SDL_Renderer* renderer);
        //GameObject* MakeFruit(int xpos, int ypos, int width, int height, TileMap* tm, SDL_Renderer* renderer);

        GameManager* gMang = nullptr;

        // int currentTile;
        TileMap* theTileMap;

        // SDL_Renderer* the_renderer
        SDL_Texture* player_texture;
        std::vector<SDL_Texture*> enemy_textures;
        std::vector<SDL_Texture*> item_textures;
        SDL_Texture* tilemap_texture;
        SDL_Texture* background_texture;
};

/*
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(mygameengine, m){
    py::class_<ResourceManager>(m, "resourceManager")
	    .def("getInstance", &ResourceManager::GetInstance, py::return_value_policy::reference)
	    .def("addGameObject", &ResourceManager::AddGameObject)
	    .def("makeFruit", &ResourceManager::MakeFruit, py::return_value_policy::reference)
	    .def("makeEnemy", &ResourceManager::MakeEnemy, py::return_value_policy::reference);

// We do not need to expose everything to our users!
//            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference)
}
*/
#endif
