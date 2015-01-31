// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>         //SDL header file needed
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "globals.h"   //need for the global variable to be included everywhere
#include "eventhandler.h"
#include <vector>
#include <string>
#include <iostream>
#include "musichandler.h"

#pragma comment(lib, "SDL2.lib")   //used to get the SDL2 library
#pragma comment (lib, "SDL2main.lib") //need to LINK 3 libraries
#pragma comment(lib, "SDL2test.lib") //libraries contain the actual functions we use, header files contain the function info

int _tmain(int argc, _TCHAR* argv[])
{
	SDL_Init(SDL_INIT_VIDEO); //initializes game

	//values for the window we create
	int windowOffsetX = 68;
	int windowOffsetY = 22;
	int windowSizeX = 1295;
	int windowSizeY = 743;

	globals::window = SDL_CreateWindow("Game", windowOffsetX, windowOffsetY, windowSizeX, windowSizeY, 0); //creates a window, then saves the pointer
	globals::renderer = SDL_CreateRenderer(globals::window, -1, 0); //creates renderer, which we need to actually draw to the screen
	globals::handler = new EventHandler;

	SDL_SetRenderDrawColor(globals::renderer, 0, 0, 0, 0); //draws black background onto the screen
	bool quit = false; //when quit is true, game ends

	int imgFlags = IMG_INIT_PNG; //initializes flags for PNG files

	if (!IMG_Init(imgFlags) &imgFlags)
	{
		std::cout << "Failed to initialize PNG loading.\n";
		quit = true;
	}
	else
	{
		std::cout << "PNG loading success\n";
		globals::gScreenSurface = SDL_GetWindowSurface(globals::window);
	}
	//initializes SDL_mixer
	if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0))
	{
		std::cout << "Failed to initialize SDL_mixer\n";
		quit = true;
	}

	//initialize scenemanager
	globals::SceneManager = new sceneManager(); 
	globals::SceneManager->initializeScenes();
	//initialize musichandler
	globals::musicPlayer = new musichandler("Resources/sound/mario.mp3"); //TODO remove initialization, so we can change music between scenes
	globals::musicPlayer->playMusic();

	while (!quit)  //loop to prevent the game from ending immediately
	{
		SDL_RenderClear(globals::renderer); //clear screen
		globals::handler->getEvent();       //get inputs
		globals::SceneManager->runScene();  //run game for current frame
		SDL_RenderPresent(globals::renderer); //update screen
	}
	//deconstructor for window to close it
	SDL_DestroyWindow(globals::window);
	return 0;
}

