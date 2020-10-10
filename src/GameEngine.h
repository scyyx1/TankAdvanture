#pragma once
#include "header.h"
#include "AdvancedTileManager.h"
#include "CoordinateMapping.h"
#include "BaseEngine.h"
#include "BaseState.h"
#include "GameMainObject.h"
#include "DrawingFilters.h" 
#include <iostream>
using namespace std;
class GameEngine :
	public BaseEngine, public CoordinateMapping
{
public:
	GameEngine();
	~GameEngine();
	void virtSetupBackgroundBuffer();
	int virtInitialiseObjects();
	void virtMouseDown(int iButton, int iX, int iY);
	void virtDrawStringsUnderneath();
	friend ostream& operator<<(ostream& output, const GameEngine& engine);
	friend istream& operator>>(istream& input, GameEngine& engine);
	friend class EndState;
	friend class StartState;
	friend class PauseState;
	friend class RunningState;
	friend class SelectState;
	friend class HelpState;
protected:
	AdvancedTileManager tm;
	GameMainObject* mainObject;
	BaseState* m_pState;
	bool isEasy = false;
	bool isMedium = false;
	bool isDifficult = false;
	bool isLoad = false;
	bool isWin = false;
	bool isLose = true;
private:
	int score;
	string username;
	bool entername;
	bool switchToScore;
	Uint8 *wav_bullet_buffer;
	Uint8 *wav_background_buffer;
	Uint8 *wav_case_buffer;
	Uint8 *wav_door_buffer;
	Uint8 *wav_bottle_buffer;
	Uint8 *wav_dead_buffer;
	Uint8 *wav_click_buffer;
	Uint32 wav_bullet_length;
	Uint32 wav_case_length;
	Uint32 wav_click_length;
	Uint32 wav_door_length;
	Uint32 wav_dead_length;
	Uint32 wav_bottle_length;
	SDL_AudioDeviceID deviceId;
	SDL_AudioDeviceID bulletDevice;
	SDL_AudioDeviceID caseDevice;
	SDL_AudioDeviceID doorDevice;
	SDL_AudioDeviceID bottleDevice;
	SDL_AudioDeviceID deadDevice;
	SDL_AudioDeviceID clickDevice;
	DisplayableObject* deleteObject = NULL;
	int m_iOffset;
	DrawingSurface m_oTheRunningSurface;
	DrawingSurface m_oTheEndSurface1;
	DrawingSurface m_oTheEndSurface2;
	DrawingSurface m_oTheEndSurface3;
	DrawingSurface m_oTheEndSurface4;
	DrawingSurface m_oTheEndSurface5;
	int m_iCurrentSurfaceNumber;
	FilterPointsScaling m_filterScaling;
	FilterPointsTranslation m_filterTranslation;
	SimpleImage lives = ImageManager::loadImage("resources/tankUp.png", true);
	SimpleImage background = ImageManager::loadImage("resources/background.png", true);
	SimpleImage startElement = ImageManager::loadImage("resources/eleStart.png", true);
	SimpleImage selectElement = ImageManager::loadImage("resources/eleSelect.png", true);
	SimpleImage runningElement = ImageManager::loadImage("resources/eleRunning.png", true);
	SimpleImage endElement = ImageManager::loadImage("resources/eleEnd.png", true);
	SimpleImage helpElement = ImageManager::loadImage("resources/eleHelp.png", true);
	SimpleImage flash1 = ImageManager::loadImage("resources/flash1.png", true);
	SimpleImage flash2 = ImageManager::loadImage("resources/flash2.png", true);
	SimpleImage flash3 = ImageManager::loadImage("resources/flash3.png", true);
	SimpleImage flash4 = ImageManager::loadImage("resources/flash4.png", true);
	SimpleImage flash5 = ImageManager::loadImage("resources/flash5.png", true);
	SimpleImage blueBottle = ImageManager::loadImage("resources/blueBottle.png", true);
	SimpleImage introKey = ImageManager::loadImage("resources/introKey.png", true);
	SimpleImage introCase = ImageManager::loadImage("resources/introCase.png", true);
	SimpleImage introTank = ImageManager::loadImage("resources/introTank.png", true);
public:
	int getScore();
	void setScore(int num);
	void save();
	void virtKeyDown(int iKeyCode);
	AdvancedTileManager& getTileManager();
	void setEngineState(BaseState* state);
	void setUpMusic();
	void readScoreFile();
	void updateScoreFile();
	void closeAllMusic();
	bool mapCoordinates(double& x, double& y, const SimpleImage& image);
	void addBossObject(int iMapX, int iMapY, int health);
	void addBullet(int iStartX, int iStartY, int dir);
	bool checkObstacle(int value);
	void setIsWin(bool win);
	void setIsLose(bool lose);
	void virtMainLoopDoBeforeUpdate();
	void copyAllBackgroundBuffer();
	void virtCreateSurfaces();
	int virtInitialise();
	GameMainObject* getMainChar();
	void virtPreDraw();
	void virtMouseWheel(int x, int y, int which, int timestamp);
	void zoomOut();
	void zoomIn();
	void virtMainLoopDoAfterUpdate();
	void setDeleteObject(DisplayableObject* ob);
	void playBulletMusic();
	void addOpenCaseMusic();
	void initialiseEasyObjects();
	void playDoorOpenMusic();
	void playBottleMusic();
	void playDeadMusic();
	void initialiseMediumObjects();
	void initialiseDifficultObjects();
	void playClickMusic();
};
