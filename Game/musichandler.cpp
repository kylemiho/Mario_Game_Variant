#include "stdafx.h" //helps manage compiling, similar to "makefile"
#include "globals.h" //includes our global file
#include "musichandler.h"
#include "object.h"
#include <SDL.h>
#include "scene.h"
#include <SDL_image.h>
#include <SDL_mixer.h>

#pragma comment(lib, "SDL2.lib")   //used to get the SDL2 library
#pragma comment (lib, "SDL2main.lib") //need to LINK 3 libraries
#pragma comment(lib, "SDL2test.lib") //libraries contain the actual functions we use, header files contain the function info
#include <iostream>

musichandler::musichandler(std::string filepath) 
	:filepath(filepath)
{
	load = true;

	musicPlay = NULL;
	musicPlay = Mix_LoadMUS(filepath.c_str());
	if (!musicPlay)
	{
		std::cout << "Failed to load from: " << filepath << "\n";
		load = false;
	}
	else
	{
		std::cout << "Successfully loaded music from: " << filepath << "\n";
	}
	load = true;

	jump = NULL;
	jump = Mix_LoadWAV("Resources/sound/jump.wav");
	if (!jump)
	{
		std::cout << "Failed to load from: Resources/music/jump.wav\n";
		load = false;
	}
	else
	{
		std::cout << "Successfully loaded music from: Resources/music/jump.wav\n";
	}
	currentTicks = 0;
	previousTicks = -150;  //intialized to allow jumping in first 0.15 seconds of game
}

musichandler::~musichandler()
{
	Mix_FreeMusic(musicPlay);
	musicPlay = NULL;
	Mix_FreeChunk(jump);
	jump = NULL;
	load = false;
}

void musichandler::run() //sound effects to play
{

}

//move mario jump to seperate function and call it from scene.cpp
void musichandler::jumpSound()
{
	if (jump)
	{
			Mix_PlayChannel(-1, jump, 0);
	}
}

void musichandler::playMusic()
{
	if (load)
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(musicPlay, -1);
		}
	}
	else
	{
		std::cout << "Cannot play music.\n";
	}
}

void musichandler::stopMusic()
{
	if (load)
	{
		Mix_PauseMusic();
	}
}