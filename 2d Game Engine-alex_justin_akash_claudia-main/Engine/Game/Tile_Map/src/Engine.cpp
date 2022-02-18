#include "Engine.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
// #include "Camera.hpp"
// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>

// Try toggling this number!
#define CHARACTERS 1

// Global array to create our characters
EditorSprite characters[CHARACTERS];

// Create a TileMap
TileMapEditor* myTileMap;

//Camera* Camera01;

int xRed;
int yRed;

//std::string fileName;

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
EditorEngine::EditorEngine(){
}


// Proper shutdown and destroy initialized objects
EditorEngine::~EditorEngine(){
}

// Return Input
void EditorEngine::Input(bool *quit){
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    int tempPlace;
      //Handle events on queue
    while(SDL_PollEvent( &e ) != 0)
    {
    	// User posts an event to quit
       	// An example is hitting the "x" in the corner of the window.
       	if(e.type == SDL_QUIT)
	{
	       	*quit = true;
        }
	//Camera01->handleEvent(e);
	bool space = false;
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
        //Adjust the velocity
        	switch( e.key.keysym.sym )
                {
            		case SDLK_UP: yRed -= 32; break;
            		case SDLK_DOWN: yRed += 32; break;
            		case SDLK_LEFT: xRed -= 32; break;
            		case SDLK_RIGHT: xRed += 32; break;
			case SDLK_SPACE: space = true; break;
        	}
		if (space)
		{
			if(yRed < 0 && xRed < 0)
			{
				xRed = 0;
				yRed = 0;
				tempPlace = myTileMap->GetTileType(0,0);
			}
			else if (yRed < 0)
			{
				yRed = 0;
				tempPlace = myTileMap->GetTileType(xRed/32,0);
			}
			else if (xRed < 0)
			{
				xRed = 0;
				tempPlace = myTileMap->GetTileType(0,yRed/32);
			}
			else
			{
				tempPlace = myTileMap->GetTileType(xRed/32,yRed/32);
			}
			if(tempPlace >= 8)
			{
				tempPlace = -1;
			}
			else
			{
				tempPlace += 1;
			}
	
			if(yRed < 0 && xRed < 0)
			{
				xRed = 0;
				yRed = 0;
				myTileMap->SetTile(0,0,tempPlace);
			}
			else if (yRed < 0)
			{
				yRed = 0;
				myTileMap->SetTile(xRed/32,0,tempPlace);
			}
			else if (xRed < 0)
			{
				xRed = 0;
				myTileMap->SetTile(0,yRed/32,tempPlace);
			}
			else
			{
				myTileMap->SetTile(xRed/32,yRed/32,tempPlace);
			}
			space = false;
		}
		//myTileMap->setTileType()
		characters[0].SetPosition(xRed, yRed);
    	}
    }
}

// Update SDL
void EditorEngine::Update()
{
    static int frame =0 ;
    
    // Increment the frame that
    // the sprite is playing
    frame++;
    if(frame>6){
        frame=0;
    }
    //Camera01->move(); 
    // iterate through each of our characters
    for(int i =0; i < CHARACTERS; i++){
        characters[i].Update(20,20, frame);
    }
}


// Render
// The render function gets called once per loop
void EditorEngine::Render(){
    // Set the color of the empty framebuffer
    m_renderer->SetRenderDrawColor(110, 130,170,0xFF);
    // Clear the screen to the color of the empty framebuffer
    m_renderer->RenderClear();

    // Render the tile map
    //myTileMap->Render(m_renderer->GetRenderer(), clip);

    // Render each of the character(s)
    for(int i =0; i < CHARACTERS; i++){
        characters[i].Render(m_renderer->GetRenderer());
    }
    myTileMap->Render(m_renderer->GetRenderer());

    // Flip the buffer to render
    m_renderer->RenderPresent();
}



//Loops forever!
void EditorEngine::MainGameLoop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;

    // While application is running
    while(!quit){
      // Get user input
      Input(&quit);
      // If you have time, implement your frame capping code here
      // Otherwise, this is a cheap hack for this lab.
      SDL_Delay(250);
      // Update our scene
      Update();
      // Render using OpenGL
      Render();
      //Update screen of our specified window
    }
    //Disable text input
    SDL_StopTextInput();
}

void EditorEngine::Start(std::string file){
    // Report which subsystems are being initialized
    if(m_renderer!=nullptr){
        std::cout << "Initializing Graphics Subsystem\n";
    }else{
        std::cout << "No Graphics Subsystem initialized\n";
    }

    //Camera01 = new Camera(1280,720);


    // Move Sprite to initial position
    characters[0].SetPosition(0,0);
    // Load an image for our character
    characters[0].LoadImage("./images/Red.bmp",m_renderer->GetRenderer());

    // Setup our TileMap
    // This tile map is 20x11 in our game
    // It is using a 'reference' tilemap with 8x8 tiles
    // that are each 64x64 pixels.
    myTileMap = new TileMapEditor("./images/spritesheetNum.bmp",3,3,32,32,40,22,m_renderer->GetRenderer());
    // Generate a a simple tilemap
    myTileMap->GenerateSimpleMap(file);
    // Print out the map to the console
    // so we can see what was created.
    myTileMap->PrintMap();

}

void EditorEngine::Shutdown(){
    // Shut down our Tile Systems
    if(nullptr!=m_renderer){
        delete m_renderer;
    } 

    // Destroy our tilemap
    if(nullptr!=myTileMap){
        delete myTileMap;
    }
}

void EditorEngine::InitializeGraphicsSubSystem(){
    // Setup our Renderer
    m_renderer = new EditorGraphicsEngineRenderer(1280,720);
    if(nullptr == m_renderer){
        exit(1); // Terminate program if renderer 
                 // cannot be created.
                 // (Optional) TODO:   Could put an error 
                 //                    messeage, or try to 
                 //                    reinitialize the engine 
                 //                    with a different render
    }
}
