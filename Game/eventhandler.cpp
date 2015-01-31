#include "stdafx.h"
#include "eventhandler.h"

EventHandler::EventHandler()
{
	for (unsigned i = 0; i < 256; i++)
		keys[i] = false;
}

EventHandler::~EventHandler()
{

}

void EventHandler::getEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{

		}
		if (e.type == SDL_KEYDOWN) //returns which key is pressed and bool value
		{
			keys[e.key.keysym.sym] = true;
			noKeyPressed = false;
		}
		if (e.type == SDL_KEYUP) //returns lifting finger off key and bool value
		{
			keys[e.key.keysym.sym] = false;
			noKeyPressed = true;
		}
	}
}

bool EventHandler::isKeyDown(SDL_Keycode key)
{
	return keys[key];
}

bool EventHandler::isKeyUp()
{
	return noKeyPressed;
}