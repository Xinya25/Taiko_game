#include "MenuCtrl.h"
#include <stdio.h>

MenuCtrl::MenuCtrl()
{
}

MenuCtrl::MenuCtrl(SDL_Renderer* renderer)
{
    directory();
    bg = Pane(renderer, 0, 0, 1920, 1080);
    bg.setImage("../rsc/image/menu1_bg.png", renderer);
    bg.setAnimate(0, 0, 1416, 1080, LEFT, 1);
    createButton(renderer);
    teaching = Pane(renderer, 0, 0, 1920, 1080, "../rsc/image/teaching.png");

}

void MenuCtrl::createButton(SDL_Renderer* renderer)
{
    int btnH = 240, wh = 1080;
    bg.modify(btnH, wh);
    pathlen = (getSongNum() + 1) * btnH * 2 - wh;
    pathx = new int[pathlen];
    pathy = new int[pathlen];
    int yy = wh - (getSongNum() + 1) * btnH;
    for (int i = 0; i < pathlen; i++)
    {
        pathy[i] = yy;
        pathx[i] = (int)(-0.000685 * yy * yy + 0.74074 * yy + 200);
        yy++;
    }

    const char* fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
    playBtn = new Button[getSongNum()];
    buttonPathIndex = new int[getSongNum()];
    for (int i = 0; i < getSongNum(); i++)
    {
        buttonPathIndex[i] = (getSongNum() + 2) * btnH - wh + i * btnH;
        playBtn[i] = Button(renderer, 0, 0, 600, 100, folderName[i], 50, { 255, 255, 255 });
        playBtn[i].setX(pathx[buttonPathIndex[i]] - playBtn[i].getWidth() / 2);
        playBtn[i].setY(pathy[buttonPathIndex[i]] - playBtn[i].getHeight() / 2);
        playBtn[i].setStroke(10, 0, 0, 0);
        playBtn[i].setEnlarge(true);
    }

    scrollEffect = Mix_LoadWAV("../rsc/audio/Ka.wav");
    if (scrollEffect == NULL)
    {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void MenuCtrl::control(
    SDL_Renderer* renderer, Input& inputs,
    int& scene)
{

    for (int i = 0; i < getSongNum(); i++)
    {
        if (playBtn[i].getPress(inputs.mouse_Left, inputs.mouse_X, inputs.mouse_Y))
        {
            choice = i;
            inputs.mouse_Left = 0;
            scene = 2;
        }
    }

    if (inputs.keyboard_Esc)
    {
        inputs.keyboard_Esc = 0;
        scene = 0;
    }

    if (inputs.mouse_Wheel)
    {
        if (wheel - 10 * inputs.mouse_Wheel < 30 || wheel - 10 * inputs.mouse_Wheel > -30)
            wheel -= 10 * inputs.mouse_Wheel;
        else if (wheel - 10 * inputs.mouse_Wheel > 30)
            wheel = 30;
        else if (wheel - 10 * inputs.mouse_Wheel < -30)
            wheel = -30;
        inputs.mouse_Wheel = 0;
    }

    if (wheel)
    {

        if ((wheel > 0 && buttonPathIndex[0] - wheel > 0) ||
            (wheel < 0 && buttonPathIndex[getSongNum() - 1] - wheel < pathlen))
        {
            for (int i = 0; i < getSongNum(); i++)
            {
                buttonPathIndex[i] -= wheel;
                playBtn[i].setX(pathx[buttonPathIndex[i]] - playBtn[i].getWidth() / 2);
                playBtn[i].setY(pathy[buttonPathIndex[i]] - playBtn[i].getHeight() / 2);
            }
            wheel = (wheel > 0) ? wheel - 1 : wheel + 1;
        }
        else
            wheel = 0;
    }
}

void MenuCtrl::draw(SDL_Renderer* renderer)
{
    bg.draw();
    teaching.draw();
    for (int i = 0; i < getSongNum(); i++)
    {
        if (playBtn[i].getDst()->y <= 1080)
            playBtn[i].draw(255, 165, 0);
    }

    //for (int i = 0; i < pathlen; i++)
        //pixelRGBA(renderer, pathx[i], pathy[i], 255, 255, 255, 255);
}
