#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <string>

#include "GraphicsEngineRenderer.hpp"
#include "Component.hpp"

// The tile map for the game, acts as a component.
/*!
 * The tile map for the game acts a component.
 * Evertything is based off the array m_tiles.
 */
class TileMap : public Component {
    public:
    	/*!
    	 * Consructor that takes in:
    	 * texture: The texture
    	 * row: The total number of rows
    	 * col: The total number of Cols
    	 * _TileWidth: Whats the width of each tile
    	 * _TileHeiht: Whats the height of the tile
    	 * _mapx: How many Col
    	 * _mapy: How many rows
    	 */
        TileMap(SDL_Texture* texture, int rows, int cols, int _TileWidth, int _TileHeight, int _mapX, int _mapY);

        // Destructor
    	/*!
    	 * Destructor.
    	 * Destruct the tile map and make sure the nothing is left hanging.
    	 */
        ~TileMap();

    	/*!
    	 * Reads in the given file into the map array.
    	 */
        void LoadMap(const char* filename);

        /*!
        * Saves the current state of the tile map to a .txt file with the given name, overwriting the file if it exists and making it if it doesn't.
        */
        void SaveMap(const char* filename);

        /*!
    	 * Prints out the array of tiles for debuging and vizuil assistance.
         * Prints the map to the console
    	 */
        void PrintMap();

    	/*!
    	 * Allows for tiles to be set from outside the scope.
    	 * Does the math from x and y to find spot in array.
         * Sets the type of a tile at the given position.
    	 */
        void SetTile(int x, int y, int type);

    	/*!
         * Returns the type of a tile at the given position.
    	 * Based of x and y given cords.
    	 */
        int GetTileType(int x, int y);

    	/*!
        * Returns the number of rows in the tile map.
    	*/
        int GetNumRows();

	    /*!
        * Returns the number of columns in the tile map.
	    */
        int GetNumCols();

	    /*!
        * Returns an SDL_Rect with the dimensions of the tile at the given position.
	    * This is based of x and y.
	    */
        SDL_Rect GetTileRect(int x, int y);

    	/*!
    	 * Renders all of the tiles in the tile map.
    	 * Uses the world renderer.
    	 */
        virtual void Render(SDL_Renderer* ren);

	    /*!
         * Does nothing.
	     */
        virtual void Update();

    private:
        /*!
         * Dimensions of the tile map.
         */
        int m_Rows, m_Cols;

    	/*!
    	 * Dimensions of a tile.
    	 */
        int m_TileWidth, m_TileHeight;
	    /*!
        * Size of the tile map.
        * m_MapX is the number of columns.
        * m_MapY is the number of rows.
	    */
        int m_MapX,  m_MapY;

	    /*!
        * Points to the surface of the tile's spritesheet.
	    */
        SDL_Surface* m_TileSpriteSheet;

	    /*!
        * Points to the texture of the tile's spritesheet.
	    */
        SDL_Texture* m_Texture;

        /*!
        * Stores the tile types.
        */
        int* m_Tiles;
};

#endif
