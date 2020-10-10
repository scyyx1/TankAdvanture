#include "GameEngine.h"
#include "GameMainObject.h"
#include "Bullet.h"
#include "Boss.h"
#include "Guard.h"
#include "SimpleImage.h"
#include "header.h"
#include "AutomatedObject.h"
#include "AdvancedTileManager.h"
#include "MappableImageObject.h"
#include "StartState.h"
#include "RunningState.h"
#include "HelpState.h"
#include "PauseState.h"
#include "SelectState.h"
#include <fstream>
#include <iostream>
#include<string>
#include<SDL_audio.h>



using namespace std;
GameEngine::GameEngine()
	:m_pState(new StartState),
	username(" "),
	entername(false),
	switchToScore(false),
	score(0),
	m_iOffset(0),
	m_oTheRunningSurface(this),
	m_oTheEndSurface1(this),
	m_oTheEndSurface2(this),
	m_oTheEndSurface3(this),
	m_oTheEndSurface4(this),
	m_oTheEndSurface5(this),
	m_iCurrentSurfaceNumber(0),
	m_filterScaling(0, 0, this),
	m_filterTranslation(0, 0, &m_filterScaling)
{
}


GameEngine::~GameEngine()
{
	delete m_pState;
}




void GameEngine::virtSetupBackgroundBuffer()
{

	m_pState->virtSetUpEngine(*this);

}



int GameEngine::virtInitialiseObjects()
{
	drawableObjectsChanged();

	destroyOldObjects(true);
	if (isEasy) {
		initialiseEasyObjects();
	}
	else if (isMedium) {
		initialiseMediumObjects();
	}
	else if (isDifficult) {
		initialiseDifficultObjects();
	}
	else if (isLoad) {
		fstream file;
		file.open("data.txt");
		if (!file) {
			perror("open file error");
		}
		else {
			file >> *this;
			cout << "Successfully loaded" << endl;
		}
		file.close();

	}

	setAllObjectsVisible(false);
	
	notifyObjectsAboutKeys(true);


	return 0;
}

void GameEngine::initialiseEasyObjects()
{
	GameMainObject* so = new GameMainObject(this, &tm, 20, 19, 3, 0);
	mainObject = so;
	appendObjectToArray(so);

	MappableImageObject* ob = new MappableImageObject(this, 50, 50, this, "resources/logo.png", true);
	appendObjectToArray(ob);

	Guard* guard = new Guard(this, 2, 19, 9, 19, 12, 2, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 4200, 2);
	appendObjectToArray(guard);
	Guard* guard1 = new Guard(this, 2, 11, 5, 11, 9, 2, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 5600, 2);
	appendObjectToArray(guard1);
	Guard* guard2 = new Guard(this, 2, 3, 2, 6, 2, 1, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 4200, 2);
	appendObjectToArray(guard2);
	addBossObject(12, 5, 2);
	addBossObject(25, 4, 2);
}

void GameEngine::initialiseMediumObjects()
{
	GameMainObject* so = new GameMainObject(this, &tm, 20, 19, 3, 0);
	mainObject = so;
	appendObjectToArray(so);

	MappableImageObject* ob = new MappableImageObject(this, 50, 50, this, "resources/logo.png", true);
	appendObjectToArray(ob);

	Guard* guard = new Guard(this, 2, 19, 9, 19, 12, 2, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 3000, 3);
	appendObjectToArray(guard);
	Guard* guard1 = new Guard(this, 2, 11, 5, 11, 9, 2, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 4000, 3);
	appendObjectToArray(guard1);
	Guard* guard2 = new Guard(this, 2, 3, 2, 6, 2, 1, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 3000, 3);
	appendObjectToArray(guard2);
	Guard* guard3 = new Guard(this, 2, 2, 15, 2, 9, 0, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 6000, 3);
	appendObjectToArray(guard3);
	Guard* guard4 = new Guard(this, 2, 9, 1, 15, 1, 1, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 6000, 3);
	appendObjectToArray(guard4);
	addBossObject(12, 5, 3);
	addBossObject(3, 1, 4);
	addBossObject(25, 4, 3);
}

