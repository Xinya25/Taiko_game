#include "RenderWindow.h"
#include <stdio.h>

// winx, winy: window's postiion,  size: percentage of full monitor size
RenderWindow::RenderWindow(const char* caption, int winx, int winy, int size)
{
	SDL_GetCurrentDisplayMode(0, &DM);
	monitorWidth = DM.w;
	monitorHeight = DM.h;
	windowWidth = monitorWidth * size / 100;
	windowHeight = monitorHeight * size / 100;
	modifyX = windowWidth / 1920.0;
	modifyY = windowHeight / 1080.0;

	window = SDL_CreateWindow(caption, winx, winy, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(0);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(0);
	}

	printf("SDL system initializes successfully!!!\n");
}

void RenderWindow::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
}

void RenderWindow::clear(Uint32 color)
{
	SDL_SetRenderDrawColor(renderer, color / 0x1111111, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100);
	SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}

void RenderWindow::getmodify(double& mx, double& my)
{
	mx = modifyX;
	my = modifyY;
}

double RenderWindow::modifyX = 0.0;
double RenderWindow::modifyY = 0.0;
