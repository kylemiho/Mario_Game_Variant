#pragma once

#include <SDL.h>
#include <vector>
#include <iostream>
#include <string>

#include "eventhandler.h"
#include "scenemanager.h"
#include "musichandler.h"

namespace globals
{
	extern SDL_Renderer *renderer;
	extern EventHandler *handler;
	extern SDL_Surface *gScreenSurface;
	extern SDL_Window *window;
	extern SDL_Rect *tile2; //list of where the renderer should crop out a given image, for sprite sheets
	extern sceneManager *SceneManager;
	extern musichandler *musicPlayer;
}