void GameEngine::initialiseDifficultObjects()
{
	GameMainObject* so = new GameMainObject(this, &tm, 20, 19, 3, 0);
	mainObject = so;
	appendObjectToArray(so);

	MappableImageObject* ob = new MappableImageObject(this, 50, 50, this, "resources/logo.png", true);
	appendObjectToArray(ob);

	Guard* guard = new Guard(this, 2, 19, 9, 19, 12, 2, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 2400, 4);
	appendObjectToArray(guard);
	Guard* guard1 = new Guard(this, 2, 11, 5, 11, 9, 2, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 3200, 4);
	appendObjectToArray(guard1);
	Guard* guard2 = new Guard(this, 2, 3, 2, 6, 2, 1, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 2400, 4);
	appendObjectToArray(guard2);
	Guard* guard3 = new Guard(this, 2, 2, 15, 2, 9, 0, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 4800, 4);
	appendObjectToArray(guard3);
	Guard* guard4 = new Guard(this, 2, 9, 1, 15, 1, 1, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 4800, 4);
	appendObjectToArray(guard4);
	Guard* guard5 = new Guard(this, 2, 19, 1, 23, 1, 1, this->getModifiedTime(), this->getModifiedTime(), this->getModifiedTime() + 3200, 4);
	appendObjectToArray(guard5);
	addBossObject(12, 5, 4);
	addBossObject(25, 4, 4);
	addBossObject(3, 1, 4);
	addBossObject(8, 18, 4);
}


void GameEngine::virtMouseDown(int iButton, int iX, int iY)
{

	m_pState->virtSetUpMouseDown(*this, iButton, iX, iY);
}


void GameEngine::virtDrawStringsUnderneath()
{
	m_pState->virtDrawLabelText(*this);
}



int GameEngine::getScore() {
	return score;
}

void GameEngine::setScore(int num)
{
	score = num;
	// TODO: Add your implementation code here.

}


void GameEngine::save()
{
	fstream file;
	file.open("data.txt");
	if (!file) {
		perror("open file error");
		return;
	}
	else {
		file << *this;
		cout << "Successfully saved" << endl;
	}
	file.close();


}

