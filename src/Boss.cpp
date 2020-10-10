#include "Boss.h"
#include "CollisionDetection.h"
#include <cmath>
#include <queue>

using namespace std;
Boss::Boss(GameEngine* pEngine, AdvancedTileManager* tm, int iMapX, int iMapY, int health) 
	:AutomatedObject(pEngine, 3, iMapX*20+350, iMapY*20+200, 20)
	, m_pTileManager(tm)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_dir(0)
	, lastAttackTime(pEngine->getModifiedTime())
	, srcMapX(pEngine->getMainChar()->getMapX())
	, srcMapY(pEngine->getMainChar()->getMapY())
	, queueSpace(10)
	, isVisited(false)
	, lastUpdatedTime(pEngine->getModifiedTime()),
	isHit(false),
	health(health)
{

	m_iCurrentScreenX = iMapX * 20 + 350;
	m_iCurrentScreenY = iMapY * 20 + 200;

}

Boss::~Boss() {

}


void Boss::setMovement(int iStartTime, int iEndTime, int iCurrentTime, int iStartX, int iStartY, int iEndX, int iEndY) {
	m_oMovement.setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMovement.calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.getX();
	m_iCurrentScreenY = m_oMovement.getY();
}

void Boss::virtDoUpdate(int iCurrentTime) {
	if (getEngine()->isPaused())
		return;

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
			srcMapX = mainChar->getMapX();
			srcMapY = mainChar->getMapY();
			int mapX = m_pTileManager->getMapXForScreenX(m_iCurrentScreenX);
			int mapY = m_pTileManager->getMapYForScreenY(m_iCurrentScreenY);
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
		if (detectDoorOpen()) {
			if (iCurrentTime - lastUpdatedTime > delay) {
				vector<Point> newRoute;
				bfs(Point(m_iMapX, m_iMapY), Point(srcMapX, srcMapY), newRoute);
				if (newRoute.size() != 0) {
					route.clear();
					route = newRoute;
				}
				if (route.size() < 10) {
					delay = 100 * route.size();
				}
				else {
					delay = 5000;
				}
				lastUpdatedTime = iCurrentTime;
			}
			if (route.size() == 0) {
				randomWalk(iCurrentTime);
			}
			else {
				int nextMapX = route[route.size() - 1].x;
				int nextMapY = route[route.size() - 1].y;
				route.pop_back();
				if (nextMapX == m_iMapX) {
					if (nextMapY > m_iMapY) {
						m_dir = 2;
					}
					else {
						m_dir = 0;
					}
				}
				else if (nextMapY == m_iMapY) {
					if (nextMapX > m_iMapX) {
						m_dir = 1;
					}
					else {
						m_dir = 3;
					}
				}
				m_iMapX = nextMapX;
				m_iMapY = nextMapY;
				m_oMovement.setup(m_iCurrentScreenX, m_iCurrentScreenY, nextMapX * 20 + 350, nextMapY * 20 + 200, iCurrentTime, iCurrentTime + 800 + rand() % 200);
			}
		}
		else {
			randomWalk(iCurrentTime);
		}

		

		
	}
	else {
		m_oMovement.calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMovement.getX();
		m_iCurrentScreenY = m_oMovement.getY();
	}

}

void Boss::virtDraw()
{
	if (!isVisible())
		return;
	if (animationFrame > 0) {
		if (health == 0) {
			dead.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
		}
		else {
			switch (m_dir) {
			case 0:
				bossUpHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 1:
				bossRightHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 2:
				bossDownHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
				break;
			case 3:
				bossLeftHit.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
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
			bossUp.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
			break;
		case 1:
			bossRight.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
			break;
		case 2:
			bossDown.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
			break;
		case 3:
			bossLeft.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
			break;
		default:
			break;
		}
	}
	
}

int Boss::getHealth() {
	return health;
}

void Boss::setIsHit(bool hit) {
	isHit = hit;
}

void Boss::bfs(Point& startP, Point endP, vector<Point>& route) {
	
	if (startP.x == endP.x && startP.y == endP.y) {
		route.push_back(startP);
		return;
	}
	Point** mark = new Point*[m_pTileManager->getMapWidth()];
	for (int i = 0; i < m_pTileManager->getMapWidth(); i++) {
		mark[i] = new Point[m_pTileManager->getMapHeight()];
	}
	bool findRoute = false;
	queue<Point> q;
	q.push(startP);
	mark[startP.x][startP.y] = startP;
	while (!q.empty()) {
		Point curPoint = q.front();
		q.pop();
		/*cout << "CurX: " << curPoint.x << " Y: " << curPoint.y << endl;
		cout << "EndX: " << endP.x << " Y: " << endP.y << endl;*/
		if (curPoint == endP) {
			findRoute = true;
			break;
		}
		for (int i = 0; i < 4; i++) {
			int mapX = curPoint.x + getXDiffForDirection(i);
			int mapY = curPoint.y + getYDiffForDirection(i);
			if ( m_pTileManager->getMapValue(mapX, mapY) != 1 && m_pTileManager->getMapValue(mapX, mapY) != 7 && in(mapX, mapY)) {
				if (mark[mapX][mapY] == Point()) {
					mark[mapX][mapY] = curPoint;
					q.push(Point(mapX, mapY));
				}
				
			}
		}
	}
	if (findRoute == true) {
		route.push_back(endP);
		int parentX = endP.x;
		int parentY = endP.y;
		int count = 0;
		while (!(mark[parentX][parentY] == startP)) {

			int curX = parentX;
			int curY = parentY;
			route.push_back(mark[parentX][parentY]);
			parentX = mark[curX][curY].x;
			parentY = mark[curX][curY].y;
		}
		//for (int i = route.size() - 1; i >= 0; i--) {
		//	cout << "X: " << route[i].x << " Y: " << route[i].y << endl;
		//}
	}
	else {
		cout << "Cannot find route" << endl;
	}
	for (int i = 0; i < m_pTileManager->getMapWidth(); i++) {
		delete mark[i];
	}
	delete mark;
}

bool Boss::in(int x1, int y1) {
	if (x1 >= 0 && x1 < 30 && y1 >= 0 && y1 <= 20) {
		return true;
	}
	else {
		return false;
	}
}

bool Boss::detectDoorOpen() {
	if (m_pTileManager->getMapValue(m_pTileManager->getDoor1X(), m_pTileManager->getDoor1Y()) == 22) {
		return true;
	}
	else {
		return false;
	}
}

void Boss::randomWalk(int iCurrentTime) {
	switch (rand()%4)
	{
	case 0: // Increase dir by 1
		m_dir = (m_dir + 1) % 4;
		break;
	case 1:

		m_dir = (m_dir + 3) % 4;

		break;
	}
	switch (m_pTileManager->getMapValue(
		m_iMapX + getXDiffForDirection(m_dir),
		m_iMapY + getYDiffForDirection(m_dir)))
	{
	case 5:
	case 0: // Passageway
		// Allow move - set up new movement now
		m_iMapX += getXDiffForDirection(m_dir);
		m_iMapY += getYDiffForDirection(m_dir);
		m_oMovement.setup(
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			m_iMapX * 20 + 350,
			m_iMapY * 20 + 200,
			iCurrentTime,
			iCurrentTime + 1000 + rand() % 200);
		break;
	default:
		m_dir = rand() % 4; // Rotate randomly
		break;
	}
}
