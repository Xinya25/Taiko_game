#pragma once

#include <SDL.h>
#include "Image.h"
#include "RenderWindow.h"
#include <stdio.h>
#include "Input.h"
#include "SDL2_gfxPrimitives.h"

class SelectBox : Image
{
public:
	// constructors
	SelectBox();
	SelectBox(SDL_Renderer* renderer, int xx, int yy);

	// setters
	void setEnable(bool en);

	// getters
	int getPress(int& mousePress, int mouseX, int mouseY);
	bool getEnable();

	// functional
	void draw();

private:
	SDL_Rect stroke_rect;
	bool enable;
};

