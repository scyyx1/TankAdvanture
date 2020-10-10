#include "header.h"
#include <ctime>
#include "templates.h"
#include "GameEngine.h"

// Determine the base window size
const int BaseScreenWidth = 1300;
const int BaseScreenHeight = 800;


// Main program
int doProgram(int argc, char *argv[])
{ 
	int iResult = 0;
	// initialize the engine
	GameEngine oMain;

	char buf[1024];
	sprintf(buf, "C++ Coursework Framework Program : Size %d x %d", BaseScreenWidth, BaseScreenHeight);
	iResult = oMain.initialise(buf, BaseScreenWidth, BaseScreenHeight, "Cornerstone Regular.ttf", 24);

	iResult = oMain.mainLoop();
	oMain.deinitialise();
	return iResult;
} 




int main(int argc, char *argv[])
{
	// Send random number generator with current time
	::srand( (unsigned int)time(0));

	int iResult = doProgram( argc, argv );

	ImageManager::destroyImageManager();
	
// Detect memory leaks on windows
#if defined(_MSC_VER)
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
#endif

	return iResult;
}
