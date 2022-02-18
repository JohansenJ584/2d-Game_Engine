#include "ResourceManager.hpp"
#include "TileMap.hpp"
#include "Background.hpp"
#include "CollisionComponent.hpp"
#include "ControllerComponent.hpp"
#include "TransformComponent.hpp"
#include "AIControllerComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Sprite.hpp"
#include "CollectibleComponent.hpp"

int xRed = 0;
int yRed = 0;
int currentTile = 0;
int placeWhat = 0;

ResourceManager* ResourceManager::instance = 0;

ResourceManager* ResourceManager::GetInstance() {
    if (!instance) {
        instance = new ResourceManager;
    }

    return instance;
}

void ResourceManager::changeBlock(int valueBlock) {
	currentTile = valueBlock;
}

void ResourceManager::PausedUpdate() {}

void ResourceManager::ChangePlaceWhat(int to) {
	placeWhat = to;
}

void ResourceManager::PausedInput(SDL_Event e) {
	bool space = false;
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: yRed -= 32; break;
            case SDLK_DOWN: yRed += 32; break;
            case SDLK_LEFT: xRed -= 32; break;
            case SDLK_RIGHT: xRed += 32; break;
			case SDLK_SPACE: space = true; break;
        }

        if (space) {
            // Places tiles and removes them
			if (placeWhat == 0) {
				if (yRed < 0 && xRed < 0) {
					xRed = 0;
					yRed = 0;
					theTileMap->SetTile(0, 0, currentTile);
				}
				else if (yRed < 0) {
					yRed = 0;
					theTileMap->SetTile(xRed/32,0,currentTile);
				}
				else if (xRed < 0) {
					xRed = 0;
					theTileMap->SetTile(0,yRed/32,currentTile);
				}
				else {
					theTileMap->SetTile(xRed/32,yRed/32,currentTile);
				}
			}
            // Allows placing collectibles
			else if (placeWhat == 1) {
                if (yRed < 0 && xRed < 0) {
					xRed = 0;
					yRed = 0;
					GameObject* Fruit = MakeFruit(xRed, yRed, 32, 32, 0);
        			std::string fulltag = "Fruit" + std::to_string(gMang->NumCollectibles());
        			AddGameObject(fulltag, Fruit);
        			gMang->AddCollectible(Fruit);
				}
                else if (yRed < 0) {
                    yRed = 0;
					GameObject* Fruit= MakeFruit(xRed, yRed, 32, 32, 0);
        			std::string fulltag = "Fruit" + std::to_string(gMang->NumCollectibles());
        			AddGameObject(fulltag, Fruit);
        			gMang->AddCollectible(Fruit);
				}
                else if (xRed < 0) {
					xRed = 0;
					GameObject* Fruit= MakeFruit(xRed, yRed, 32, 32, 0);
        			std::string fulltag = "Fruit" + std::to_string(gMang->NumCollectibles());
        			AddGameObject(fulltag, Fruit);
        			gMang->AddCollectible(Fruit);

				}
                else {
                    GameObject* Fruit= MakeFruit(xRed, yRed, 32, 32, 0);
    				std::string fulltag = "Fruit" + std::to_string(gMang->NumCollectibles());
    				AddGameObject(fulltag, Fruit);
    				gMang->AddCollectible(Fruit);
				}
			}
             // Deletes collectibles
			else if (placeWhat == 2) {
                if(yRed < 0 && xRed < 0) {
					xRed = 0;
					yRed = 0;
					DeleteFruitEnemy(xRed, yRed);
				}
                else if (yRed < 0) {
					yRed = 0;
					DeleteFruitEnemy(xRed, yRed);
				}
                else if (xRed < 0) {
					xRed = 0;
					DeleteFruitEnemy(xRed, yRed);
				}
                else {
					DeleteFruitEnemy(xRed, yRed);
				}
            }
            // Place AI
            else if (placeWhat == 3) {
				if (yRed < 0 && xRed < 0) {
					xRed = 0;
					yRed = 0;
					GameObject* Enemy = MakeEnemy(xRed, yRed, 30, 0);
    				std::string fulltag = "Enemy" + std::to_string(gMang->NumEnemies());
    				AddGameObject(fulltag, Enemy);
    				gMang->AddEnemy(Enemy);
				}
                else if (yRed < 0) {
					yRed = 0;
					GameObject* Enemy = MakeEnemy(xRed, yRed, 30, 0);
    				std::string fulltag = "Enemy" + std::to_string(gMang->NumEnemies());
    				AddGameObject(fulltag, Enemy);
    				gMang->AddEnemy(Enemy);
				}
                else if (xRed < 0) {
					xRed = 0;
					GameObject* Enemy = MakeEnemy(xRed, yRed, 30, 0);
    				std::string fulltag = "Enemy" + std::to_string(gMang->NumEnemies());
    				AddGameObject(fulltag, Enemy);
    				gMang->AddEnemy(Enemy);
				}
                else {
					GameObject* Enemy = MakeEnemy(xRed, yRed, 30, 0);
    				std::string fulltag = "Enemy" + std::to_string(gMang->NumEnemies());
    				AddGameObject(fulltag, Enemy);
    				gMang->AddEnemy(Enemy);
				}
			}
             // Deletes AI
			else if (placeWhat == 4) {
                if (yRed < 0 && xRed < 0) {
					xRed = 0;
					yRed = 0;
					DeleteFruitEnemy(xRed, yRed);
				}
                else if (yRed < 0) {
					yRed = 0;
					DeleteFruitEnemy(xRed, yRed);
				}
                else if (xRed < 0) {
					xRed = 0;
					DeleteFruitEnemy(xRed, yRed);
				}
                else {
					DeleteFruitEnemy(xRed, yRed);
				}
			}
			space = false;
        }
    	SDL_Rect rectangle = {
			.x = xRed,
			.y = yRed,
			.w = 32,
			.h = 32
		};

		// myTileMap->setTileType()
		// characters[0].SetPosition(xRed, yRed);
		SDL_SetRenderDrawColor(the_renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(the_renderer, &rectangle);
		SDL_RenderPresent(the_renderer);
    }

    show = 30;
}

