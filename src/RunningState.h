#pragma once
#include "BaseState.h"
class RunningState :
	public BaseState
{
public:

	virtual void virtSetUpEngine(GameEngine& pEngine);
	virtual void virtDrawLabelText(GameEngine& pEngine);
	virtual void applyState(GameEngine& pEngine);
	virtual void virtSetUpKeyboard(GameEngine& pEngine, int iKeyCode);
	virtual void virtSetUpForeground(GameEngine& pEngine);
	virtual void virtSetUpMouseDown(GameEngine& pEngine, int iButton, int iX, int iY);

private:
	SDL_AudioSpec wav_spec;
	Uint32 wav_length;
	Uint8 *wav_buffer;
	SDL_AudioDeviceID deviceId;
};

