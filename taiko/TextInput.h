#pragma once
#include "Text.h"
#include "Input.h"
#include <string.h>
#include <iostream>
#include <SDL_mixer.h>

class TextInput
{
public:
	TextInput();
	TextInput(Text t);

	void edit(Input& input);
	void generateTexture();
	void setSelect(bool s);
	void setText(char* s);
	void setNum();
	void setPos(SDL_Point p);
	int getWidth();
	void draw();
	void draw(SDL_Renderer* renderer, SDL_Point pos);
	char* getString();
	void close();

private:
	Text text;
	bool selected;
	bool numOnly;
	Mix_Chunk* typeEffect;
};

