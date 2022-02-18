#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "TileMap.hpp"

// Creates a new tile map
TileMap::TileMap(SDL_Texture* texture, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY) {
    // Setup variables
    m_Rows = rows;
    m_Cols = cols;
    m_TileWidth = _TileWidth;
    m_TileHeight = _TileHeight;
    m_MapX = _mapX;
    m_MapY = _mapY;

    m_Texture = texture;

    // Setup the tile map array
    // This sets each tile to '0'
    m_Tiles = new int[m_MapX * m_MapY];
    for (int i = 0; i < m_MapX * m_MapY; i++) {
        m_Tiles[i] = -1; // Default value is no tile.
    }
    // SDL_Log("Tile sheet to here");
}

// Destructor
TileMap::~TileMap() {
    SDL_DestroyTexture(m_Texture);
    // Remove our tile map
    delete[] m_Tiles;
}

void TileMap::SaveMap(const char* filename) {
    printf("Tilemap Saved!\n");
    char buffer[m_MapX * m_MapY * 3 + m_MapY];
    // printf("m_MapX: %i, m_MapY: %i, buffer size: %i\n", m_MapX, m_MapY, sizeof(buffer));
    char* to_add = buffer;
    for (int row = 0; row < m_MapY; ++row) {
        for (int col = 0; col < m_MapX; ++col) {
            int tile = GetTileType(col, row); // maybe should switch row and col
            //put number into buffer
            int to_move = 1;
            if (tile < 0 || tile > 9) {
                to_move = 2;
            }
            sprintf(to_add, "%i", tile);
            to_add += to_move;
            *to_add = ' ';
            ++to_add;
        }
        *to_add = '\n';
        ++to_add;
    }
    *to_add = '\0';
    std::ofstream save_file;
    save_file.open(filename, std::ios::trunc);
    save_file << buffer;
    save_file.close();
}

// Loads tilemap from given filename/path
void TileMap::LoadMap(const char* filename) {
	std::ifstream file(filename);
	std::string tempStr;
	std::ifstream tempFile(filename);
	std::getline(tempFile, tempStr);
	tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), ' '), tempStr.end());
	tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), '-'), tempStr.end());
	int length = tempStr.length();
	int incLength = 0;
	int yLength = 0;
	int tempInt;
	tempStr = "";

	while (std::getline(file, tempStr, ' ')) {
		std::stringstream stream(tempStr);
		stream >> tempInt;
		//SDL_Log("Hmmmmmm: %d", tempInt);
        if (incLength < 0 || yLength < 0) {
            printf("generate map index < 0\n");
        }
        if (incLength >= m_MapX) {
            // printf("error: incLength(%i) >= m_MapX (%i).  Setting incLength to %i\n", incLength, m_MapX, m_MapX - 1);
            incLength = m_MapX - 1;
        }
        if (yLength >= m_MapY) {
            // printf("error: yLength(%i) >= m_MapY (%i).  Setting yLength to %i\n", yLength, m_MapY, m_MapY - 1);
            yLength = m_MapY - 1;
        }
		SetTile(incLength,yLength, tempInt);
		if (incLength == length - 1) {
			incLength = 0;
			yLength += 1;
		}
		else {
			incLength += 1;
		}
	}
/*
    for(int y= 0; y < m_MapY; y++){
        for(int x= 0; x < m_MapX; x++){
           if(y==0){
                SetTile(x,y,12);
           }
           if(y==m_MapY-1){
                SetTile(x,y,0);
           }
       }
    }
 */
}

// Helper function to print out the tile map to the console
void TileMap::PrintMap() {
    /*
    for (int y= 0; y < m_MapY; y++) {
        for (int x= 0; x < m_MapX; x++) {
            std::cout << std::setw(3) << GetTileType(x, y);
       }
         std::cout << "\n";
    }
    */
}

// Sets a tile a certain type
void TileMap::SetTile(int x, int y, int type) {
    m_Tiles[y * m_MapX + x] = type;
}

// Returns what the tile is at a specific position
int TileMap::GetTileType(int x, int y) {
    return m_Tiles[y * m_MapX + x];
}

int TileMap::GetNumRows() {
    return m_MapX;
}

int TileMap::GetNumCols() {
    return m_MapY;
}

SDL_Rect TileMap::GetTileRect(int x, int y) {
    SDL_Rect r;
    r.x = x * m_TileWidth;
    r.y = y * m_TileHeight;
    r.w = m_TileWidth;
    r.h = m_TileHeight;
    return r;
}

// Render the tile map
void TileMap::Render(SDL_Renderer* ren) {
    if (ren == nullptr) {
        SDL_Log("No valid renderer found");
    }

    SDL_Rect src, dest;
    for (int y = 0; y < m_MapY; y++) {
        for (int x = 0; x < m_MapX; x++) {
            // Select our tile
            int currentTile = GetTileType(x, y);
            if (currentTile > -1) {
                src = {(currentTile % m_Cols) * m_TileWidth, (currentTile / m_Rows) * m_TileHeight, m_TileWidth, m_TileHeight};
                dest = {x * m_TileWidth, y * m_TileHeight, m_TileWidth, m_TileHeight};
                SDL_RenderCopy(ren, m_Texture, &src, &dest);
            }
        }
    }
}

void TileMap::Update() {}
