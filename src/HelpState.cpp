#include "header.h"
#include "HelpState.h"
#include "StartState.h"
#include "GameEngine.h"


void HelpState::virtSetUpEngine(GameEngine& pEngine) {
	pEngine.m_oTheBackgroundSurface.mySDLLockSurface();
	pEngine.fillBackground(0x000000);
	pEngine.background.renderImage(pEngine.getBackgroundSurface(), 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.m_oTheBackgroundSurface.mySDLUnlockSurface();
}



void HelpState::virtDrawLabelText(GameEngine& pEngine)
{
	pEngine.lockForegroundForDrawing();
	pEngine.drawForegroundString(550, 600, "BACK", 0xffffff, NULL);
	pEngine.unlockForegroundForDrawing();
	pEngine.redrawDisplay();
}

void HelpState::applyState(GameEngine& pEngine) {

}
void HelpState::virtSetUpKeyboard(GameEngine& pEngine, int iKeyCode) {

}

void HelpState::virtSetUpForeground(GameEngine& pEngine) {
	pEngine.helpElement.renderImageWithMask(pEngine.getForegroundSurface(), 0, 0, 0, 0, pEngine.helpElement.getWidth(), pEngine.helpElement.getHeight());

}
void HelpState::virtSetUpMouseDown(GameEngine& pEngine, int iButton, int iX, int iY) {
	if (iButton == SDL_BUTTON_LEFT) {
		if (iX > 550 && iX < 630 && iY > 600 && iY < 622) {
			pEngine.playClickMusic();
			delete pEngine.m_pState;
			pEngine.m_pState = new StartState;
			pEngine.m_pState->applyState(pEngine);
		}
	}
}

