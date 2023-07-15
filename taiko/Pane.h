#pragma once
#include <SDL.h>
#include "Image.h"
#include "RenderWindow.h"
#include <stdio.h>

class Pane : public Image
{
public:
	// constructors
	Pane();
	Pane(SDL_Renderer* renderer, int xx, int yy, int ww, int hh);
	Pane(SDL_Renderer* renderer, int x, int y, int w, int h, const char* path);
	Pane(SDL_Renderer* renderer, int dstX, int dstY, int dstW, int dstH,
		int srcX, int srcY, int srcW, int srcH, const char* path);

	// setters
	void setSrcPosition(int x, int y);
	void setSrcSize(int w, int h);
	void setPosition(int xx, int yy);
	void setAnimate(int xx, int yy, int ww, int hh, int dir, int vel);
	void setImage(const char* path, SDL_Renderer* renderer);

	// functional
	void UpAndStop(int x, int y1, int y2);
	void draw();
	void draw(Uint8 r, Uint8 g, Uint8 b);
	void startTimer(Uint32 t);
	void people_move(Uint32 t);
	void logo_move(Uint32 t);
	void close();

private:
	char path[100];
	bool pic;
	int back; //people & logo 0:up, 1: down
	int count = 0;
	Uint32 time;
	SDL_TimerID timerID;
	Uint32 p_time;
	SDL_TimerID p_timerID;
	Uint32 logo_time;
	SDL_TimerID logo_timerID;

	int direction; // 1: right, 2: left, 3: up, 4: down
	int velocity;  // picture moving animation velocity

	static Uint32 changeData(Uint32 interval, void* param);
	static Uint32 people_animation(Uint32 interval, void* param);
	static Uint32 logo_animation(Uint32 interval, void* param);
};
