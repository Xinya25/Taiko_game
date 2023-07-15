#include "SelectBox.h"

SelectBox::SelectBox() :Image()
{
}

SelectBox::SelectBox(SDL_Renderer* renderer, int x, int y) :Image(renderer)
{
    int size = 40;
    setX(x);
    setY(y);
    setWidth(size);
    setHeight(size);
}

void SelectBox::draw()
{
    if (enable)
    {
        roundedBoxRGBA(getRenderer(), getDst()->x + getDst()->w + 5, getDst()->y - 5, getDst()->x - 5, getDst()->y + getDst()->h + 5, 10, 0, 0, 0, 255);
        roundedBoxRGBA(getRenderer(), getDst()->x + getDst()->w, getDst()->y, getDst()->x, getDst()->y + getDst()->h, 5, 200, 200, 200, 255);
    }
    else
    {
        roundedBoxRGBA(getRenderer(), getDst()->x + getDst()->w + 5, getDst()->y - 5, getDst()->x - 5, getDst()->y + getDst()->h + 5, 10, 0, 0, 0, 255);
        roundedBoxRGBA(getRenderer(), getDst()->x + getDst()->w, getDst()->y, getDst()->x, getDst()->y + getDst()->h, 5, 50, 50, 50, 255);
    }
}

int SelectBox::getPress(int& mousePress, int mouseX, int mouseY)
{
    int press = mousePress &&
        mouseX >= getDst()->x &&
        mouseY >= getDst()->y &&
        mouseX < getDst()->x + getDst()->w &&
        mouseY < getDst()->y + getDst()->h;

    //mousePress = 0;
    return press;
}


void SelectBox::setEnable(bool en)
{
    enable = en;
}

bool SelectBox::getEnable()
{
    return enable;
}