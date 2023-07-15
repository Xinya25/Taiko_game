#pragma once
#include <SDL.h>
#include "Input.h"
#include "Button.h"
#include "Pane.h"
class StartCtrl
{
private:
    Pane bg;
    SDL_Rect bg_Rect;
    Button startBtn;
    Pane logo;
    bool islogo;
    Mix_Chunk* startEffect;
public:
    StartCtrl();
    StartCtrl(SDL_Renderer* renderer);
    void control(SDL_Renderer* renderer, Input& inputs, int& gameState, bool& quit);
    void draw(SDL_Renderer* renderer);
};

