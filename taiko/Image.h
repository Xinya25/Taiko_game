#pragma once
#include "Object.h"
#include <SDL.h> // Using SDL

class Image : public Object
{
public:
	Image();
	Image(SDL_Renderer* renderer);
	Image(const char* path, SDL_Renderer* renderer);
	Image(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void set(const char* path, SDL_Renderer* renderer);
	void set(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void draw();
	void setApha(Uint8 alpha);
	SDL_Rect* getImageRect();

private:
	SDL_Texture* texture;
	SDL_Rect imageRect;
};

