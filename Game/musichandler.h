#ifndef __MUSICHANDLER_H__
#define __MUSICHANDLER_H__

#include <SDL_mixer.h> 
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <string>

class musichandler
{
public:
	musichandler(std::string filepath);
	~musichandler();
	void playMusic();
	void stopMusic();
	void run();
	void jumpSound();

protected:
	std::string filepath;
	bool load;
	Mix_Music *musicPlay;
	Mix_Chunk *jump;
	int currentTicks;
	int previousTicks;
};

#endif