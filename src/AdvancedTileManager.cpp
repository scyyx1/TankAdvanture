#include  "header.h"
#include "AdvancedTileManager.h"
#include "GameEngine.h"
#include "ImageManager.h"
#include <ctime>


AdvancedTileManager::AdvancedTileManager()
	:TileManager(20, 20, 10, 10),
	door1X(24),
	door1Y(14),
	door2X(13),
	door2Y(14)
{

}


AdvancedTileManager::~AdvancedTileManager()
{
}

void AdvancedTileManager::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const {
	GameEngine* engine = dynamic_cast<GameEngine*>(pEngine);
	if (engine == NULL) {
		cout << "dynamic cast error" << endl;
		return;
	}
	int randomGround = rand() % 10;
	int randomBottle = rand() % 6;
	switch (getMapValue(iMapX, iMapY)) {
	case 0:
		if (randomGround == 0) {
			ground1.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, ground1.getWidth(), ground1.getHeight());
		}
		else {
			ground2.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, ground2.getWidth(), ground2.getHeight());
		}
		break;
	case 1:
		stone.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, stone.getWidth(), stone.getHeight());
		break;
	case 3:
		ground1.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, ground1.getWidth(), ground1.getHeight());
		stair.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, stair.getWidth(), stair.getHeight());
		break;
	case 4:
		ground1.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, ground1.getWidth(), ground1.getHeight());
		exit.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, exit.getWidth(), exit.getHeight());
		break;
	case 5:
		ground1.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, ground1.getWidth(), ground1.getHeight());
		switch (randomBottle) {
		case 0:
			blueBottle.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, blueBottle.getWidth(), blueBottle.getHeight());
			break;
		case 1:
			greenBottle.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, greenBottle.getWidth(), greenBottle.getHeight());
			break;
		case 2:
			orangeBottle.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, orangeBottle.getWidth(), orangeBottle.getHeight());
			break;
		case 3:
			purpleBottle.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, purpleBottle.getWidth(), purpleBottle.getHeight());
			break;
		case 4:
			redBottle.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, redBottle.getWidth(), redBottle.getHeight());
			break;
		case 5:
			yellowBottle.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, yellowBottle.getWidth(), yellowBottle.getHeight());
			break;

		}
		break;
	case 6:
		caseClosed.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, caseClosed.getWidth(), caseClosed.getHeight());
		break;
	case 7:
		ground1.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, ground1.getWidth(), ground1.getHeight());
		wall.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, wall.getWidth(), wall.getHeight());
		break;
	case 10:
		caseOpen.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, caseOpen.getWidth(), caseOpen.getHeight());
		break;
	case 20:
		key.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, key.getWidth(), key.getHeight());
		break;
	case 21:
		doorClosed.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, doorClosed.getWidth(), doorClosed.getHeight());
		break;
	case 22:
		doorOpen.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, doorOpen.getWidth(), doorOpen.getHeight());
		break;
	}



}

int AdvancedTileManager::getDoor1X()
{
	return door1X;
}


int AdvancedTileManager::getDoor1Y()
{
	return door1Y;
}
int AdvancedTileManager::getDoor2X()
{
	return door2X;
}

int AdvancedTileManager::getDoor2Y()
{
	return door2Y;
}


