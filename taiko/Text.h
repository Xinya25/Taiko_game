#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include "Const.h"
#include "Object.h"
#include "SDL_ttf.h"

class Text :public Object
{
public:
	Text();
	Text(const char* str, const char* fontPath, int fontSize,
		SDL_Color color, SDL_Renderer* renderer, SDL_Point pos);
	Text(Uint16* str, const char* fontPath, int fontSize,
		SDL_Color color, SDL_Renderer* renderer, SDL_Point pos);
	void generateTexture();
	void close();
	void draw();

	void setString(const char* s);
	void setMandarin(Uint16* s);
	void setFontPath(const char* f);
	void setFontSize(int s);
	void setFgColor(SDL_Color fc);
	void setPos(SDL_Point p);
	void setStroke(int width, SDL_Color color);
	char* getString();
	Uint16* getMandarin();
	int Mandlen();
	void hitAnimation();

private:
	SDL_Texture* strokeTexture;
	SDL_Texture* texture;
	SDL_Rect strokedst;

	TTF_Font* ttfFont;
	TTF_Font* fontOutline;
	int strokeWidth;
	Uint16* mandarin;
	int mandlength;
	char* str;
	char* fontPath;
	int fontSize;
	Uint32 time;
	SDL_TimerID timerID;
	SDL_Color fgColor;
	SDL_Color strokeColor;
	bool isMand;
	static Uint32 changeData(Uint32 interval, void* param);
};