ostream& operator<<(ostream& output, const GameEngine& engine)
{
	if (engine.isEasy) {
		output << "Easy" << endl;
	}
	else if (engine.isMedium) {
		output << "Medium" << endl;
	}
	else if (engine.isDifficult) {
		output << "Difficult" << endl;
	}
	output << engine.score<<endl;
	output << engine.getContentCount() << endl;
	for (int i = 0; i < engine.getContentCount(); i++) {
		DisplayableObject* object = engine.getDisplayableObject(i);
		GameMainObject* mainChar = dynamic_cast<GameMainObject*>(object);
		if (mainChar != NULL) {
			output << "MainChar" << endl;
			output << mainChar->getXCentre() << endl;
			output << mainChar->getYCentre() << endl;
			output << mainChar->getHealth() << endl;
			output << mainChar->getDir() << endl;
			continue;
		}
		Boss *boss = dynamic_cast<Boss*>(object);
		if (boss != NULL) {
			output << "Boss" << endl;
			output << boss->getXCentre() << endl;
			output << boss->getYCentre() << endl;
			output << boss->getHealth() << endl;
			continue;
		}
		Guard* guard = dynamic_cast<Guard*>(object);
		if (guard != NULL) {
			output << "Guard" << endl;
			output << guard->getStartX() << endl;
			output << guard->getEndX() <<endl;
			output << guard->getStartY() << endl;
			output << guard->getEndY() << endl;
			output << guard->getInterval() << endl;
			output << guard->getInitialTime() << endl;
			output << guard->getiCurrentTime() << endl;
			output << guard->getDir() << endl;
			output << guard->getHealth() << endl;
			continue;
		}
		MappableImageObject* mapObject = dynamic_cast<MappableImageObject*>(object);
		if (mapObject != NULL) {
			output << "MapObject" << endl;
			output << mapObject->getDrawHeight() << endl;
			output << mapObject->getDrawWidth() << endl;
			output << engine.getDisplayableObject(i)->getXCentre() << endl;
			output << engine.getDisplayableObject(i)->getYCentre() << endl;
			continue;
		}
		Bullet* bullet = dynamic_cast<Bullet*>(object);
		if (bullet != NULL) {
			output << "Bullet" << endl;
			output << bullet->getDir() << endl;
			output << bullet->getXCentre() << endl;
			output << bullet->getYCentre() << endl;
		}

	}
	int mapHeight = engine.tm.getMapHeight();
	int mapWidth = engine.tm.getMapWidth();
	for (int j = 0; j < mapHeight; j++) {
		for (int i = 0; i < mapWidth; i++) {
			output << engine.tm.getMapValue(i, j)<<" ";
		}
		output << endl;
	}
	/*for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			output << engine.tm.getMapValue(i, j)<<" ";
		}
		output << endl;
	}*/
	return output;
}
istream& operator>>(istream& input, GameEngine& engine) {
	string level;
	input >> level;
	const char *s = level.c_str();
	if (strcmp(s, "Easy") == 0) {
		engine.isEasy = true;
	}
	else if (strcmp(s, "Medium") == 0) {
		engine.isMedium = true;
	}
	else if (strcmp(s, "Difficult") == 0) {
		engine.isDifficult = true;
	}
	input >> engine.score;
	int totalObject = 0;
	int screenX = 0;
	int screenY = 0;
	int health = 0;
	input >> totalObject;
	//cout << "total Object: " << totalObject<<endl;
	for (int i = 0; i < totalObject; i++) {
		string objType;
		input >> objType;
		const char *cstr = objType.c_str();
		if (strcmp(cstr, "Boss") == 0) {
			input >> screenX;
			input >> screenY;
			input >> health;
			int mapX = engine.tm.getMapXForScreenX(screenX);
			int mapY = engine.tm.getMapYForScreenY(screenY);
			//cout << "mapX: " << mapX << " MapY: " << mapY << endl;
			engine.addBossObject(mapX, mapY,  health);
		}
		else if (strcmp(cstr, "MainChar") == 0) {
			input >> screenX;
			input >> screenY;
			input >> health;
			int dir = 0;
			input >> dir;
			int mapX = engine.tm.getMapXForScreenX(screenX);
			int mapY = engine.tm.getMapYForScreenY(screenY);
			GameMainObject* object = new GameMainObject(&engine, &engine.tm, mapX, mapY, health, dir);
			engine.mainObject = object;
			engine.appendObjectToArray(object);
		}
		else if (strcmp(cstr, "MapObject") == 0) {
			int width = 0;
			int height = 0;
			input >> height;
			input >> width;
			input >> screenX;
			input >> screenY;
			MappableImageObject* mapObject = new MappableImageObject(&engine, screenX - width / 2, screenY - height / 2, &engine, "resources/logo.png", true);
			engine.appendObjectToArray(mapObject);
		}
		else if (strcmp(cstr, "Guard") == 0) {
			int iStartX = 0;
			int iEndX = 0;
			int iStartY = 0;
			int iEndY = 0;
			input >> iStartX;
			input >> iEndX;
			input >> iStartY;
			input >> iEndY;
			int interval = 0;
			int dir = 0;
			int initialTime = 0;
			int iCurrentTime = 0;
			input >> interval;
			input >> initialTime;
			input >> iCurrentTime;
			input >> dir;
			input >> health;
			int iStartTime = engine.getModifiedTime();
			iCurrentTime = iStartTime + ((iCurrentTime - initialTime) % interval);
			//cout << "iStartTime: " << iStartTime << endl;
			//cout << "iCurrentTime: " << iCurrentTime << endl;
			Guard* guard = new Guard(&engine, 1, iStartX, iStartY, iEndX, iEndY, dir, iStartTime, iCurrentTime, iStartTime + interval, health);
			engine.appendObjectToArray(guard);
		}
		else if (strcmp(cstr, "Bullet") == 0) {
			int dir = 0;
			input >> dir;
			input >> screenX;
			input >> screenY;
			engine.addBullet(screenX, screenY, dir);
			
		}
	}
	int mapHeight = engine.tm.getMapHeight();
	int mapWidth = engine.tm.getMapWidth();
	int mapValue = 0;

	for (int j = 0; j < mapHeight; j++) {
		for (int i = 0; i < mapWidth; i++) {
			input >> mapValue;
			engine.tm.setMapValue(i, j, mapValue);
		}
	}

	return input;
}


void GameEngine::virtKeyDown(int iKeyCode)
{
	
	m_pState->virtSetUpKeyboard(*this, iKeyCode);

}




AdvancedTileManager& GameEngine::getTileManager()
{
	// TODO: Add your implementation code here.
	// TODO: insert return statement here
	return tm;
}




