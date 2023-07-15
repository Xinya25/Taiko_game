#pragma once
#include <SDL.h>
#include "Input.h"
#include "Button.h"
#include "SongData.h"
#include "Pane.h"
#include "Text.h"
#include <stdio.h>
#include <math.h>

class MenuCtrl : public SongData
{
private:
    Pane bg;
    Pane teaching;
    SDL_Rect bg_Rect;
    Button* playBtn;
    int* buttonPathIndex;
    int* pathx;
    int* pathy;
    int pathlen;
    int wheel;
    Mix_Chunk* scrollEffect;

public:
    int songNumber;
    MenuCtrl();
    MenuCtrl(SDL_Renderer* renderer);
    void control(SDL_Renderer* renderer, Input& inputs, int& gameState);
    void draw(SDL_Renderer* renderer);
    //int songchoose();
    void createButton(SDL_Renderer* renderer);
};
