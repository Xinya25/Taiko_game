#include "Image.h"
#include "SDL_image.h"
#include <stdio.h>
#include <SDL.h> // Using SDL

Image::Image() : Object()
{
}

Image::Image(SDL_Renderer* renderer) : Object(renderer)
{
}

Image::Image(const char* path, SDL_Renderer* renderer) : Object(renderer)
{
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		SDL_SetColorKey(imgSurface, false, SDL_MapRGB(imgSurface->format, 0, 0, 0));
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		setWidth(imgSurface->w);
		setHeight(imgSurface->h);
		setSrcW(imgSurface->w);
		setSrcH(imgSurface->h);
		imageRect.x = 0;
		imageRect.y = 0;
		imageRect.w = imgSurface->w;
		imageRect.h = imgSurface->h;

		SDL_FreeSurface(imgSurface);
	}
}

Image::Image(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) : Object(renderer)
{
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));

		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		setWidth(imgSurface->w);
		setHeight(imgSurface->h);
		setSrcW(imgSurface->w);
		setSrcH(imgSurface->h);
		imageRect.x = 0;
		imageRect.y = 0;
		imageRect.w = imgSurface->w;
		imageRect.h = imgSurface->h;

		SDL_FreeSurface(imgSurface);
	}
}

void Image::set(const char* path, SDL_Renderer* renderer)
{
	setRenderer(renderer);
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		setWidth(imgSurface->w);
		setHeight(imgSurface->h);
		setSrcW(imgSurface->w);
		setSrcH(imgSurface->h);
		imageRect.x = 0;
		imageRect.y = 0;
		imageRect.w = imgSurface->w;
		imageRect.h = imgSurface->h;

		SDL_FreeSurface(imgSurface);
	}
}

void Image::set(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	setRenderer(renderer);
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));

		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		setWidth(imgSurface->w);
		setHeight(imgSurface->h);
		setSrcW(imgSurface->w);
		setSrcH(imgSurface->h);
		imageRect.x = 0;
		imageRect.y = 0;
		imageRect.w = imgSurface->w;
		imageRect.h = imgSurface->h;

		SDL_FreeSurface(imgSurface);
	}
}

void Image::close()
{
	SDL_DestroyTexture(texture);
}

void Image::draw()
{
	SDL_RenderCopy(getRenderer(), texture, getSrc(), getDst());
}

SDL_Rect* Image::getImageRect()
{
	return &imageRect;
}

void Image::setApha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}