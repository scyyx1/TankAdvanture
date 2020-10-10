#pragma once
#include "AutomatedObject.h"
class Guard :
	public AutomatedObject
{
public:
	Guard(GameEngine* pEngine, int iID, int iStartX, int iStartY, int iEndX, int iEndY, int dir, int iStartTime, int iCurrentTime, int iEndTime, int health);
	~Guard();
	void virtDoUpdate(int iCurrentTime) override;
	int getHealth();
	void setIsHit(bool hit);
	void virtDraw();
	int getStartX();
	int getEndX();
	int getStartY();
	int getEndY();
	int getInterval();
	int getiCurrentTime();
	int getDir();
	int getInitialTime();
private:
	MovementPosition m_oMovement;
	SimpleImage guardUp = ImageManager::loadImage("resources/guardUp.png", true);
	SimpleImage guardDown = ImageManager::loadImage("resources/guardDown.png", true);
	SimpleImage guardRight = ImageManager::loadImage("resources/guardRight.png", true);
	SimpleImage guardLeft = ImageManager::loadImage("resources/guardLeft.png", true);
	SimpleImage guardUpHit = ImageManager::loadImage("resources/guardUpHit.png", true);
	SimpleImage guardDownHit = ImageManager::loadImage("resources/guardDownHit.png", true);
	SimpleImage guardRightHit = ImageManager::loadImage("resources/guardRightHit.png", true);
	SimpleImage guardLeftHit = ImageManager::loadImage("resources/guardLeftHit.png", true);
	SimpleImage dead = ImageManager::loadImage("resources/dead.png", true);
	int lastAttackTime = 0;
	int interval;
	int animationFrame = 0;
	int health;
	bool isHit = false;
	int m_iMapStartX;
	int m_iMapStartY;
	int m_iMapEndX;
	int m_iMapEndY;
	int m_dir;
	int initialStartTime;
	int delay;
};