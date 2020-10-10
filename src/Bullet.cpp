#include "Bullet.h"
#include "CollisionDetection.h"
#include "Boss.h"
#include "Guard.h"
Bullet::Bullet(GameEngine* pEngine, AdvancedTileManager* tm, int dir, int iStartX, int iStartY) 
	:AutomatedObject(pEngine, 1, iStartX, iStartY, 6),
	m_pTileManager(tm),
	m_dir(dir)
{

}


Bullet::~Bullet() {

}

void Bullet::virtDoUpdate(int iCurrentTime) {
	if (getEngine()->isPaused())
		return;
	int iMapX = m_pTileManager->getMapXForScreenX(m_iCurrentScreenX);
	int iMapY = m_pTileManager->getMapYForScreenY(m_iCurrentScreenY);
	int mapValue = m_pTileManager->getMapValue(iMapX, iMapY);
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

		int iSizeOther = 10;
		int iSize = 3;

		if (CollisionDetection::checkRectangles(pObject->getXCentre() - iSizeOther, pObject->getXCentre() + iSizeOther,
			pObject->getYCentre() - iSizeOther, pObject->getYCentre() + iSizeOther,
			m_iCurrentScreenX, m_iCurrentScreenX + iSize * 2,
			m_iCurrentScreenY, m_iCurrentScreenY + iSize * 2)) {
			/*cout << "detect" << endl;
			cout << "Object xcentre: " << pObject->getXCentre() << " ycentre: " << pObject->getYCentre() << endl;
			cout << "x1l: " << pObject->getXCentre() - iSizeOther << "  x1r:" << pObject->getXCentre() + iSizeOther << endl;
			cout << "y1t: " << pObject->getYCentre() - iSizeOther << "  y1b:" << pObject->getYCentre() + iSizeOther << endl;
			cout << "Current x: " << m_iCurrentScreenX << " currenty: " << m_iCurrentScreenY << endl;
			cout << "x2l: " << m_iCurrentScreenX << "  x2r:" << m_iCurrentScreenX + iSize * 2 << endl;
			cout << "y2t: " << m_iCurrentScreenY << "  y2b:" << m_iCurrentScreenY + iSize * 2 << endl;*/

			
			Guard* guardEnemy = dynamic_cast<Guard*>(pObject);
			if (guardEnemy != NULL) {
				if (guardEnemy->getHealth() > 0) {
					guardEnemy->setIsHit(true);
					m_pEngine->setScore(m_pEngine->getScore() + 100);
				}
				m_pEngine->setDeleteObject(this);
				return;

			}

			Boss* boss = dynamic_cast<Boss*>(pObject);
			if (boss != NULL) {
				if (boss->getHealth() > 0) {
					boss->setIsHit(true);
					m_pEngine->setScore(m_pEngine->getScore() + 100);
				}
				else {
					//m_pEngine->deleteAutomatedObject(pObject);		
				}
				m_pEngine->setDeleteObject(this);
				return;
			}

			GameMainObject* so = dynamic_cast<GameMainObject*>(pObject);
			if (so != NULL) {
				if (so->getHealth() > 0) {
					so->setIsHit(true);
				}
				m_pEngine->setDeleteObject(this);
				return;
			}


		}
	}
	switch (m_dir) {
	case 0:
		if (!checkObstacle(mapValue)) {
			m_iCurrentScreenY--;
			redrawDisplay();
		}
		else {
			m_pEngine->setDeleteObject(this);
		}
		break;
	case 1:
		if (!checkObstacle(mapValue)) {
			m_iCurrentScreenX++;
			redrawDisplay();
		}
		else {
			m_pEngine->setDeleteObject(this);
		}
		break;
	case 2:
		if (!checkObstacle(mapValue)) {
			m_iCurrentScreenY++;
			redrawDisplay();
		}
		else {
			m_pEngine->setDeleteObject(this);
		}
		break;
	case 3:
		if (!checkObstacle(mapValue)) {
			m_iCurrentScreenX--;
			redrawDisplay();
		}
		else {
			m_pEngine->setDeleteObject(this);
		}
		break;
	}


}

void Bullet::virtDraw() {
	if (!isVisible())
		return;
	bullet.renderImage(m_pEngine->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
}

bool Bullet::checkObstacle(int value) {
	if (value != 7 && value != 1 && value != 3 && value != 4) {
		return false;
	}
	else {
		return true;
	}
}

int Bullet::getDir() {
	return m_dir;
}