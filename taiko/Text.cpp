#include "Text.h"

Text::Text()
{
}

Text::Text(const char* str, const char* fontPath, int fontSize,
	SDL_Color color, SDL_Renderer* renderer, SDL_Point pos)
{
	setRenderer(renderer);
	strokeWidth = 0;
	isMand = false;
	mandlength = 0;
	setString(str);
	setFontPath(fontPath);
	setFontSize(fontSize);
	setFgColor(color);
	setPos(pos);
	generateTexture();
}

Text::Text(Uint16* str, const char* fontPath, int fontSize,
	SDL_Color color, SDL_Renderer* renderer, SDL_Point pos)
{
	setRenderer(renderer);
	strokeWidth = 0;
	isMand = true;
	mandlength = 0;
	for (int i = 0; str[i] != 0; i++)
		mandlength++;
	setMandarin(str);
	setFontPath(fontPath);
	setFontSize(fontSize);
	setFgColor(color);
	setPos(pos);
	generateTexture();
}

void Text::generateTexture()
{
	ttfFont = TTF_OpenFont(fontPath, fontSize);
	if (ttfFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		exit(0);
	}
	// TTF_SetFontStyle(ttfFont, TTF_STYLE_BOLD);

	SDL_Surface* surface = NULL;
	if (isMand)
	{
		if (fontSize > 55)
			surface = TTF_RenderUNICODE_Solid(ttfFont, mandarin, fgColor);
		else
			surface = TTF_RenderUNICODE_Solid(ttfFont, mandarin, fgColor);
	}
	else
	{
		surface = TTF_RenderUTF8_Blended(ttfFont, str, fgColor);
	}

	TTF_CloseFont(ttfFont);

	if (surface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		exit(0);
	}
	else
	{
		//SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			exit(0);
		}

		setWidth(surface->w);
		setHeight(surface->h);
		setSrcW(surface->w);
		setSrcH(surface->h);

		SDL_FreeSurface(surface);
	}
}

void Text::setStroke(int width, SDL_Color color)
{
	strokeWidth = width;
	strokeColor = color;
	// generateStrokeTexture();
}
void Text::hitAnimation()
{
	setX(600 - (getWidth() / 2));
	setY(270);
	setPathIndex(0);
	time = 8;
	timerID = SDL_AddTimer(time, changeData, this);
}

Uint32 Text::changeData(Uint32 interval, void* param)
{
	Text* p = (Text*)param;

	if (p->time != 0)
	{
		if (p->getPathIndex() < 30)
		{
			p->setY(p->getPathY()[p->getPathIndex()]);
			p->setPathIndex(p->getPathIndex() + 1);
			return interval;
		}
		else
		{
			p->setY(1200);
			p->time = 0;
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void Text::close()
{
	SDL_DestroyTexture(texture);
}

void Text::draw()
{
	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
	{
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return;
	}

	SDL_RenderCopy(getRenderer(), texture, getSrc(), getDst());

	if (strokeWidth)
	{
		if (SDL_SetTextureBlendMode(strokeTexture, SDL_BLENDMODE_BLEND) == -1)
		{
			printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
			return;
		}

		SDL_RenderCopy(getRenderer(), strokeTexture, NULL, getSrc());
	}
}

void Text::setString(const char* s)
{
	str = new char[strlen(s)];
	strcpy_s(str, strlen(s) + 1, s);
}

void Text::setMandarin(Uint16* s)
{
	mandarin = s;
}

void Text::setFontPath(const char* f)
{
	fontPath = new char[strlen(f)];
	strcpy_s(fontPath, strlen(f) + 1, f);
}

void Text::setFontSize(int s)
{
	fontSize = s;
}

void Text::setFgColor(SDL_Color fc)
{
	fgColor = fc;
}

void Text::setPos(SDL_Point p)
{
	setX(p.x);
	setY(p.y);
	setSrcX(0);
	setSrcY(0);
}

int Text::Mandlen()
{
	return mandlength;
}


char* Text::getString()
{
	return str;
}


Uint16* Text::getMandarin()
{
	return mandarin;
}
