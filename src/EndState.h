#pragma once
#include "BaseState.h"

class EndState :
	public BaseState
{
public:

	virtual void virtSetUpEngine(GameEngine& pEngine);
	virtual void virtDrawLabelText(GameEngine& pEngine);
	virtual void applyState(GameEngine& pEngine);
	virtual void virtSetUpKeyboard(GameEngine& pEngine, int iKeyCode);
	virtual void virtSetUpForeground(GameEngine& pEngine);
	virtual void virtSetUpMouseDown(GameEngine& pEngine, int iButton, int iX, int iY) ;
};

