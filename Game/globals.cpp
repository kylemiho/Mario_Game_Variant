#include "stdafx.h"
#include "globals.h"

namespace globals
{
	SDL_Renderer *renderer = 0;  //default pointer to null
	EventHandler *handler = 0; //pointer to null
	SDL_Surface *gScreenSurface = 0;
	SDL_Window *window = 0;
	SDL_Rect *tile2 = 0; //list of where the renderer should crop out a given image, for sprite sheets
	sceneManager *SceneManager = 0; //initialize sceneManager
	musichandler *musicPlayer = 0;
}