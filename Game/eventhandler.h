#pragma once
#include <SDL.h>

class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	void getEvent();
	bool isKeyDown(SDL_Keycode key);
	bool isKeyUp();
	bool noKeyIsPressed()
	{
		return noKeyPressed;
	}

protected:
	bool keys[256];
	bool noKeyPressed;
};
