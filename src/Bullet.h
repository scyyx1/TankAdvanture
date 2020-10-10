#pragma once
#include "AutomatedObject.h"
class Bullet :
	public AutomatedObject
{
public:
	Bullet(GameEngine* pEngine, AdvancedTileManager* tm, int dir, int iStartX, int iStartY);
	~Bullet();
	void virtDoUpdate(int iCurrentTime);
	void virtDraw();
	bool checkObstacle(int value);
	int getDir();
protected:
	AdvancedTileManager* m_pTileManager;
	int m_dir;
	int deadAnimation = 10;
	SimpleImage bullet = ImageManager::loadImage("resources/bullet.png", true);
};

