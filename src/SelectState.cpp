#include "SelectState.h"
#include "header.h"
#include "StartState.h"
#include "RunningState.h"
#include "AdvancedTileManager.h"
#include "GameEngine.h"
#include <ctime>
void SelectState::virtSetUpEngine(GameEngine& pEngine) {
	pEngine.m_oTheBackgroundSurface.mySDLLockSurface();
	pEngine.fillBackground(0x000000);
	pEngine.background.renderImage(pEngine.getBackgroundSurface(), 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.m_oTheBackgroundSurface.mySDLUnlockSurface();
}



void SelectState::virtDrawLabelText(GameEngine& pEngine)
{
	pEngine.lockForegroundForDrawing();
	pEngine.drawForegroundString(610, 340, "Easy", 0xffffff, NULL);
	pEngine.drawForegroundString(610, 425, "Medium", 0xffffff, NULL);
	pEngine.drawForegroundString(610, 510, "Difficult", 0xffffff, NULL);
	pEngine.drawForegroundString(610, 595, "Back", 0xffffff, NULL);
	pEngine.unlockForegroundForDrawing();
	pEngine.redrawDisplay();
}

void SelectState::applyState(GameEngine& pEngine) {

}

void SelectState::virtSetUpKeyboard(GameEngine& pEngine, int iKeyCode) {

}

void SelectState::virtSetUpForeground(GameEngine& pEngine) {
	pEngine.selectElement.renderImageWithMask(pEngine.getForegroundSurface(), 0, 0, 0, 0, pEngine.selectElement.getWidth(), pEngine.selectElement.getHeight());
	pEngine.drawForegroundRectangle(595, 335, 730, 375, 0x708090);
	pEngine.drawForegroundRectangle(595, 420, 730, 460, 0x708090);
	pEngine.drawForegroundRectangle(595, 505, 730, 545, 0x708090);
	pEngine.drawForegroundRectangle(595, 590, 730, 630, 0x708090);
}

void SelectState::virtSetUpMouseDown(GameEngine& pEngine, int iButton, int iX, int iY) {
	if (iButton == SDL_BUTTON_LEFT) {
		if (iX > 595 && iX < 730 && iY > 335 && iY < 375) {
			pEngine.playClickMusic();
			pEngine.isEasy = true;
			delete pEngine.m_pState;
			pEngine.m_pState = new RunningState;
			pEngine.m_pState->applyState(pEngine);
		}
		else if (iX > 595 && iX < 730 && iY > 420 && iY < 460) {
			pEngine.playClickMusic();
			pEngine.isMedium = true;
			delete pEngine.m_pState;
			pEngine.m_pState = new RunningState;
			pEngine.m_pState->applyState(pEngine);
		}
		else if (iX > 595 && iX < 730 && iY > 505 && iY < 545) {
			pEngine.playClickMusic();
			pEngine.isDifficult = true;
			delete pEngine.m_pState;
			pEngine.m_pState = new RunningState;
			pEngine.m_pState->applyState(pEngine);
		}
		else if (iX > 595 && iX < 730 && iY > 590 && iY < 630) {
			pEngine.playClickMusic();
			delete pEngine.m_pState;
			pEngine.m_pState = new StartState;
			pEngine.m_pState->applyState(pEngine);
		}



	}
}

