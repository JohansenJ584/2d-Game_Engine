#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "GameObject.hpp"
#include "AIControllerComponent.hpp"
#include "CollectibleComponent.hpp"
#include "TransformComponent.hpp"

// Manages all the resources in the game.
class GameManager {
	public:
		/*!
		 * Is actually the constructor for Game Manager
		 * player: The playable character's GameObject
		 * tilemap: The Tilemap Component for the world
		 * fruits: A vector list of all the Fruits' GameObjects
		 * Ai: A vector of all the enemies in the world
		 * m_renderer: The game renderers
		 */
		void Start(GameObject* player, TileMap* tileMap, std::vector<GameObject*> Fruits, std::vector<GameObject*> Ai, SDL_Renderer* m_renderer);
		void Start(GameObject* player, TileMap* tileMap, SDL_Renderer* m_renderer);
		/*!
		 * Checks to see if there is collisions bewteen player and fruits and player and Ai.
		 * Also increaments score based off collisions with fruits and removes wall segments based of score.
		 */
		void Update();

		/*!
		 * Renders the text for the score.
		 */
		void Render();

		/*!
		 * Makes sure that ttf is correctly removed.
		 */
		void Stop();

		/*!
			Saves the types and positions of all collectibles in the level to a file.
		*/
		void SaveCollectibles(const char* filename);

		/*!
			Saves the types and positions of all enemies in the level to a file.
		*/
		void SaveEnemies(const char* filename);

		/*!
			Adds Enemy to GameManager.
		*/
		void AddEnemy(GameObject* enemy);

		/*!
			Gets the number of collectibles in the scene.
		*/

		int NumCollectibles();

		/*!
			Gets the number of enemies in the scene.
		*/
		int NumEnemies();

		/*!
			Adds collectible to GameManager.
		*/
		void AddCollectible(GameObject* collectible);

		/*!
		 * Vector of all the Fruits' GameObjects in the level.
		 */
		std::vector<GameObject*> Fruits;

		/*!
		 * Vector of all the AIs in the current level.
		 */
		std::vector<GameObject*> Ai;

		/*!
		 * Constructor.
		 */
		GameManager(){};

		/*!
		 * Destructor.
		 */
	    ~GameManager(){};

		// Determines whether the player has won.
        bool win;

	private:
		/*!
		 * Amount of fruit collected.
		 */
		int Score;

		/*!
		 * Playible character GameObject.
		 */
		GameObject* player;

		/*!
		 * TileMap Component that contains the array that is used to display world.
		 */
		TileMap* tileMap;

		/*!
		 * Vector of all the Fruits' GameObjects in the level.
		 */
		// std::vector<GameObject*> Fruits;

		/*!
		 * Vector of all the AIs in the current level.
		 */
		// std::vector<GameObject*> Ai;

		/*!
		 *The render for displaying text in the world.
		 */
		SDL_Renderer* m_renderer;

		/*!
		 *The render surface.
		 */
		SDL_Surface* surface{};

		/*!
		 *The render texture.
		 */
		SDL_Texture* texture{};

		/*!
		 *The render rect.
		 */
		SDL_Rect rect{};

		/*!
		 * The font loaded for displaying the score and victory.
		 */
		TTF_Font* scoreFont;
};

#endif
