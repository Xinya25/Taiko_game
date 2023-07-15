#include "System.h"
#include <stdio.h>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

int System::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 0;
	}

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed: %s\n", IMG_GetError());
		return 0;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 5;
	}

	SDL_StartTextInput();

	return 1;
}

void System::close()
{
	SDL_StopTextInput();
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
