#pragma once
#include "Image.h"
#include "Const.h"
#include "Sprite.h"
#include <stdio.h>

class Sprite : public Image
{
public:
	Sprite();
	Sprite(SDL_Renderer* renderer, int x, int y, int w, int h,
		int n, int hhn, int wwn, bool loop, const char* path);
	void setPosition(int x, int y);
	void startTimer(Uint32 t);
	void stopTimer();
	void setFrame(int f);
	void setStartEnd(int start, int end, bool loop);
	int getFrame();
	int getNum();
	void draw();
	void close();

private:
	Uint32 time;
	SDL_TimerID timerID;
	int num;
	int wn;
	int hn;
	int frame;
	int fstart;
	int fend;
	bool isLoop;
	static Uint32 changeData(Uint32 interval, void* param);
};
