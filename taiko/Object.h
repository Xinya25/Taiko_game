#pragma once
#include <SDL.h>
#include "RenderWindow.h"

class Object
{
private:
	int* pathX;
	int* pathY;
	int pathSize;
	int pathIndex;
	SDL_Rect src;
	SDL_Rect dst;
	SDL_Renderer* renderer;

public:
	// constructor
	Object();
	Object(SDL_Renderer* renderer);
	Object(SDL_Renderer* renderer, int x, int y);

	// setter
	void setX(int x);
	void setY(int y);
	void setWidth(int w);
	void setHeight(int h);
	void setSrcX(int x);
	void setSrcY(int y);
	void setSrcW(int w);
	void setSrcH(int H);
	void setPath(int size, int* pathx, int* pathy);
	void setPathSize(int size);
	void setPathIndex(int x);
	void setRenderer(SDL_Renderer* ren);

	// getter
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getSrcX();
	int getSrcY();
	int getSrcW();
	int getSrcH();

	int* getPathX();
	int* getPathY();
	int getPathSize();
	int getPathIndex();

	SDL_Rect* getDst();
	SDL_Rect* getSrc();
	SDL_Renderer* getRenderer();

	// function
	void modify(int& x, int& y);
	void demodify(int& x, int& y);
};

