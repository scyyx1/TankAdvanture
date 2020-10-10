#pragma once
#include "header.h"
#include "AdvancedTileManager.h"
#include "DisplayableObject.h"
class GameMainObject :
	public DisplayableObject
{
public:
	GameMainObject(GameEngine* pEngine, AdvancedTileManager* tm, int iMapX, int iMapY, int health, int dir);
	~GameMainObject();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
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
	AdvancedTileManager* m_pTileManager;
	int m_iMapX;
	int m_iMapY;
	int m_dir;
	GameEngine* m_pEngine;
	SimpleImage tankUp = ImageManager::loadImage("resources/tankUp.png", true);
	SimpleImage tankDown = ImageManager::loadImage("resources/tankDown.png", true);
	SimpleImage tankLeft = ImageManager::loadImage("resources/tankLeft.png", true);
	SimpleImage tankRight = ImageManager::loadImage("resources/tankRight.png", true);
	SimpleImage tankUpHit = ImageManager::loadImage("resources/tankUpHit.png", true);
	SimpleImage tankDownHit = ImageManager::loadImage("resources/tankDownHit.png", true);
	SimpleImage tankLeftHit = ImageManager::loadImage("resources/tankLeftHit.png", true);
	SimpleImage tankRightHit = ImageManager::loadImage("resources/tankRightHit.png", true);
	SimpleImage dead = ImageManager::loadImage("resources/dead.png", true);
	bool hasEnemy;
	bool isHit;
	int health;
	int hitAnimation = 0;
public:
	void virtKeyDown(int iKeyCode);
	bool checkObstacle(int value);
	int getMapX();
	int getMapY();
	int getDir();
	void setIsHit(bool hit);
	int getHealth();
};