void ResourceManager::DeleteFruitEnemy(int placeX, int placeY) {
	// Place transform
	double pposx = placeX;
	double pposy = placeY - 32;
	int pwidth = 32;
	int pheight = 32;
	// Fruit transform
	std::pair<double, double> fpos;
	std::pair<int, int> fdim;
	double fposx;
	double fposy;
	int fwidth;
	int fheight;

    // Used to see if a collision happened with the fruit
    for (GameObject* fruit : gMang->Fruits) {
		TransformComponent* ftc = nullptr;
        for (std::vector<Component*>::iterator it = fruit->m_components.begin(); it != fruit->m_components.end(); ++it) {
            if (!ftc) {
               ftc = dynamic_cast<TransformComponent*>(*it);
            }
        }
		if (ftc) {
			fpos = ftc->GetPosition();
			fdim = ftc->GetDimensions();
			fposx = fpos.first;
			fposy = fpos.second;
			fwidth = fdim.first;
			fheight = fdim.second;
			if (pposy + pheight >= fposy && pposy <= fposy + fheight && pposx < fposx + fwidth && pposx + pwidth > fposx) {
				// printf("There was a collision bewteen fruit and player\n");
				fruit->m_components.clear();
			}
			ftc = nullptr;
		}
    }

	for (GameObject* ai : gMang->Ai) {
		TransformComponent* atc = nullptr;
        	for (std::vector<Component*>::iterator it = ai->m_components.begin(); it != ai->m_components.end(); ++it) {
        		if (!atc) {
        		   atc = dynamic_cast<TransformComponent*>(*it);
        		}
        	}
		if (atc) {
			fpos = atc->GetPosition();
			fdim = atc->GetDimensions();
			fposx = fpos.first;
			fposy = fpos.second;
			fwidth = fdim.first;
			fheight = fdim.second;
			if (pposy + pheight >= fposy && pposy <= fposy + fheight && pposx < fposx + fwidth && pposx + pwidth > fposx) {
				if (pposy + pheight  >= fposy && pposy + pheight  <= fposy + 5) {
					// printf("There was a collision bewteen AI and player\n");
					ai->m_components.clear();
				}
			}
			atc = nullptr;
		}
	}
}

