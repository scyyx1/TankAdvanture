#include "header.h"
#include "EndState.h"
#include "StartState.h"
#include "GameEngine.h"
class GameEngine;
using namespace std;

void EndState::virtSetUpEngine(GameEngine& pEngine) {

	pEngine.m_oTheEndSurface1.mySDLLockSurface();
	pEngine.m_oTheEndSurface1.fillSurface(0x000000);
	pEngine.background.renderImage(&pEngine.m_oTheEndSurface1, 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.flash1.renderImageWithMask(&pEngine.m_oTheEndSurface1, 0, 0, 0, 0, pEngine.flash1.getWidth(), pEngine.flash1.getHeight());
	pEngine.endElement.renderImageWithMask(&pEngine.m_oTheEndSurface1, 0, 0, 0, 0, pEngine.endElement.getWidth(), pEngine.endElement.getHeight());
	pEngine.m_oTheEndSurface1.mySDLUnlockSurface();

	
	pEngine.m_oTheEndSurface2.mySDLLockSurface();
	pEngine.m_oTheEndSurface2.fillSurface(0x000000);
	pEngine.background.renderImage(&pEngine.m_oTheEndSurface2, 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.flash2.renderImageWithMask(&pEngine.m_oTheEndSurface2, 0, 0, 0, 0, pEngine.flash2.getWidth(), pEngine.flash2.getHeight());
	pEngine.endElement.renderImageWithMask(&pEngine.m_oTheEndSurface2, 0, 0, 0, 0, pEngine.endElement.getWidth(), pEngine.endElement.getHeight());
	pEngine.m_oTheEndSurface2.mySDLUnlockSurface();

	
	pEngine.m_oTheEndSurface3.mySDLLockSurface();
	pEngine.m_oTheEndSurface3.fillSurface(0x000000);
	pEngine.background.renderImage(&pEngine.m_oTheEndSurface3, 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.flash3.renderImageWithMask(&pEngine.m_oTheEndSurface3, 0, 0, 0, 0, pEngine.flash3.getWidth(), pEngine.flash3.getHeight());
	pEngine.endElement.renderImageWithMask(&pEngine.m_oTheEndSurface3, 0, 0, 0, 0, pEngine.endElement.getWidth(), pEngine.endElement.getHeight());
	pEngine.m_oTheEndSurface3.mySDLUnlockSurface();

	
	pEngine.m_oTheEndSurface4.mySDLLockSurface();
	pEngine.m_oTheEndSurface4.fillSurface(0x000000);
	pEngine.background.renderImage(&pEngine.m_oTheEndSurface4, 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.flash4.renderImageWithMask(&pEngine.m_oTheEndSurface4, 0, 0, 0, 0, pEngine.flash4.getWidth(), pEngine.flash4.getHeight());
	pEngine.endElement.renderImageWithMask(&pEngine.m_oTheEndSurface4, 0, 0, 0, 0, pEngine.endElement.getWidth(), pEngine.endElement.getHeight());
	pEngine.m_oTheEndSurface4.mySDLUnlockSurface();

	
	pEngine.m_oTheEndSurface5.mySDLLockSurface();
	pEngine.m_oTheEndSurface5.fillSurface(0x000000);
	pEngine.background.renderImage(&pEngine.m_oTheEndSurface5, 0, 0, 0, 0, pEngine.background.getWidth(), pEngine.background.getHeight());
	pEngine.flash5.renderImageWithMask(&pEngine.m_oTheEndSurface5, 0, 0, 0, 0, pEngine.flash5.getWidth(), pEngine.flash5.getHeight());
	pEngine.endElement.renderImageWithMask(&pEngine.m_oTheEndSurface5, 0, 0, 0, 0, pEngine.endElement.getWidth(), pEngine.endElement.getHeight());
	pEngine.m_oTheEndSurface5.mySDLUnlockSurface();
	pEngine.m_iCurrentSurfaceNumber = 2;
	pEngine.m_iDefaultUpdatePeriod = 50;
}

void EndState::virtDrawLabelText(GameEngine& pEngine)
{
	
	if (pEngine.switchToScore) {
		pEngine.drawForegroundString(430, 120, "High Score Board", 0xffffff, NULL);
		pEngine.readScoreFile();
	}
	else {
		const char* buf = pEngine.username.c_str();
		pEngine.lockForegroundForDrawing();
		if (pEngine.isWin) {
			pEngine.drawForegroundString(480, 120, "You Win", 0xffffff, NULL);
		}
		else if (pEngine.isLose) {
			pEngine.drawForegroundString(480, 120, "You Lose", 0xffffff, NULL);
		}
		pEngine.drawForegroundString(280, 180, "Enter Name: ", 0xffffff, NULL);
		pEngine.drawForegroundString(450, 180, buf, 0xffffff, NULL);
		pEngine.unlockForegroundForDrawing();
		pEngine.redrawDisplay();
	}

	pEngine.drawForegroundString(600, 650, "Main Menu", 0xffffff, NULL);


}
void EndState::applyState(GameEngine& pEngine) {
	pEngine.destroyOldObjects(true);
	pEngine.lockAndSetupBackground();
	pEngine.entername = true;
	pEngine.redrawDisplay();
}
void EndState::virtSetUpKeyboard(GameEngine& pEngine, int iKeyCode) {
	if (pEngine.entername) {
		if (pEngine.username.length() < 15) {
			switch (iKeyCode) {
			case SDLK_a:pEngine.username += 'a'; break;
			case SDLK_b:pEngine.username += 'b'; break;
			case SDLK_c:pEngine.username += 'c'; break;
			case SDLK_d:pEngine.username += 'd'; break;
			case SDLK_e:pEngine.username += 'e'; break;
			case SDLK_f:pEngine.username += 'f'; break;
			case SDLK_g:pEngine.username += 'g'; break;
			case SDLK_h:pEngine.username += 'h'; break;
			case SDLK_i:pEngine.username += 'i'; break;
			case SDLK_j:pEngine.username += 'j'; break;
			case SDLK_k:pEngine.username += 'k'; break;
			case SDLK_l:pEngine.username += 'l'; break;
			case SDLK_m:pEngine.username += 'm'; break;
			case SDLK_n:pEngine.username += 'n'; break;
			case SDLK_o:pEngine.username += 'o'; break;
			case SDLK_p:pEngine.username += 'p'; break;
			case SDLK_q:pEngine.username += 'q'; break;
			case SDLK_r:pEngine.username += 'r'; break;
			case SDLK_s:pEngine.username += 's'; break;
			case SDLK_t:pEngine.username += 't'; break;
			case SDLK_u:pEngine.username += 'u'; break;
			case SDLK_v:pEngine.username += 'v'; break;
			case SDLK_w:pEngine.username += 'w'; break;
			case SDLK_x:pEngine.username += 'x'; break;
			case SDLK_y:pEngine.username += 'y'; break;
			case SDLK_z:pEngine.username += 'z'; break;
			case SDLK_1:pEngine.username += '1'; break;
			case SDLK_2:pEngine.username += '2'; break;
			case SDLK_3:pEngine.username += '3'; break;
			case SDLK_4:pEngine.username += '4'; break;
			case SDLK_5:pEngine.username += '5'; break;
			case SDLK_6:pEngine.username += '6'; break;
			case SDLK_7:pEngine.username += '7'; break;
			case SDLK_8:pEngine.username += '8'; break;
			case SDLK_9:pEngine.username += '9'; break;
			case SDLK_0:pEngine.username += '0'; break;
			case SDLK_RETURN:pEngine.entername = false; pEngine.switchToScore = true; pEngine.updateScoreFile(); break;
			case SDLK_BACKSPACE:pEngine.username = pEngine.username.substr(0, pEngine.username.length() - 1); break;
			}
		}
		else {
			switch (iKeyCode) {
			case SDLK_RETURN:pEngine.entername = false; pEngine.switchToScore = true; pEngine.updateScoreFile(); break;
			case SDLK_BACKSPACE:pEngine.username = pEngine.username.substr(0, pEngine.username.length() - 1); break;
			}
		}
	}
	
}

void EndState::virtSetUpForeground(GameEngine& pEngine) {

}

void EndState::virtSetUpMouseDown(GameEngine& pEngine, int iButton, int iX, int iY) {
	if (iButton == SDL_BUTTON_LEFT) {
		if (iX > 600 && iX < 780 && iY > 645 && iY < 667) {
			pEngine.playClickMusic();
			delete pEngine.m_pState;
			pEngine.m_pState = new StartState;
			pEngine.m_pState->applyState(pEngine);
		}
	}
}

