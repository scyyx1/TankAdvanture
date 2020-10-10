#pragma once

#include "TileManager.h"
class AdvancedTileManager :
	public TileManager
{
public:
	AdvancedTileManager();
	~AdvancedTileManager();
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
protected:
	SimpleImage wall = ImageManager::loadImage("resources/tree.png", true);
	SimpleImage ground1 = ImageManager::loadImage("resources/grass.png", true);
	SimpleImage ground2 = ImageManager::loadImage("resources/grass2.png", true);
	SimpleImage stone = ImageManager::loadImage("resources/stone.png", true);
	SimpleImage blueBottle = ImageManager::loadImage("resources/blue.png", true);
	SimpleImage greenBottle = ImageManager::loadImage("resources/green.png", true);
	SimpleImage orangeBottle = ImageManager::loadImage("resources/orange.png", true);
	SimpleImage purpleBottle = ImageManager::loadImage("resources/purple.png", true);
	SimpleImage redBottle = ImageManager::loadImage("resources/red.png", true);
	SimpleImage yellowBottle = ImageManager::loadImage("resources/yellow.png", true);
	SimpleImage key = ImageManager::loadImage("resources/key.png", true);
	SimpleImage caseClosed = ImageManager::loadImage("resources/caseClosed.png", true);
	SimpleImage caseOpen = ImageManager::loadImage("resources/caseOpen.png", true);
	SimpleImage doorClosed = ImageManager::loadImage("resources/doorClosed.png", true);
	SimpleImage doorOpen = ImageManager::loadImage("resources/doorOpen.png", true);
	SimpleImage stair = ImageManager::loadImage("resources/stair.png", true);
	SimpleImage exit = ImageManager::loadImage("resources/exit.png", true);
	int door1X;
	int door1Y;
	int door2X;
	int door2Y;
public:
	int getDoor1X();
	int getDoor1Y();
	int getDoor2X();
	int getDoor2Y();
};