GameObject* ResourceManager::MakeFruit(int xpos, int ypos, int width, int height, int type) {
    GameObject* fruit = new GameObject();
    TransformComponent* tc = new TransformComponent();
    tc->SetPosition(xpos, ypos);
    tc->SetWidth(width);
    tc->SetHeight(height);
    PhysicsComponent* pc = new PhysicsComponent(tc);
    Sprite* s = new Sprite(item_textures[type], tc, width, height);
    CollisionComponent* colc = new CollisionComponent(tc, theTileMap);
    CollectibleComponent* cc = new CollectibleComponent(type);
    fruit->AddComponent(tc);
    fruit->AddComponent(s);
    fruit->AddComponent(colc);
    fruit->AddComponent(pc);
    fruit->AddComponent(cc);
    return fruit;
}

void ResourceManager::SaveState(const char* name) {
    char buffer_tm[strlen(name) + strlen("_tilemap.txt") + 1];
    sprintf(buffer_tm, "%s_tilemap.txt", name);
    theTileMap->SaveMap(buffer_tm);

    char buffer_e[strlen(name) + strlen("_enemies.txt") + 1];
    sprintf(buffer_e, "%s_enemies.txt", name);
    gMang->SaveEnemies(buffer_e);

    char buffer_c[strlen(name) + strlen("_collectibles.txt") + 1];
    sprintf(buffer_c, "%s_collectibles.txt", name);
    gMang->SaveCollectibles(buffer_c);
}

