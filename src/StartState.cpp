#include "header.h"
#include "StartState.h"
#include "RunningState.h"
#include "SelectState.h"
#include "EndState.h"
#include "HelpState.h"
#include "AdvancedTileManager.h"
#include "GameEngine.h"
#include <ctime>

void StartState::virtSetUpEngine(GameEngine& pEngine) {
	pEngine.m_oTheBackgroundSurface.mySDLLockSurface();
	pEngine.fillBackground(0x000000);
	pEngine.background.renderImage(pEngine.getBackgroundSurface(), 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.m_oTheBackgroundSurface.mySDLUnlockSurface();
	pEngine.m_iCurrentSurfaceNumber = 0;
	pEngine.m_iDefaultUpdatePeriod = 10;
	srand(time(0));
	AdvancedTileManager& tm = pEngine.tm;
	const char* data[] = {
				"hhhehhhhhhhhhhhhhhhhhhhhhhhhhh",
				"hbbabbaabaaaaaaabbbaaaaabbbabh",
				"hbbaaaabgabbabbabbgabbbaaaaaah",
				"haaabbabbbbaaabaaabbaaaabbbabh",
				"habbbaabaaubbbbababaabbbbgbabh",
				"haababbbabbaaaaabababbaaaaaabh",
				"hbabaaabaaaabababaaabbabababbh",
				"hbaababbbababbaabbbabaabbbaaah",
				"hbbaaaaaabbabaabuaabbabaaabbah",
				"hbabbabbabaababbbbaababababbah",
				"hgabaaaaababbaaaaababaaabaaaah",
				"hbababbbbbaaabbbbababbbbbbabbh",
				"hbabaaaaaaababbbbabaaaagbbabbh",
				"haabbabbabbaabaaaababbbbbbabgh",
				"hbabbaabaaabavabbbbaaaaavaabah",
				"haabbbabbbbbabaaabbabbbbbbbbah",
				"habbaaaaaaaaababagbaababbaaaah",
				"haaaababbbbbabababbbaaafaabbbh",
				"hbbbababaaaaaabbagbfababbaaabh",
				"hhhhhhhhhhhhhhhhhhhhdhhhhhhhhh" };

	// Specify how many tiles wide and high
	tm.setMapSize(30, 20);
	// Set up the tiles
	for (int x = 0; x < 30; x++)
		for (int y = 0; y < 20; y++) {
			int value = data[y][x] - 'a';
			if (value == 0) {
				int random = rand() % 6;
				if (random == 0) {
					tm.setMapValue(x, y, 5);
				}
			}
			else {
				tm.setMapValue(x, y, value);
			}

		}


	//for (int y = 0; y < 20; y++)
	//{
	//	for (int x = 0; x < 30; x++)
	//		std::cout << tm.getMapValue(x, y);
	//	std::cout << std::endl;
	//}

	// Specify the screen x,y of top left corner
	tm.setTopLeftPositionOnScreen(350, 200);
}



void StartState::virtDrawLabelText(GameEngine& pEngine)
{
	pEngine.lockForegroundForDrawing();
	pEngine.drawForegroundString(615, 410, "Start", 0xffffff, NULL);
	pEngine.drawForegroundString(615, 480, "Load", 0xffffff, NULL);
	pEngine.drawForegroundString(615, 550, "Help", 0xffffff, NULL);
	pEngine.drawForegroundString(615, 620, "Exit", 0xffffff, NULL);
	pEngine.unlockForegroundForDrawing();
	pEngine.redrawDisplay();
}

void StartState::applyState(GameEngine& pEngine) {
	pEngine.lockAndSetupBackground();
}

void StartState::virtSetUpKeyboard(GameEngine& pEngine, int iKeyCode) {


}

void StartState::virtSetUpForeground(GameEngine& pEngine) {
	pEngine.startElement.renderImageWithMask(pEngine.getForegroundSurface(), 0, 0, 0, 0, pEngine.startElement.getWidth(), pEngine.startElement.getHeight());
	pEngine.drawForegroundRectangle(600, 405, 700, 445, 0x708090);
	pEngine.drawForegroundRectangle(600, 475, 700, 515, 0x708090);
	pEngine.drawForegroundRectangle(600, 545, 700, 585, 0x708090);
	pEngine.drawForegroundRectangle(600, 615, 700, 655, 0x708090);
}
void StartState::virtSetUpMouseDown(GameEngine& pEngine, int iButton, int iX, int iY) {
	if (iButton == SDL_BUTTON_LEFT) {
		if (iX > 600 && iX < 700 && iY > 405 && iY < 445) {
			pEngine.playClickMusic();
			delete pEngine.m_pState;
			pEngine.m_pState = new SelectState;
			pEngine.m_pState->applyState(pEngine);

		}
		else if (iX > 600 && iX < 700 && iY > 475 && iY < 515) {
			pEngine.playClickMusic();
			pEngine.isLoad = true;
			delete pEngine.m_pState;
			pEngine.m_pState = new RunningState;
			pEngine.m_pState->applyState(pEngine);

		}
		else if (iX > 600 && iX < 700 && iY > 545 && iY < 585) {
			pEngine.playClickMusic();
			delete pEngine.m_pState;
			pEngine.m_pState = new HelpState;
			pEngine.m_pState->applyState(pEngine);
			
		}
		else if (iX > 600 && iX < 700 && iY > 615 && iY < 655) {
			pEngine.playClickMusic();
			pEngine.closeAllMusic();
			exit(0);
		}

	}
}
