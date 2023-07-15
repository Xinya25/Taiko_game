#pragma once
#include <SDL.h>
#include "Input.h"
#include "Button.h"
#include "Pane.h"

class HomeCtrl
{
private:
    Pane bg;
    SDL_Rect bg_Rect;
    Button menuBtn;
    Button compBtn;
    Button quitBtn;
public:
    HomeCtrl();
    HomeCtrl(SDL_Renderer* renderer);
    void control(SDL_Renderer* renderer, Input& inputs, int& gameState, bool& quit);
    void draw(SDL_Renderer* renderer);
};