void ResourceManager::Start(SDL_Renderer* m_renderer) {
    // Create vectors for GameManager
    std::vector<GameObject*> vecFruits = {};
    std::vector<GameObject*> vecAi = {};

    the_renderer = m_renderer;

    // Load textures
    // Background
    SDL_Surface* bg_surface = SDL_LoadBMP("./assets/background.bmp");
    if (bg_surface == nullptr) {
            SDL_Log("Failed to allocate background surface");
    }
    else {
        // Create a texture from our surface
        background_texture = SDL_CreateTextureFromSurface(m_renderer, bg_surface);
        SDL_FreeSurface(bg_surface);
    }

    // TileMap
    SDL_Surface* tm_surface = SDL_LoadBMP("./assets/spritesheet.bmp");
    if (tm_surface == nullptr) {
            SDL_Log("Failed to allocate tilemap surface");
    }
    else {
        // Create a texture from our surface
        tilemap_texture = SDL_CreateTextureFromSurface(m_renderer, tm_surface);
        SDL_FreeSurface(tm_surface);
    }

    // Player
    SDL_Surface* player_surface = SDL_LoadBMP("./assets/player.bmp");
    if (player_surface == nullptr) {
            SDL_Log("Failed to allocate player surface");
    }
    else {
        // Create a texture from our surface
        player_texture = SDL_CreateTextureFromSurface(m_renderer, player_surface);
        SDL_FreeSurface(player_surface);
    }

    // Enemies
    SDL_Surface* enemy_surface0 = SDL_LoadBMP("./assets/enemy.bmp");
    if (enemy_surface0 == nullptr) {
            SDL_Log("Failed to allocate enemy surface");
    }
    else {
        // Create a texture from our surface
        auto enemy_texture0 = SDL_CreateTextureFromSurface(m_renderer, enemy_surface0);
        enemy_textures.push_back(enemy_texture0);
        SDL_FreeSurface(enemy_surface0);
    }

    // Items
    SDL_Surface* item_surface0 = SDL_LoadBMP("./assets/item.bmp");
    if (item_surface0 == nullptr) {
            SDL_Log("Failed to allocate item surface");
    }
    else {
        // Create a texture from our surface
        auto item_texture0 = SDL_CreateTextureFromSurface(m_renderer, item_surface0);
        item_textures.push_back(item_texture0);
        SDL_FreeSurface(item_surface0);
    }

    // Make the background image
    GameObject* background = new GameObject();
    Background* bg = new Background(background_texture);
    background->AddComponent(bg);
    AddGameObject("Background", background);

    // Make the tilemap
    GameObject* tilemap = new GameObject();
    theTileMap = new TileMap(tilemap_texture, 3, 3, 32, 32, 40, 22);
    theTileMap->LoadMap("saves/level_save_tilemap.txt");
    theTileMap->PrintMap();
    tilemap->AddComponent(theTileMap);
    AddGameObject("TileMap", tilemap);

    // Make the player
    GameObject* player = new GameObject();
    TransformComponent* tc = new TransformComponent();
    tc->SetPosition(128, 508);
    tc->SetWidth(32);
    tc->SetHeight(32);
    PhysicsComponent* gc = new PhysicsComponent(tc);
    ControllerComponent* conc = new ControllerComponent(tc);
    Sprite* s = new Sprite(player_texture, tc, 32, 32);
    CollisionComponent* colc = new CollisionComponent(tc, theTileMap);
    player->AddComponent(tc);
    player->AddComponent(gc);
    player->AddComponent(conc);
    player->AddComponent(s);
    player->AddComponent(colc);
    AddGameObject("Player", player);

    /*
    //Make Enemies
    GameObject* enemy1 = MakeEnemy(304, 159, 55,0);
    AddGameObject("Enemy1", enemy1);
    vecAi.push_back(enemy1);
    GameObject* enemy2 = MakeEnemy(960, 543, 80,0);
    AddGameObject("Enemy2", enemy2);
    vecAi.push_back(enemy2);

    //Make Collectibles: 1
    GameObject* Fruit1 = MakeFruit(64, 100, 32, 32,0);
    AddGameObject("Fruits1", Fruit1);
    //2
    GameObject* Fruit2 = MakeFruit(320, 100, 32, 32,0);
    AddGameObject("Fruits2", Fruit2);
    //3
    GameObject* Fruit3 = MakeFruit(320, 200, 32, 32,0);
    AddGameObject("Fruits3",Fruit3);
    //4
    GameObject* Fruit4 = MakeFruit(450, 400, 32, 32,0);
    AddGameObject("Fruits4",Fruit4);
    //5
    GameObject* Fruit5 = MakeFruit(730, 150, 32, 32,0);
    AddGameObject("Fruits5",Fruit5);
    //6
    GameObject* Fruit6 = MakeFruit(960, 250, 32, 32,0);
    AddGameObject("Fruits6",Fruit6);
    //7
    GameObject* Fruit7 = MakeFruit(1220, 100, 32, 32,0);
    AddGameObject("Fruits7",Fruit7);
    //8
    GameObject* Fruit8 = MakeFruit(930, 300, 32, 32,0);
    AddGameObject("Fruits8",Fruit8);

    vecFruits.push_back(Fruit1);
    vecFruits.push_back(Fruit2);
    vecFruits.push_back(Fruit3);
    vecFruits.push_back(Fruit4);
    vecFruits.push_back(Fruit5);
    vecFruits.push_back(Fruit6);
    vecFruits.push_back(Fruit7);
    vecFruits.push_back(Fruit8);


    gMang = new GameManager();
    gMang->Start(player, theTileMap, vecFruits, vecAi, m_renderer);
    */

    gMang = new GameManager();
    gMang->Start(player, theTileMap, m_renderer);
    printf("Loading Collectibles and Enemies\n");
    LoadCollectibles("saves/level_save_collectibles.txt");
    LoadEnemies("saves/level_save_enemies.txt");
    printf("After Loading\n");

}

void ResourceManager::LoadCollectibles(const char * filename) {
    std::string tag = "Fruit";

    std::ifstream save_file;
    save_file.open(filename);

    std::string info;
    int type;
    double posX;
    double posY;

    while (std::getline(save_file, info)) {
        //int result = sscanf(info.c_str(), "%i %d %d", &type, &posX, &posY);
        std::istringstream line(info);
        line >> type >> posX >> posY;

        GameObject* Fruit = MakeFruit(posX, posY, 32, 32, type);
        std::string fulltag = tag + std::to_string(gMang->NumCollectibles());
        AddGameObject(fulltag, Fruit);
        gMang->AddCollectible(Fruit);
    }
}