void GameEngine::setEngineState(BaseState* state)
{
	m_pState = state;
	// TODO: Add your implementation code here.
}



void GameEngine::setUpMusic()
{
	SDL_AudioSpec wav_spec;
	Uint32 wav_length;
	SDL_Init(SDL_INIT_AUDIO);
	if (SDL_LoadWAV("resources/background.wav", &wav_spec, &wav_background_buffer, &wav_length))
	{
		deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
		cout << "finish set up music" << endl;
		if (deviceId)
		{
			int success = SDL_QueueAudio(deviceId, wav_background_buffer, wav_length);
			SDL_PauseAudioDevice(deviceId, 0);
			

		}
		else
			SDL_ShowSimpleMessageBox(0, "Error", "Audio driver failed to initialize", NULL);

	}


	SDL_AudioSpec wav_bullet_spec;
	if (SDL_LoadWAV("resources/bullet.wav", &wav_bullet_spec, &wav_bullet_buffer, &wav_bullet_length))
	{
		bulletDevice = SDL_OpenAudioDevice(NULL, 0, &wav_bullet_spec, NULL, 0);
	}

	SDL_AudioSpec wav_case_spec;
	if (SDL_LoadWAV("resources/openCase.wav", &wav_case_spec, &wav_case_buffer, &wav_case_length)) {
		caseDevice = SDL_OpenAudioDevice(NULL, 0, &wav_case_spec, NULL, 0);
	}

	SDL_AudioSpec wav_door_spec;
	if (SDL_LoadWAV("resources/doorOpen.wav", &wav_door_spec, &wav_door_buffer, &wav_door_length)) {
		doorDevice = SDL_OpenAudioDevice(NULL, 0, &wav_door_spec, NULL, 0);
	}

	SDL_AudioSpec wav_dead_spec;
	if (SDL_LoadWAV("resources/dead.wav", &wav_dead_spec, &wav_dead_buffer, &wav_dead_length)) {
		deadDevice = SDL_OpenAudioDevice(NULL, 0, &wav_dead_spec, NULL, 0);
	}
	SDL_AudioSpec wav_bottle_spec;
	if (SDL_LoadWAV("resources/bottle.wav", &wav_bottle_spec, &wav_bottle_buffer, &wav_bottle_length)) {
		bottleDevice = SDL_OpenAudioDevice(NULL, 0, &wav_bottle_spec, NULL, 0);
	}
	SDL_AudioSpec wav_click_spec;
	if (SDL_LoadWAV("resources/click.wav", &wav_click_spec, &wav_click_buffer, &wav_click_length)) {
		clickDevice = SDL_OpenAudioDevice(NULL, 0, &wav_click_spec, NULL, 0);
	}
}



void GameEngine::readScoreFile()
{
	fstream file;
	file.open("score.txt");
	if (!file) {
		perror("open file error");
		return;
	}
	else {
		string string;
		int y = 0;
		int count = 0;
		lockForegroundForDrawing();
		while (getline(file, string)) {
			char * str = const_cast<char*>(string.c_str());
			drawForegroundString(430, 200 + y, str, 0xffffff, NULL);
			y += 50;
			count++;
			if (count == 10) {
				break;
			}
		}
		unlockForegroundForDrawing();
		redrawDisplay();
	}
	file.close();
	// TODO: Add your implementation code here.
}


void GameEngine::updateScoreFile()
{
	fstream file;
	file.open("score.txt", std::ios::app);
	if (!file) {
		perror("open file error");
		return;
	}
	else {
		if (isMedium) {
			score = 2 * score;
		}
		else if (isDifficult) {
			score = 3 * score;
		}
		file << "\n" << username << " " << score;
		cout << username << endl;
	}
	file.close();
}


