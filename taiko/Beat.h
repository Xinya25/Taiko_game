#pragma once
#include "Image.h"
#include "Const.h"
#include "RenderWindow.h"
#include "SDL2_gfxPrimitives.h"

class Beat : public Image
{
public:
	Beat();
	Beat(SDL_Renderer* renderer, int property, bool isBig, int index, int start);
	int getStartPostion();
	bool getAvailable();
	int getColor();
	bool getSize();
	void setAvailable(bool avai);
	void setPosition(int x, int y);
	void hitAnimation();
	void setColor(int col);
	void setSize(bool siz);
	void setOrangeLen(int dis);
	void draw();

private:
	Uint32 time;
	SDL_TimerID timerID;
	int startPosition;
	int orangeLen;
	int prop;
	bool size;
	bool available;

	SDL_Color color;
	SDL_Color blue;
	SDL_Color red;

	static Uint32 changeData(Uint32 interval, void* param);
	void setPath();
	void setPane(int index, int start);
	void setImage(SDL_Renderer* renderer, bool size, int property);
};
