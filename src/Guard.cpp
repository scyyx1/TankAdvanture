#include "Guard.h"

Guard::Guard(GameEngine* pEngine, int iID, int iMapStartX, int iMapStartY, int iMapEndX, int iMapEndY, int dir, int iStartTime, int iCurrentTime, int iEndTime, int health)
	:AutomatedObject(pEngine, iID, iMapStartX * 20 + 350, iMapStartY * 20 + 200, 20),
	health(health),
	m_iMapStartX(iMapStartX), m_iMapStartY(iMapStartY), m_iMapEndX(iMapEndX), m_iMapEndY(iMapEndY),
	interval(iEndTime - iStartTime),
	m_dir(dir),
	initialStartTime(iStartTime),
	delay(iCurrentTime - iStartTime)
{
	switch (m_dir) {
	case 0:
		if (iMapEndY > iMapStartY) {
			int temp = iMapStartY;
			iMapStartY = iMapEndY;
			iMapEndY = temp;
		}
		break;
	case 1:
		if (iMapEndX < iMapStartX) {
			int temp = iMapEndX;
			iMapEndX = iMapStartX;
			iMapStartX = temp;
			break;
		}
	case 2:
		if (iMapEndY < iMapStartY) {
			int temp = iMapStartY;
			iMapStartY = iMapEndY;
			iMapEndY = temp;
		}
		break;
	case 3:
		if (iMapEndX > iMapStartX) {
			int temp = iMapStartX;
			iMapStartX = iMapEndX;
			iMapEndX = temp;
		}
		break;
	}
	//cout << "Guard StartY: " << iMapStartY << " EndY: " << iMapEndY << endl;
	//cout << "iStartTime: " << iStartTime << " iEndTime: " << iEndTime << " iCurrentTime: " << iCurrentTime << endl;
	m_oMovement.setup(iMapStartX * 20 + 350, iMapStartY * 20 + 200, iMapEndX * 20 + 350, iMapEndY * 20 + 200, iStartTime, iEndTime);
	m_oMovement.calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.getX();
	m_iCurrentScreenY = m_oMovement.getY();
	//cout << "Guard X: " << m_iCurrentScreenX << " Y: " << m_iCurrentScreenY << endl;

}

Guard::~Guard() {

}

void Guard::virtDoUpdate(int iCurrentTime) {
	if (getEngine()->isPaused())
		return;
	iCurrentTime = iCurrentTime + delay;

	if (health == 0 && animationFrame > 0) {
		redrawDisplay();
		return;
	}
	if (health == 0 && animationFrame == 0) {
		m_pEngine->setDeleteObject(this);
		return;
	}
	if (isHit) {
		health--;
		animationFrame = 10;
		isHit = false;
		if (health == 0) {
			m_pEngine->playDeadMusic();
		}
	}

	// fire bullet
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
		GameMainObject* mainChar = dynamic_cast<GameMainObject*>(pObject);
		if (mainChar != NULL) {
			int iSizeOther = 9;
			int iSize = 9;
			int srcMapX = mainChar->getMapX();
			int srcMapY = mainChar->getMapY();
			int mapX = m_pEngine->getTileManager().getMapXForScreenX(m_iCurrentScreenX);
			int mapY = m_pEngine->getTileManager().getMapYForScreenY(m_iCurrentScreenY);
			switch (m_dir) {
			case 0:
				if (mapX == srcMapX && mapY > srcMapY) {
					if (mapY - srcMapY < 6 && iCurrentTime - lastAttackTime > 1000) {
						m_pEngine->addBullet(m_iCurrentScreenX, m_iCurrentScreenY, m_dir);
						lastAttackTime = iCurrentTime;
					}
				}
				break;
			case 1:
				if (mapY == srcMapY && srcMapX > mapX) {
					if (srcMapX - mapX < 6 && (iCurrentTime - lastAttackTime) > 1000) {
						m_pEngine->addBullet(m_iCurrentScreenX, m_iCurrentScreenY, m_dir);
						lastAttackTime = iCurrentTime;
					}
				}
				break;
			case 2:
				if (mapX == srcMapX && srcMapY > mapY) {
					if (srcMapY - mapY < 6 && (iCurrentTime - lastAttackTime) > 1000) {
						m_pEngine->addBullet(m_iCurrentScreenX, m_iCurrentScreenY, m_dir);
						lastAttackTime = iCurrentTime;
					}
				}
				break;
			case 3:
				if (mapY == srcMapY && mapX > srcMapX) {
					if (mapX - srcMapX < 6 && (iCurrentTime - lastAttackTime) > 1000) {
						m_pEngine->addBullet(m_iCurrentScreenX, m_iCurrentScreenY, m_dir);
						lastAttackTime = iCurrentTime;
					}
				}
				break;
			}

		}
	}
	if (m_oMovement.hasMovementFinished(iCurrentTime)) {
		switch (m_dir) {
		case 0:
			m_dir = 2;
			break;
		case 1:
			m_dir = 3;
			break;
		case 2:
			m_dir = 0;
			break;
		case 3:
			m_dir = 1;
			break;
		}
		m_oMovement.reverse();
		m_oMovement.calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMovement.getX();
		m_iCurrentScreenY = m_oMovement.getY();
		redrawDisplay();
	}
	else {
		m_oMovement.calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMovement.getX();
		m_iCurrentScreenY = m_oMovement.getY();
		redrawDisplay();
	}
}
void Guard::virtDraw() {
	if (isVisible())
	{
		if (animationFrame > 0) {
			if (health == 0) {
				dead.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
			}
			else {
				switch (m_dir) {
				case 0:
					guardUpHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
					break;
				case 1:
					guardRightHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
					break;
				case 2:
					guardDownHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
					break;
				case 3:
					guardLeftHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
					break;
				default:
					break;
			}
			}
			animationFrame--;
		}
		else {
			switch (m_dir) {
			case 0:
				guardUp.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 1:
				guardRight.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 2:
				guardDown.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 3:
				guardLeft.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			default:
				break;
			}

		}

	}
}
int Guard::getHealth() {
	return health;
}

void Guard::setIsHit(bool hit) {
	isHit = hit;
}

int Guard::getStartX() {
	return m_iMapStartX;
}
int Guard::getEndX() {
	return m_iMapEndX;
}
int Guard::getStartY() {
	return m_iMapStartY;
}
int Guard::getEndY() {
	return m_iMapEndY;
}
int Guard::getInterval() {
	return interval;
}
int Guard::getiCurrentTime() {
	return m_pEngine->getModifiedTime();
}
int Guard::getDir() {
	return m_dir;
}
int Guard::getInitialTime() {
	return initialStartTime;
}

