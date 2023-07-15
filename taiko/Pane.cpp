#include "Pane.h"

Pane::Pane() :Image()
{
}

// full picture, set position only
Pane::Pane(SDL_Renderer* renderer, int x, int y, int w, int h) : Image(renderer)
{
    setX(x);
    setY(y);
    setWidth(w);
    setHeight(h);

    pic = false;
    velocity = 0;
    back = 0;
}

Pane::Pane(SDL_Renderer* renderer, int x, int y, int w, int h, const char* path)
    :Image(path, renderer)
{
    setX(x);
    setY(y);
    setWidth(w);
    setHeight(h);
    pic = true;
    velocity = 0;
    back = 0;
}

Pane::Pane(SDL_Renderer* renderer, int dstX, int dstY, int dstW, int dstH,
    int srcX, int srcY, int srcW, int srcH, const char* path)
    :Image(path, renderer)
{
    setX(dstX);
    setY(dstY);
    setWidth(dstW);
    setHeight(dstH);
    setSrcX(srcX);
    setSrcY(srcY);
    setSrcW(srcW);
    setSrcH(srcH);
    pic = true;
    velocity = 0;
    back = 0;
}

void Pane::setSrcPosition(int x, int y)
{
    setSrcX(x);
    setSrcY(y);
}

void Pane::setSrcSize(int w, int h)
{
    setSrcW(w);
    setSrcH(h);
}

void Pane::setPosition(int x, int y)
{
    setX(x);
    setY(y);
}

void Pane::UpAndStop(int x, int y1, int y2)
{
    int size = abs(y1 - y2);
    int* pathX = new int[size];
    int* pathY = new int[size];
    for (int i = 0; i < size / 2; i++)
    {
        pathX[i] = x;
        pathY[i] = y1 - i;
    }
    for (int i = size / 2; i < size; i++)
    {
        pathX[i] = x;
        pathY[i] = y2;
    }
    setPath(size, pathX, pathY);
}

void Pane::draw()
{
    if (pic)
    {
        if (velocity)
        {
            switch (direction)
            {
            case 1:
                if (getSrcX() - velocity < 0)
                    setSrcX(getSrcW() - getImageRect()->w);
                else
                    setSrcX(getSrcX() - velocity);
                break;
            case 2:
                if (getSrcX() + velocity > getImageRect()->w - getSrcW())
                    setSrcX(0);
                else
                    setSrcX(getSrcX() + velocity);
                break;
            case 3:
                if (getSrcY() - velocity < 0)
                    setSrcY(getHeight() - getSrcH());
                else
                    setSrcY(getSrcY() - velocity);
                break;
            case 4:
                if (getSrcY() + velocity > getDst()->h - getSrcH())
                    setSrcY(0);
                //src.y = 0;
                else
                    setSrcY(getSrcY() + velocity);
                break;
            }
        }
        Image::draw();
    }
    else
    {
        SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
        SDL_RenderFillRect(getRenderer(), getDst());
    }
}

void Pane::draw(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(getRenderer(), r, g, b, 255);
    SDL_RenderFillRect(getRenderer(), getDst());
}

void Pane::setImage(const char* path, SDL_Renderer* renderer)
{
    set(path, renderer);
    pic = true;
}

void Pane::setAnimate(int xx, int yy, int ww, int hh, int dir, int vel)
{
    setSrcX(xx);
    setSrcY(yy);
    setSrcW(ww);
    setSrcH(hh);
    direction = dir;
    velocity = vel;
}

void Pane::startTimer(Uint32 t)
{
    setPathIndex(0);
    time = t;
    timerID = SDL_AddTimer(time, changeData, this);
}

Uint32 Pane::changeData(Uint32 interval, void* param)
{
    Pane* p = (Pane*)param;

    if (p->time != 0)
    {
        if (p->getPathIndex() < p->getPathSize())
        {
            p->setX(p->getPathX()[p->getPathIndex()]);
            p->setY(p->getPathY()[p->getPathIndex()]);
            p->setPathIndex(p->getPathIndex() + 4);
            return interval;
        }
        else
        {
            p->setX(2000);
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

void Pane::people_move(Uint32 t)
{
    setPathIndex(0);
    time = t;
    timerID = SDL_AddTimer(time, people_animation, this);
}

Uint32 Pane::people_animation(Uint32 interval, void* param)
{
    Pane* p = (Pane*)param;
    if (p->time != 0)
    {
        if (p->back == 0)
        {
            p->setY(p->getY() - 10);
            if (p->getY() <= 620)
                p->back = 1;
            return interval;
        }
        else if (p->back == 1)
        {
            p->setY(p->getY() + 10);
            if (p->getY() >= 645)
                p->back = 0;
            return interval;
        }
        else {
            p->setY(655);
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

void Pane::logo_move(Uint32 t)
{
    setPathIndex(0);
    logo_time = t;
    logo_timerID = SDL_AddTimer(logo_time, logo_animation, this);
}

Uint32 Pane::logo_animation(Uint32 interval, void* param)
{
    Pane* p = (Pane*)param;
    if (p->time != 0)
    {
        if (p->count >= 15) {
            p->back = 10;
            p->setY(0);
            return interval;
        }
        else if (p->back == 0)
        {
            p->setY(p->getY() - 5);
            if (p->getY() <= -10) {
                p->back = 1;
                p->count++;
            }
            return interval;
        }
        else if (p->back == 1)
        {
            p->setY(p->getY() + 5);
            if (p->getY() >= 10) {
                p->back = 0;
                p->count++;
            }
            return interval;
        }
        else {
            p->setY(1080);
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

void Pane::close()
{
    Image::close();
}