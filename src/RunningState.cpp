#include "header.h"
#include "RunningState.h"
#include "PauseState.h"
#include "GameEngine.h"
#include<SDL_audio.h>

void RunningState::virtSetUpEngine(GameEngine& pEngine) {
	pEngine.m_oTheRunningSurface.mySDLLockSurface();
	pEngine.m_oTheRunningSurface.fillSurface(0x000000);
	pEngine.background.renderImage(&pEngine.m_oTheRunningSurface, 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.runningElement.renderImageWithMask(&pEngine.m_oTheRunningSurface, 0, 0, 0, 0, pEngine.runningElement.getWidth(), pEngine.runningElement.getHeight());
	pEngine.lives.renderImage(&pEngine.m_oTheRunningSurface, 0, 0, 0, 0, pEngine.lives.getWidth(), pEngine.lives.getHeight());
	pEngine.m_oTheRunningSurface.mySDLUnlockSurface();
	pEngine.tm.drawAllTiles(&pEngine, &pEngine.m_oTheRunningSurface);
	pEngine.m_iCurrentSurfaceNumber = 1;
}

void RunningState::virtDrawLabelText(GameEngine& pEngine)
{
	char buf[128];
	char live[128];
	int reward = 1;
	if (pEngine.isEasy) {
		reward = 1;
	}
	else if (pEngine.isMedium) {
		reward = 2;
	}
	else if (pEngine.isDifficult) {
		reward = 3;
	}
	sprintf(buf, "SCORE: %d  X %d", pEngine.score, reward);
	sprintf(live, " X %d", pEngine.mainObject->getHealth());
	pEngine.lockForegroundForDrawing();
	pEngine.drawForegroundString(300, 650, "Running", 0xffffff, NULL);
	pEngine.drawForegroundString(700, 650, buf, 0xffffff, NULL);
	pEngine.drawForegroundString(30, 0, live, 0xffffff, NULL);
	SimpleImage entry = ImageManager::loadImage("resources/entry.png", true);
	entry.renderImageWithMask(pEngine.getBackgroundSurface(), 0, 0, 750, 600, entry.getWidth(), entry.getHeight());
	pEngine.unlockForegroundForDrawing();
	pEngine.redrawDisplay();
	// TODO: Add your implementation code here.
}

void RunningState::applyState(GameEngine& pEngine) {
	if (pEngine.isPaused()) {
		pEngine.unpause();
		SDL_PauseAudioDevice(pEngine.deviceId, 0);
		SDL_PauseAudioDevice(pEngine.bulletDevice, 0);
		SDL_PauseAudioDevice(pEngine.caseDevice, 0);
		SDL_PauseAudioDevice(pEngine.bottleDevice, 0);
		SDL_PauseAudioDevice(pEngine.doorDevice, 0);
		SDL_PauseAudioDevice(pEngine.deadDevice, 0);
	}
	else {
		pEngine.virtInitialiseObjects();
		pEngine.lockAndSetupBackground();
	}
	pEngine.setAllObjectsVisible(true);
	pEngine.redrawDisplay();

}

void RunningState::virtSetUpKeyboard(GameEngine& pEngine, int iKeyCode) {
	switch (iKeyCode) {
	case SDLK_u:
		pEngine.save();
		break;
	case SDLK_SPACE:
		delete pEngine.m_pState;
		pEngine.m_pState = new PauseState;
		pEngine.m_pState->applyState(pEngine);
		break;
	case SDLK_j:
		pEngine.addBullet(pEngine.mainObject->getMapX() * 20 + 350, pEngine.mainObject->getMapY() * 20 + 200, pEngine.mainObject->getDir());
		pEngine.playBulletMusic();
		break;
	}

}

void RunningState::virtSetUpForeground(GameEngine& pEngine) {
	pEngine.drawForegroundString(400, 50, "Scores as many points as you can!", 0xffffff, NULL);
	pEngine.drawForegroundString(140, 230, "Up", 0xffffff, pEngine.getFont("Cornerstone Regular.ttf", 20));
	pEngine.drawForegroundString(125, 320, "Down", 0xffffff, pEngine.getFont("Cornerstone Regular.ttf", 20));
	pEngine.drawForegroundString(190, 320, "Right", 0xffffff, pEngine.getFont("Cornerstone Regular.ttf", 20));
	pEngine.drawForegroundString(70, 320, "Left", 0xffffff, pEngine.getFont("Cornerstone Regular.ttf", 20));
	pEngine.drawForegroundString(125, 420, "Fire", 0xffffff, pEngine.getFont("Cornerstone Regular.ttf", 20));
	pEngine.drawForegroundString(125, 500, "Save", 0xffffff, pEngine.getFont("Cornerstone Regular.ttf", 20));
	pEngine.drawForegroundString(125, 600, "Pause", 0xffffff, pEngine.getFont("Cornerstone Regular.ttf", 20));
	pEngine.drawForegroundString(1010, 230, "Get   as much as", 0xffffff, NULL);
	pEngine.blueBottle.renderImageWithMask(pEngine.getForegroundSurface(), 0, 0, 1060,230, pEngine.blueBottle.getWidth(), pEngine.blueBottle.getHeight());
	pEngine.drawForegroundString(1010, 260, "possible", 0xffffff, NULL);
	pEngine.drawForegroundString(1010, 310, "Find   to unlock", 0xffffff, NULL);
	pEngine.introKey.renderImageWithMask(pEngine.getForegroundSurface(), 0, 0, 1070, 310, pEngine.introKey.getWidth(), pEngine.introKey.getHeight());
	pEngine.drawForegroundString(1010, 340, "The door!", 0xffffff, NULL);
	pEngine.drawForegroundString(1010, 390, "Steal as much  ", 0xffffff, NULL);
	pEngine.introCase.renderImageWithMask(pEngine.getForegroundSurface(), 0, 0, 1230, 390, pEngine.introCase.getWidth(), pEngine.introCase.getHeight());
	pEngine.drawForegroundString(1010, 420, "as you can!  ", 0xffffff, NULL);
	pEngine.drawForegroundString(1010, 470, "Be careful! Some  ", 0xffffff, NULL);
	pEngine.drawForegroundString(1010, 500, "of them are traps", 0xffffff, NULL);
	pEngine.drawForegroundString(1010, 530, "which will call   ", 0xffffff, NULL);
	pEngine.introTank.renderImageWithMask(pEngine.getForegroundSurface(), 0, 0, 1240, 530, pEngine.introTank.getWidth(), pEngine.introTank.getHeight());

	
}
void RunningState::virtSetUpMouseDown(GameEngine& pEngine, int iButton, int iX, int iY) {

}