void GameEngine::closeAllMusic()
{
	SDL_CloseAudioDevice(deviceId);
	SDL_CloseAudioDevice(bulletDevice);
	SDL_CloseAudioDevice(caseDevice);
	SDL_CloseAudioDevice(doorDevice);
	SDL_CloseAudioDevice(deadDevice);
	SDL_CloseAudioDevice(bottleDevice);
	SDL_CloseAudioDevice(clickDevice);

	if (wav_background_buffer != NULL) {
		SDL_FreeWAV(wav_background_buffer);
	}
	if (wav_bullet_buffer != NULL) {
		SDL_FreeWAV(wav_bullet_buffer);
	}
	if (wav_bottle_buffer != NULL) {
		SDL_FreeWAV(wav_bottle_buffer);
	}
	if (wav_case_buffer != NULL) {
		SDL_FreeWAV(wav_case_buffer);
	}
	if (wav_click_buffer != NULL) {
		SDL_FreeWAV(wav_click_buffer);
	}
	if (wav_door_buffer != NULL) {
		SDL_FreeWAV(wav_door_buffer);
	}
	if (wav_dead_buffer != NULL) {
		SDL_FreeWAV(wav_dead_buffer);
	}
	

}


bool GameEngine::mapCoordinates(double& x, double& y, const SimpleImage& image)
{
	int iOffset = getModifiedTime() / 10;

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;


	// Shift offset to the centre of the image, so we can rotate around centre
	x -= image.getWidth() / 2;
	y -= image.getHeight() / 2;

	// Rotate it
	double dAngle = atan(y / (x + 0.0001));
	if (x < 0)
		dAngle += M_PI;
	double hyp = ::sqrt(x*x + y * y);
	dAngle -= (double)iOffset / 100;

	x = hyp * ::cos(dAngle);
	y = hyp * ::sin(dAngle);

	// Shift offset back to the corner
	x += image.getWidth() / 2;
	y += image.getHeight() / 2;

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	return true;
}

void GameEngine::addBossObject(int iMapX, int iMapY,int health)
{

	appendObjectToArray(new Boss(this, &tm, iMapX, iMapY, health));

}



void GameEngine::addBullet(int iStartX, int iStartY, int dir)
{
	switch (dir) {
	case 0:
		appendObjectToArray(new Bullet(this, &tm, dir, iStartX + 7, iStartY - 15));
		break;
	case 1:
		appendObjectToArray(new Bullet(this, &tm, dir, iStartX + 30, iStartY + 7));
		break;
	case 2:
		appendObjectToArray(new Bullet(this, &tm, dir, iStartX + 7, iStartY + 30));
		break;
	case 3:
		appendObjectToArray(new Bullet(this, &tm, dir, iStartX - 15, iStartY + 7));
		break;
	}

}



bool GameEngine::checkObstacle(int value)
{
	cout << "Current Value: " << value << endl;
	if (value != 7 && value != 1) {
		return false;
	}
	else {
		return true;
	}
}





void GameEngine::virtMainLoopDoBeforeUpdate()
{

	if (m_iCurrentSurfaceNumber == 0) {
		m_pBackgroundSurface = &m_oTheBackgroundSurface;
		m_iOffset = (m_iOffset + 1) % getWindowHeight();
	}
	else if (m_iCurrentSurfaceNumber == 1) {
		m_pBackgroundSurface = &m_oTheRunningSurface;
		m_iOffset = 0;
	}
	else if (m_iCurrentSurfaceNumber == 2) {
		m_pBackgroundSurface = &m_oTheEndSurface1;
		m_iOffset = 0;
	}
	else if (m_iCurrentSurfaceNumber == 3) {
		m_pBackgroundSurface = &m_oTheEndSurface2;
		m_iOffset = 0;
	}
	else if (m_iCurrentSurfaceNumber == 4) {
		m_pBackgroundSurface = &m_oTheEndSurface3;
		m_iOffset = 0;
	}
	else if (m_iCurrentSurfaceNumber == 5) {
		m_pBackgroundSurface = &m_oTheEndSurface4;
		m_iOffset = 0;
	}
	else if (m_iCurrentSurfaceNumber == 6) {
		m_pBackgroundSurface = &m_oTheEndSurface5;
		m_iOffset = 0;
	}
	if (m_iCurrentSurfaceNumber != 0 && m_iCurrentSurfaceNumber != 1) {
		m_iCurrentSurfaceNumber = (m_iCurrentSurfaceNumber + 1) % 5 + 2;
	}
	this->redrawDisplay();
}


void GameEngine::copyAllBackgroundBuffer()
{
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, m_iOffset);
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - m_iOffset, getWindowWidth(), getWindowHeight(), 0, m_iOffset - getWindowHeight());
}


