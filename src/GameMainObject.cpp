#include "GameEngine.h"
#include "GameMainObject.h"
#include "AdvancedTileManager.h"
#include "EndState.h"
#include "CollisionDetection.h"
#include "header.h"
#include "Bullet.h"
#include <iostream>
using namespace std;
class GameEngine;



GameMainObject::GameMainObject(GameEngine* pEngine, AdvancedTileManager* tm, int iMapX, int iMapY, int health, int dir)
	:DisplayableObject(pEngine),
	m_pEngine(pEngine),
	m_pTileManager(tm),
	m_iMapX(iMapX),
	m_iMapY(iMapY),
	m_dir(dir),
	hasEnemy(false),
	health(health),
	isHit(false)
{
	m_iDrawWidth = 20;
	m_iDrawHeight = 20;

	// Put item at specific coordinates
	m_iCurrentScreenX = iMapX * 20 + 350;
	m_iCurrentScreenY = iMapY * 20 + 200;
	setVisible(true);


}


GameMainObject::~GameMainObject()
{
}

void GameMainObject::virtDraw() {
	if (isVisible())
	{
		if (hitAnimation > 0) {
			if (health == 0) {
				dead.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
			}
			else {
				switch (m_dir) {
				case 0:
					tankUpHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
					break;
				case 1:
					tankRightHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
					break;
				case 2:
					tankDownHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
					break;
				case 3:
					tankLeftHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
					break;
				default:
					break;
				}
			}
			
			hitAnimation--;
		}
		else {
			switch (m_dir) {
			case 0:
				tankUp.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 1:
				tankRight.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 2:
				tankDown.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 3:
				tankLeft.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			default:
				break;
			}

		}

	}
}

void GameMainObject::virtDoUpdate(int iCurrentTime)
{
	if (getEngine()->isPaused())
		return;
	if (health == 0 &&  hitAnimation == 0) {
		m_pEngine->setIsLose(true);
		BaseState* curState = new EndState;
		m_pEngine->setEngineState(curState);
		curState->applyState(*m_pEngine);
		return;
	}
	else if (health == 0 && hitAnimation > 0) {
		redrawDisplay();
		return;
	}
	if (isHit) {
		health--;
		hitAnimation = 10;
		isHit = false;
		if (health == 0) {
			m_pEngine->playDeadMusic();
		}
	}
	m_iCurrentScreenX = m_iMapX * 20 + 350;
	m_iCurrentScreenY = m_iMapY * 20 + 200;

	// collision detection
	DisplayableObject* pObject;
	for (int iObjectId = 0;
		(pObject = m_pEngine->getDisplayableObject(iObjectId)
			) != NULL;
		iObjectId++)
	{
		if (pObject == this) // This is us, skip it
			continue;
		if (pObject == nullptr) // Object does not exist, skip it
			continue;		// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19

		int iSizeOther = 9;
		int iSize = 9;
		if (CollisionDetection::checkRectangles(pObject->getXCentre() - iSizeOther, pObject->getXCentre() + iSizeOther,
			pObject->getYCentre() - iSizeOther, pObject->getYCentre() + iSizeOther,
			m_iCurrentScreenX, m_iCurrentScreenX + iSize * 2,
			m_iCurrentScreenY, m_iCurrentScreenY + iSize * 2)) {
			Bullet* bullet = dynamic_cast<Bullet*>(pObject);
			if (bullet != NULL) {
				continue;
			}
			else {
				m_pEngine->playDeadMusic();
				health = 0;
				hitAnimation = 10;
				return;
			}
			
		}
	}
	if (m_iMapX == 3 && m_iMapY == 0) {
		m_pEngine->setIsWin(true);
		BaseState* curState = new EndState;
		m_pEngine->setEngineState(curState);
		curState->applyState(*m_pEngine);
		return;
	}

	if (m_pTileManager->getMapValue(m_iMapX, m_iMapY) == 6) {
		m_pEngine->addOpenCaseMusic();
		m_pTileManager->setAndRedrawMapValueAt(m_iMapX, m_iMapY, 10, m_pEngine, m_pEngine->getBackgroundSurface());
		if (m_iMapX == 28 && m_iMapY == 13) {
			m_pEngine->addBossObject(22, 12, 2);
		}
		else if (m_iMapX == 18 && m_iMapY == 2) {
			m_pEngine->addBossObject(11, 3, 2);
		}
		else if (m_iMapX == 17 && m_iMapY == 18) {
			m_pEngine->addBossObject(14, 7, 2);
		}
		else {
			m_pEngine->setScore(m_pEngine->getScore() + 50);
		}
	}

	if (m_pTileManager->getMapValue(m_iMapX, m_iMapY) == 5) {
		m_pEngine->playBottleMusic();
		m_pEngine->setScore(m_pEngine->getScore() + 1);
		m_pTileManager->setAndRedrawMapValueAt(m_iMapX, m_iMapY, 0, m_pEngine, m_pEngine->getBackgroundSurface());
	}
	
	if (m_pTileManager->getMapValue(m_iMapX, m_iMapY) == 20) {
		cout << "X: " << m_iMapX << " Y: " << m_iMapY << endl;
		m_pEngine->playDoorOpenMusic();
		if (m_iMapX == 16 && m_iMapY == 8) {
			m_pTileManager->setAndRedrawMapValueAt(m_pTileManager->getDoor1X(), m_pTileManager->getDoor1Y(), 22, m_pEngine, m_pEngine->getBackgroundSurface());
		}
		else if (m_iMapX == 10 && m_iMapY == 4) {
			
			m_pTileManager->setAndRedrawMapValueAt(m_pTileManager->getDoor2X(), m_pTileManager->getDoor2Y(), 22, m_pEngine, m_pEngine->getBackgroundSurface());
		}
		m_pTileManager->setAndRedrawMapValueAt(m_iMapX, m_iMapY, 0, m_pEngine, m_pEngine->getBackgroundSurface());
	}

	this->redrawDisplay();
}

