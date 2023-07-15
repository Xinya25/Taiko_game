#include "StartCtrl.h"
#include <stdio.h>

StartCtrl::StartCtrl()
{
}

StartCtrl::StartCtrl(SDL_Renderer* renderer)
{
    bg = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/start_bg.png");
    logo = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/logo.png");
    islogo = true;

    startBtn = Button(renderer, 700, 900, 500, 100, "Start", 60, { 255, 255, 255 });
    startBtn.setStroke(10, 0, 0, 0);
    startBtn.setCorner(10);
    startBtn.setEnlarge(true);
    startEffect = Mix_LoadWAV("../rsc/audio/taiko.wav");
    if (startEffect == NULL)
    {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    Mix_PlayChannel(-1, startEffect, 0);

}

void StartCtrl::control(
    SDL_Renderer* renderer, Input& inputs,
    int& scene, bool& quit)
{
    if (startBtn.getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
    {
        scene = 0;

    }

    if (islogo) {
        logo.logo_move(50);
        islogo = false;
    }

}

void StartCtrl::draw(SDL_Renderer* renderer)
{
    bg.draw();
    logo.draw();
    startBtn.draw(255, 165, 0);
}