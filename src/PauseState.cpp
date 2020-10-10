#include "header.h"
#include "PauseState.h"
#include "RunningState.h"
#include "GameEngine.h"

void PauseState::virtSetUpEngine(GameEngine& pEngine) {

}

void PauseState::virtDrawLabelText(GameEngine& pEngine)
{
	pEngine.lockForegroundForDrawing();
	pEngine.drawForegroundString(250, 10, "Paused. Press SPACE to continue", 0xffffff, NULL);
	pEngine.unlockForegroundForDrawing();
	pEngine.redrawDisplay();
	// TODO: Add your implementation code here.
}

void PauseState::applyState(GameEngine& pEngine) {
	pEngine.pause();
	SDL_PauseAudioDevice(pEngine.deviceId, 1);
	SDL_PauseAudioDevice(pEngine.bulletDevice, 1);
	SDL_PauseAudioDevice(pEngine.caseDevice, 1);
	SDL_PauseAudioDevice(pEngine.bottleDevice, 1);
	SDL_PauseAudioDevice(pEngine.doorDevice, 1);
	SDL_PauseAudioDevice(pEngine.deadDevice, 1);
}
void PauseState::virtSetUpKeyboard(GameEngine& pEngine, int iKeyCode) {
	switch (iKeyCode) {
	case SDLK_SPACE:
		delete pEngine.m_pState;
		pEngine.m_pState = new RunningState;
		pEngine.m_pState->applyState(pEngine);
	}

}

void PauseState::virtSetUpForeground(GameEngine& pEngine) {

}
void PauseState::virtSetUpMouseDown(GameEngine& pEngine, int iButton, int iX, int iY) {

}