void GameMainObject::virtKeyDown(int iKeyCode)
{
	if (getEngine()->isPaused())
		return;
	if (iKeyCode == SDLK_d) {
		m_dir = 1;
		int mapValue = m_pTileManager->getMapValue(m_iMapX + getXDiffForDirection(m_dir), m_iMapY + getYDiffForDirection(m_dir));
		if (!checkObstacle(mapValue)) {
			m_iMapX += 1;
		}
		
	}
	else if (iKeyCode == SDLK_a) {

		m_dir = 3;
		int mapValue = m_pTileManager->getMapValue(m_iMapX + getXDiffForDirection(m_dir), m_iMapY + getYDiffForDirection(m_dir));
		if (!checkObstacle(mapValue)) {
			m_iMapX -= 1;
		}
		
	}
	else if (iKeyCode == SDLK_w) {
		m_dir = 0;
		int mapValue = m_pTileManager->getMapValue(m_iMapX + getXDiffForDirection(m_dir), m_iMapY + getYDiffForDirection(m_dir));
		if (!checkObstacle(mapValue)) {
			m_iMapY -= 1;
		}
	}
	else if (iKeyCode == SDLK_s) {
		m_dir = 2;
		int mapValue = m_pTileManager->getMapValue(m_iMapX + getXDiffForDirection(m_dir), m_iMapY + getYDiffForDirection(m_dir));
		if (!checkObstacle(mapValue)) {
			m_iMapY += 1;
		}
	}
}


bool GameMainObject::checkObstacle(int value)
{
	if (value != 7 && value != 1 && value != 21 && value != 3) {
		return false;
	}
	else {
		return true;
	}
}


int GameMainObject::getMapX()
{

	return m_iMapX;
}


int GameMainObject::getMapY()
{

	return m_iMapY;
}


int GameMainObject::getDir()
{

	return m_dir;
}


void GameMainObject::setIsHit(bool hit) {
	isHit = hit;
}

int GameMainObject::getHealth() {
	return health;
}