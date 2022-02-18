#include "GameManager.hpp"

// Manages all the resources in the game

void GameManager::Start(GameObject* player, TileMap* tileMap, std::vector<GameObject*> Fruits, std::vector<GameObject*> Ai, SDL_Renderer* m_renderer) {
	this->player = player;
	this->tileMap = tileMap;
	this->Fruits = Fruits;
	this->Ai = Ai;
	this->m_renderer = m_renderer;
	Score = 0;
	win = false;
	TTF_Init();

	this->scoreFont = TTF_OpenFont("./assets/DotGothic16-Regular.ttf", 40);
	if (!scoreFont) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
	surface = TTF_RenderText_Solid(scoreFont, "", {0, 0, 0, 255});
	texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	rect = {static_cast<int>(100), static_cast<int>(650), width, height};
}

void GameManager::Start(GameObject* player, TileMap* tileMap, SDL_Renderer* m_renderer) {
	this->player = player;
	this->tileMap = tileMap;
	this->m_renderer = m_renderer;
	this->Ai = {};
	this->Fruits = {};
	Score = 0;
	win = false;
	TTF_Init();

	this->scoreFont = TTF_OpenFont("./assets/DotGothic16-Regular.ttf", 40);
	if (!scoreFont) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
	surface = TTF_RenderText_Solid(scoreFont, "", {0, 0, 0, 255});
	texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	rect = {static_cast<int>(100), static_cast<int>(650), width, height};
}

void GameManager::AddCollectible(GameObject* collectible){
	Fruits.push_back(collectible);
}

void GameManager::AddEnemy(GameObject* enemy){
	Ai.push_back(enemy);
}

int GameManager::NumCollectibles() {
	int num = 0;
    for (int ii = 0; ii < Fruits.size(); ++ii) {
        std::pair<double, double> pos;
        pos.first = -1;
        pos.second = -1;
        for (auto it = Fruits[ii]->m_components.begin(); it != Fruits[ii]->m_components.end(); ++it) {
            TransformComponent* tc = dynamic_cast<TransformComponent*>(*it);
            if(tc) {
                pos = tc->GetPosition();
            }
        }
        if (!(pos.first == -1 || pos.second == -1)) {
            ++num;
        }
    }
    return num;
}

int GameManager::NumEnemies() {
    int num = 0;
    for (int ii = 0; ii < Ai.size(); ++ii) {
        std::pair<double, double> pos;
        pos.first = -1;
        pos.second = -1;
        for (auto it = Ai[ii]->m_components.begin(); it != Ai[ii]->m_components.end(); ++it) {
            TransformComponent* tc = dynamic_cast<TransformComponent*>(*it);
            if (tc) {
                pos = tc->GetPosition();
            }
        }
        if (!(pos.first == -1 || pos.second == -1)) {
            ++num;
        }
    }
    return num;
}

void GameManager::Update() {
	// Player transform
	std::pair<double, double> ppos;
	std::pair<int, int> pdim;
	double pposx;
	double pposy;
	int pwidth;
	int pheight;
	// Fruit transform
	std::pair<double, double> fpos;
	std::pair<int, int> fdim;
	double fposx;
	double fposy;
	int fwidth;
	int fheight;

	TransformComponent* ptc = nullptr;
	for (std::vector<Component*>::iterator it = player->m_components.begin(); it != player->m_components.end(); ++it) {
		if (!ptc) {
			ptc = dynamic_cast<TransformComponent*>(*it);
		}
	}
	ppos = ptc->GetPosition();
	pdim = ptc->GetDimensions();
	pposx = ppos.first;
	pposy = ppos.second;
	pwidth = pdim.first;
	pheight = pdim.second;

    // Used to see if a collision happend with the fruit
    for (GameObject* fruit : Fruits) {
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
				Score += 1;
			}
			ftc = nullptr;
		}
    }

    for (GameObject* ai : Ai) {
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
				else {
					ptc->SetPosition(128, 508);
				}
			}
			atc = nullptr;
		}
	}
    if (NumCollectibles() == 0) {
        for (int x = 0; x <  tileMap->GetNumRows(); x++) {
        	for (int y = 0; y < tileMap->GetNumCols(); y++) {
        		// Select our tile
        		int currentTile = tileMap->GetTileType(x, y);
        		if (currentTile == 8) {
					tileMap->SetTile(x,y,-1);
				}
			}
		}
    }
}

void GameManager::Render() {
	SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    if (!win) {
		surface = TTF_RenderText_Solid(scoreFont, ("Fruit Collected:  " + std::to_string(Score)).c_str(), {0, 0, 0, 255});
        texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        int width, height;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        rect.w = width;
        rect.h = height;
        SDL_RenderCopy(m_renderer, texture, nullptr, &rect);
    }
    else {
		surface = TTF_RenderText_Solid(scoreFont, "You Win", {0, 0, 0, 255});
        texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        int width, height;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
		rect = {625, 250, width + 200, height + 100};
        SDL_RenderCopy(m_renderer, texture, nullptr, &rect);
    }
}

void GameManager::Stop() {
     TTF_CloseFont(scoreFont);
     TTF_Quit();
}

void GameManager::SaveCollectibles(const char* filename) {
	std::ofstream save_file;
	save_file.open(filename, std::ios::trunc);
	for(int ii = 0; ii < Fruits.size(); ++ii) {
		int type;
		std::pair<double, double> pos;
		pos.first = -1;
        pos.second = -1;
        for (auto it = Fruits[ii]->m_components.begin(); it != Fruits[ii]->m_components.end(); ++it) {
			CollectibleComponent* cc = dynamic_cast<CollectibleComponent*>(*it);
			TransformComponent* tc = dynamic_cast<TransformComponent*>(*it);
			if(cc) {
				type = cc->GetType();
			}
			if(tc) {
				pos = tc->GetPosition();
			}
		}
        if (!(pos.first == -1 || pos.second == -1)) {
		    save_file << type << " " << pos.first << " " << pos.second << std::endl;
        }
	}
	save_file.close();
}

void GameManager::SaveEnemies(const char* filename) {
	std::ofstream save_file;
	save_file.open(filename, std::ios::trunc);
	for(int ii = 0; ii < Ai.size(); ii++) {
		int type;
		std::pair<double, double> pos;
        pos.first = -1;
        pos.second = -1;
		int range;
		for (auto it = Ai[ii]->m_components.begin(); it != Ai[ii]->m_components.end(); ++it) {
			AIControllerComponent* aic = dynamic_cast<AIControllerComponent*>(*it);
			if (aic) {
				type = aic->GetType();
				pos = aic->GetStartPosition();
				range = aic->GetRadius();
			}
		}
        if (!(pos.first == -1 || pos.second == -1)) {
		    save_file << type << " " << pos.first << " " << pos.second << " " << range << std::endl;
	    }
    }
	save_file.close();
}