void GameEngine::virtCreateSurfaces()
{
	BaseEngine::virtCreateSurfaces();
	m_oTheRunningSurface.createSurface(m_iWindowWidth, m_iWindowHeight);
	m_oTheEndSurface1.createSurface(m_iWindowWidth, m_iWindowHeight);
	m_oTheEndSurface2.createSurface(m_iWindowWidth, m_iWindowHeight);
	m_oTheEndSurface3.createSurface(m_iWindowWidth, m_iWindowHeight);
	m_oTheEndSurface4.createSurface(m_iWindowWidth, m_iWindowHeight);
	m_oTheEndSurface5.createSurface(m_iWindowWidth, m_iWindowHeight);
}


int GameEngine::virtInitialise()
{
	getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	m_oTheRunningSurface.setDrawPointsFilter(&m_filterTranslation);
	m_oTheEndSurface1.setDrawPointsFilter(&m_filterTranslation);
	m_oTheEndSurface2.setDrawPointsFilter(&m_filterTranslation);
	m_oTheEndSurface3.setDrawPointsFilter(&m_filterTranslation);
	m_oTheEndSurface4.setDrawPointsFilter(&m_filterTranslation);
	m_oTheEndSurface5.setDrawPointsFilter(&m_filterTranslation);
	getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	setUpMusic();
	// Call base class version
	return BaseEngine::virtInitialise();
}


GameMainObject* GameEngine::getMainChar()
{
	// TODO: Add your implementation code here.
	return mainObject;
}

void GameEngine::virtPreDraw()
{
	m_pState->virtSetUpForeground(*this);
	// TODO: Add your implementation code here.
}

void GameEngine::setIsWin(bool win) {
	isWin = win;
}

void GameEngine::setIsLose(bool lose) {
	isLose = lose;
}


void GameEngine::virtMouseWheel(int x, int y, int which, int timestamp)
{

	if (y < 0)
		zoomOut();
	else if (y > 0)
		zoomIn();

	virtSetupBackgroundBuffer();

	redrawDisplay(); // Force total redraw

}


void GameEngine::zoomOut()
{

	int iOldCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
	int iOldCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);
	m_filterScaling.compress();

	int iNewCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
	int iNewCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);
	m_filterTranslation.changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);
	redrawDisplay(); // Force total redraw

}


void GameEngine::zoomIn()
{


	int iOldCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
	int iOldCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);
	m_filterScaling.stretch();

	int iNewCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
	int iNewCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);
	m_filterTranslation.changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);
	redrawDisplay(); // Force total redraw

}


void GameEngine::virtMainLoopDoAfterUpdate()
{
	if (deleteObject != NULL) {
		removeDisplayableObject(deleteObject);
		delete deleteObject;
		deleteObject = NULL;
	}
}


void GameEngine::setDeleteObject(DisplayableObject* ob)
{
	deleteObject = ob;
}


void GameEngine::playBulletMusic()
{
	SDL_ClearQueuedAudio(bulletDevice);
	SDL_QueueAudio(bulletDevice, wav_bullet_buffer, wav_bullet_length);
	SDL_PauseAudioDevice(bulletDevice, 0);
}
void GameEngine::addOpenCaseMusic() {

	SDL_ClearQueuedAudio(caseDevice);
	SDL_QueueAudio(caseDevice, wav_case_buffer, wav_case_length);
	SDL_PauseAudioDevice(caseDevice, 0);
}

void GameEngine::playDoorOpenMusic()
{
	SDL_ClearQueuedAudio(doorDevice);
	SDL_QueueAudio(doorDevice, wav_door_buffer, wav_door_length);
	SDL_PauseAudioDevice(doorDevice, 0);
}


void GameEngine::playBottleMusic()
{
	SDL_ClearQueuedAudio(bottleDevice);
	SDL_QueueAudio(bottleDevice, wav_bottle_buffer, wav_bottle_length);
	SDL_PauseAudioDevice(bottleDevice, 0);
}


void GameEngine::playDeadMusic()
{
	SDL_ClearQueuedAudio(deadDevice);
	SDL_QueueAudio(deadDevice, wav_dead_buffer, wav_dead_length);
	SDL_PauseAudioDevice(deadDevice, 0);
}



void GameEngine::playClickMusic()
{
	SDL_ClearQueuedAudio(clickDevice);
	SDL_QueueAudio(clickDevice, wav_click_buffer, wav_click_length);
	SDL_PauseAudioDevice(clickDevice, 0);
}
