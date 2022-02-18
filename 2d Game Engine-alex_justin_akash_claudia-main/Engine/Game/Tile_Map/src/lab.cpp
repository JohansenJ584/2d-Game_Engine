// Support Code written by Michael D. Shah
// Last Updated: 2/19/21
// Please do not redistribute without asking permission.

#include <sstream>
#include "Engine.hpp" // The main engine
#include "GraphicsEngineRenderer.hpp" // The renderering engine

int main(int argc, char** argv){
	// Create an instance of an object for our engine
	EditorEngine engine;
	// Initialize the Engine Subsystems
	engine.InitializeGraphicsSubSystem();	 
    // Once all subsystems have been initialized
    // Start the engine
    
    std::string str1;

    if (argc == 1)
    {
	std::cout << "Please enter what file you want to edit\n";
	exit(-1);
    }
    else
    {
	str1 = argv[1];
	std::fstream f(("file/" + str1).c_str());
	if (!f.good())
	{
		std::cout << "File does not exist, please try again.\n" ;
		exit(-1);
	}
	else
	{
		f.close();
	}
    }
    
    engine.Start(str1);
    // Run our program forever
	engine.MainGameLoop();
    // Explicitly call Shutdown to terminate our engine
    engine.Shutdown();
	// When our program ends, it will exit scope,
    // the destructor will then be called
    // and clean up the program.
	return 0;
}
