#include "TextInput.h"

using namespace std;

TextInput::TextInput()
{
}

TextInput::TextInput(Text t)
{
	text = t;
	text.setString(" ");
	text.generateTexture();

	typeEffect = Mix_LoadWAV("../rsc/audio/typing.wav");
	if (typeEffect == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	selected = true;
	numOnly = false;
}

void TextInput::edit(Input& input)
{
	if (input.isEvent && selected)
	{
		bool textFlag = false;
		char* str = new char[strlen(text.getString()) + 1]();
		strcpy_s(str, strlen(text.getString()) + 1, text.getString());
		switch (input.type)
		{
		case SDL_KEYDOWN:
			Mix_PlayChannel(-1, typeEffect, 0);
			if (input.keySym == SDLK_BACKSPACE && strlen(str) > 0)
			{
				str[strlen(str) - 1] = '\0';
				textFlag = true;
			}
			else if (input.keySym == SDLK_c && (SDL_GetModState() & KMOD_CTRL))
			{
				SDL_SetClipboardText(str + 1);
			}
			else if (input.keySym == SDLK_v && (SDL_GetModState() & KMOD_CTRL))
			{
				char* strtmp = new char[strlen(str) + strlen(SDL_GetClipboardText()) + 1]();
				strcpy_s(strtmp, strlen(str) + 1, str);
				strcat_s(strtmp, strlen(str) + strlen(SDL_GetClipboardText()) + 1, SDL_GetClipboardText());
				str = strtmp;
				textFlag = true;
			}
			break;

		case SDL_TEXTINPUT:
			Mix_PlayChannel(-1, typeEffect, 0);
			if (!((SDL_GetModState() & KMOD_CTRL) && (input.keyTyped[0] == 'c' || input.keyTyped[0] == 'C' || input.keyTyped[0] == 'v' || input.keyTyped[0] == 'V')) && strlen(str) <= 30)
			{
				bool canCat = true;
				if (numOnly)
				{
					for (int i = 0; i < strlen(input.keyTyped); i++)
					{
						if (input.keyTyped[i] < '0' || input.keyTyped[i]>'9')
						{
							canCat = false;
							break;
						}
					}

				}
				if (canCat)
				{
					char* strtmp = new char[strlen(str) + strlen(input.keyTyped) + 1]();
					strcpy_s(strtmp, strlen(str) + 1, str);

					strcat_s(strtmp, strlen(str) + strlen(input.keyTyped) + 1, input.keyTyped);
					str = strtmp;
					textFlag = true;
				}
			}
			break;
		}

		if (textFlag)
		{
			if (strcmp(str, "") != 0)
			{
				setText(str);
				generateTexture();
			}
			else
			{
				strcpy_s(str, 2, " ");
				setText(str);
				generateTexture();
			}
		}
	}

}

void TextInput::generateTexture()
{
	text.generateTexture();
}

void TextInput::setText(char* s)
{
	text.setString(s);
}

void TextInput::setNum()
{
	numOnly = true;
}

void TextInput::setPos(SDL_Point p)
{
	text.setPos(p);
}

int TextInput::getWidth()
{
	return text.getWidth();
}

void TextInput::draw()
{
	text.draw();
}

void TextInput::draw(SDL_Renderer* ren, SDL_Point pos)
{
	text.setRenderer(ren);
	text.setPos(pos);
	draw();
}

char* TextInput::getString()
{
	return text.getString();
}


void TextInput::setSelect(bool s)
{
	selected = s;
}


void TextInput::close()
{
	Mix_FreeChunk(typeEffect);
	text.close();
}