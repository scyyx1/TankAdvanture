#pragma once
#include "AutomatedObject.h"
class Boss :
	public AutomatedObject
{
	struct Point {
		int x;
		int y;
		Point(int x = -1, int y = -1)
			: x(x), y(y)
		{
		}
		Point& operator=(const Point& a)
		{
			x = a.x;
			y = a.y;
			return *this;
		}
		bool operator==(const Point& a) const
		{
			return (x == a.x && y == a.y);
		}
	} ;
public:
	Boss(GameEngine* pEngine, AdvancedTileManager* tm, int iMapX, int iStartMapY, int health);
	~Boss();
	void setMovement(int iStartTime, int iEndTime, int iCurrentTime, int iStartX, int iStartY, int iEndX, int iEndY);
	void virtDoUpdate(int iCurrentTime) override;
	int getXDiffForDirection(int iDir)
	{
		switch (iDir % 4)
		{
		case 0: return 0; // Up
		case 1: return 1; // Right
		case 2: return 0; // Down
		case 3: return -1; // Left
		default: return 0; // Can never happen
		}
	}

	int getYDiffForDirection(int iDir)
	{
		switch (iDir % 4)
		{
		case 0: return -1; // Up
		case 1: return 0; // Right
		case 2: return 1; // Down
		case 3: return 0; // Left
		default: return 0; // Can never happen
		}
	}

protected:
	MovementPosition m_oMovement;
	AdvancedTileManager* m_pTileManager;
	int m_iMapX;
	int m_iMapY;
	int m_dir;
	SimpleImage image;
	SimpleImage dead = ImageManager::loadImage("resources/dead.png", true);
	SimpleImage bossLeft = ImageManager::loadImage("resources/bossLeft.png", true);
	SimpleImage bossRight = ImageManager::loadImage("resources/bossRight.png", true);
	SimpleImage bossUp = ImageManager::loadImage("resources/bossUp.png", true);
	SimpleImage bossDown = ImageManager::loadImage("resources/bossDown.png", true);
	SimpleImage bossUpHit = ImageManager::loadImage("resources/bossUpHit.png", true);
	SimpleImage bossDownHit = ImageManager::loadImage("resources/bossDownHit.png", true);
	SimpleImage bossLeftHit = ImageManager::loadImage("resources/bossLeftHit.png", true);
	SimpleImage bossRightHit = ImageManager::loadImage("resources/bossRightHit.png", true);
	int animationFrame = 0;
	int health;
	bool isHit;
	int lastAttackTime;
	int lastUpdatedTime;
	int srcMapX;
	int srcMapY;
	vector<Point> route;
	int queueSpace;
	bool isVisited;
	int delay = 0;
public:
	void virtDraw();
	int getHealth();
	void setIsHit(bool hit);
	void bfs(Point& startP, Point endP, vector<Point>& shortestPath);
	bool in(int x1, int y1);
	bool detectDoorOpen();
	void randomWalk(int iCurrentTime);
	
};

