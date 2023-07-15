#pragma once
#include <SDL.h>
#include "Image.h"
#include "Text.h"
#include "RenderWindow.h"
#include <stdio.h>
#include "SDL2_gfxPrimitives.h"
#include <SDL_mixer.h>
#include "Input.h"


class Button : public Image
{
public:
	// constructors
	Button();
	Button(SDL_Renderer* renderer, int x, int y, int r, const char* string, int fontSize, SDL_Color color);
	Button(const char* path, SDL_Renderer* renderer, int xx, int yy);
	Button(SDL_Renderer* renderer, int xx, int yy, int ww, int hh);
	Button(SDL_Renderer* renderer, int xx, int yy, int ww, int hh,
		const char* string, int fontSize, SDL_Color color);

	// setters
	void setStroke(int width, Uint8 r, Uint8 g, Uint8 b);
	void setCorner(int r);
	void setX(int x);
	void setY(int y);
	void setEnlarge(bool en);

	// getters
	int getPress(int& mousePress, int mouseX, int mouseY);
	bool getInside();

	// functional
	void draw(Uint8 r, Uint8 g, Uint8 b);

private:
	bool inside;
	bool enlarge;
	int shape;	// 0: square, 1: circle
	int radius;
	int stroke;
	int originW;
	int originH;
	int originR;
	SDL_Rect stroke_rect;
	Uint8 stroke_r;
	Uint8 stroke_g;
	Uint8 stroke_b;
	Text text;
	int corner;
	Mix_Chunk* BtnPressEffect;
	Mix_Chunk* BtnInsideEffect;

	void initSound();
};
