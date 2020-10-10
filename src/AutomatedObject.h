#pragma once
#include "DisplayableObject.h"
#include "header.h"
#include "GameEngine.h"
#include "MovementPosition.h"

class AutomatedObject :
	public DisplayableObject
{
public:
	AutomatedObject(GameEngine* pEngine, int iID, int iStartX, int iStartY, int iSize);
	virtual ~AutomatedObject();
	void virtDraw() override; 
	void virtDoUpdate(int iCurrentTime) override;
protected:
	GameEngine* m_pEngine;
	int m_iID;
	int m_iSize;
};



