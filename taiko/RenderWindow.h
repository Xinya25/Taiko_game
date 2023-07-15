#pragma once
#include <SDL.h>
#include "Const.h"

class RenderWindow
{
public:
	RenderWindow(const char* caption, int winx, int winy, int size);
	void close();
	void clear();
	void clear(Uint32 color);
	void display();
	SDL_Renderer* getRenderer();
	static void getmodify(double& mx, double& my);

private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_DisplayMode DM;
	int monitorWidth;
	int monitorHeight;
	int windowWidth;
	int windowHeight;
	static double modifyX;
	static double modifyY;
};