void ResourceManager::LoadEnemies(const char* filename) {
    std::string tag = "Enemy";

    std::ifstream save_file;
    save_file.open(filename);

    std::string info;
    int type;
    double posX;
    double posY;
    int range;

    while (std::getline(save_file, info)) {
        //sscanf(info.c_str(), "%i %d %d %i", &type, &posX, &posY, &range);
        std::istringstream line(info);
        line >> type >> posX >> posY >> range;
        GameObject* Enemy = MakeEnemy(posX, posY,range, type);
        std::string fulltag = tag + std::to_string(gMang->NumEnemies());
        AddGameObject(fulltag, Enemy);
        gMang->AddEnemy(Enemy);
    }
}

GameObject* ResourceManager::MakeEnemy(int x, int y, int range, int type) {
    GameObject* enemy = new GameObject();
    TransformComponent* tc = new TransformComponent();
    tc->SetPosition(x, y);
    tc->SetWidth(32);
    tc->SetHeight(32);
    AIControllerComponent* aic = new AIControllerComponent(tc, range, type);
    Sprite* s = new Sprite(enemy_textures[type], tc, 32, 32);
    PhysicsComponent* pc = new PhysicsComponent(tc, false);
    enemy->AddComponent(tc);
    enemy->AddComponent(aic);
    enemy->AddComponent(s);
    enemy->AddComponent(pc);
    return enemy;
}

void ResourceManager::Shutdown() {
     gMang->Stop();
    // for (auto pair : gameObjects) {
    //     pair.second->free();
    // }
}

void ResourceManager::AddGameObject(std::string name, GameObject* object) {
    gameObjects.insert(make_pair(name, object));
}

GameObject* ResourceManager::GetGameObject(std::string name) {
    auto it = gameObjects.find(name);

    if (it == gameObjects.end()) {
        // If the requested game object is not found
    }

    return it->second;
}

void ResourceManager::RemoveGameObject(std::string name) {
    auto it = gameObjects.find(name);

    if (it == gameObjects.end()) {
        return;
    }

    // it->second->free();
    gameObjects.erase(it);
}

void ResourceManager::Input(SDL_Event e) {
    for (auto pair : gameObjects) {
        pair.second->Input(e);
    }
}

void ResourceManager::Update() {
    for (auto pair : gameObjects) {
        if (pair.second->Update()) {
            gMang->win = true;
        }
    }
    gMang->Update();
}

void ResourceManager::Render(SDL_Renderer* m_renderer) {
    for (auto pair : gameObjects) {
        if (pair.first == "Background") {
            pair.second->Render(m_renderer);
        }
    }

    for (auto pair : gameObjects) {
        if (pair.first == "TileMap") {
            pair.second->Render(m_renderer);
        }
    }

    if (show > 0) {
        SDL_Rect rectangle = {
            .x = xRed,
            .y = yRed,
            .w = 32,
            .h = 32
        };
        SDL_SetRenderDrawColor(the_renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(the_renderer, &rectangle);
        --show;
    }

    for (auto pair: gameObjects) {
        if (pair.first != "Background" && pair.first != "TileMap") {
            //printf("%s\n", pair.first.c_str());
            pair.second->Render(m_renderer);
        }
    }

    /*
    for (auto pair : gameObjects) {
        if (pair.first == "Player") {
            pair.second->Render(m_renderer);
        }
    }

    for (auto pair : gameObjects) {
        if (pair.first == "Enemy") {
            pair.second->Render(m_renderer);
        }
    }

    for (auto pair : gameObjects) {
        if (pair.first == "Fruits1" || pair.first == "Fruits2" || pair.first == "Fruits3" || pair.first == "Fruits4")
	{
	    pair.second->Render(m_renderer);
	}
        else if(pair.first == "Fruits5" || pair.first == "Fruits6" || pair.first == "Fruits7" || pair.first == "Fruits8")
	{
            pair.second->Render(m_renderer);
        }
    }
    */
    gMang->Render();
}
