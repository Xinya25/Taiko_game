#include "HomeCtrl.h"
#include <stdio.h>

HomeCtrl::HomeCtrl()
{
}

HomeCtrl::HomeCtrl(SDL_Renderer* renderer)
{
    bg = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/home_bg.png");

    menuBtn = Button(renderer, 500, 250, 350, 150, "MENU", 60, { 255, 255, 255 });
    menuBtn.setStroke(10, 0, 0, 0);
    menuBtn.setCorner(10);
    menuBtn.setEnlarge(true);

    compBtn = Button(renderer, 1100, 250, 350, 150, "COMPOSE", 60, { 255, 255, 255 });
    compBtn.setStroke(10, 0, 0, 0);
    compBtn.setCorner(10);
    compBtn.setEnlarge(true);

    quitBtn = Button(renderer, 50, 50, 80, 80, "X", 40, { 255, 255, 255 });
    quitBtn.setStroke(10, 0, 0, 0);
    quitBtn.setCorner(10);
    quitBtn.setEnlarge(true);
}

void HomeCtrl::control(
    SDL_Renderer* renderer, Input& inputs,
    int& scene, bool& quit)
{
    if (menuBtn.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
    {
        scene = 1;
    }

    if (compBtn.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
    {
        scene = 4;
    }

    if (quitBtn.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
    {
        quit = true;
    }
}

void HomeCtrl::draw(SDL_Renderer* renderer)
{
    bg.draw();
    menuBtn.draw(255, 165, 0);
    compBtn.draw(255, 165, 0);
    quitBtn.draw(255, 165, 0);
}