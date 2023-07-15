#include "Button.h"

Button::Button() :Image()
{
}

Button::Button(SDL_Renderer* renderer, int x, int y, int r, const char* string, int fontSize, SDL_Color color) :Image(renderer)
{
    originR = r;
    shape = 1;
    enlarge = false;
    setX(x);
    setY(y);
    radius = r;
    stroke = 0;
    corner = 0;
    const char* fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
    text = Text(string, fontPath, fontSize, color, renderer, { x, y });
    text.setX(x + radius - text.getWidth() / 2);
    text.setY(y + radius - text.getHeight() / 2);
    int useless = 0;
    radius = r;
    modify(radius, useless);

    initSound();
}

Button::Button(const char* path, SDL_Renderer* renderer, int x, int y)
    :Image(path, renderer)
{
    originW = getWidth();
    originH = getHeight();
    shape = 2;
    enlarge = false;
    setX(x);
    setY(y);
    stroke = 0;
    corner = 0;
    const char* fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
    text = Text(" ", fontPath, 30, { 0, 0, 0 }, renderer, { x, y });

    initSound();
}

Button::Button(SDL_Renderer* renderer, int x, int y, int w, int h) :Image(renderer)
{
    originW = w;
    originH = h;
    shape = 0;
    enlarge = false;
    setX(x);
    setY(y);
    setWidth(w);
    setHeight(h);
    stroke = 0;
    corner = 0;
    const char* fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
    text = Text(" ", fontPath, 30, { 0, 0, 0 }, renderer, { x, y });

    initSound();
}

void Button::initSound()
{
    BtnPressEffect = Mix_LoadWAV("../rsc/audio/Don.wav");
    if (BtnPressEffect == NULL)
    {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    BtnInsideEffect = Mix_LoadWAV("../rsc/audio/Ka.wav");
    if (BtnPressEffect == NULL)
    {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

Button::Button(SDL_Renderer* renderer, int x, int y, int w, int h,
    const char* string, int fontSize, SDL_Color color) :Image(renderer)
{
    originW = w;
    originH = h;
    shape = 0;
    enlarge = false;
    setX(x);
    setY(y);
    setWidth(w);
    setHeight(h);
    stroke = 0;
    corner = 0;
    const char* fontPath = "../fonts/Taiko_No_Tatsujin_Official_Font.ttf";
    text = Text(string, fontPath, fontSize, color, renderer, { x, y });
    text.setX(x + w / 2 - text.getWidth() / 2);
    text.setY(y + h / 2 - text.getHeight() / 2);

    initSound();
}

/*void Button::close()
{
    Image::close();
}

void Button::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void Button::draw()
{
    Image::draw(rect, {-1});
}*/

void Button::draw(Uint8 r, Uint8 g, Uint8 b)
{
    if (shape == 0)
    {
        if (corner)
        {
            if (stroke)
            {
                roundedBoxRGBA(getRenderer(), getDst()->x + getDst()->w + stroke, getDst()->y - stroke, getDst()->x - stroke, getDst()->y + getDst()->h + stroke, corner + stroke, stroke_r, stroke_g, stroke_b, 255);
            }
            roundedBoxRGBA(getRenderer(), getDst()->x + getDst()->w, getDst()->y, getDst()->x, getDst()->y + getDst()->h, corner, r, g, b, 255);

        }
        else
        {
            if (stroke)
            {
                SDL_SetRenderDrawColor(getRenderer(), stroke_r, stroke_g, stroke_b, 255);
                stroke_rect.x = getDst()->x - stroke;
                stroke_rect.y = getDst()->y - stroke;
                stroke_rect.w = getDst()->w + stroke * 2;
                stroke_rect.h = getDst()->h + stroke * 2;
                SDL_RenderFillRect(getRenderer(), &stroke_rect);
            }
            SDL_SetRenderDrawColor(getRenderer(), r, g, b, 255);
            SDL_RenderFillRect(getRenderer(), getDst());
        }
        text.draw();
    }
    else if (shape == 1)
    {
        if (stroke)
        {
            filledCircleRGBA(getRenderer(), getDst()->x + radius, getDst()->y + radius, radius + stroke, stroke_r, stroke_g, stroke_b, 255);
        }
        filledCircleRGBA(getRenderer(), getDst()->x + radius, getDst()->y + radius, radius, r, g, b, 255);
        text.draw();
    }
    else if (shape == 2)
    {
        Image::draw();
    }
}

void Button::setStroke(int width, Uint8 r, Uint8 g, Uint8 b)
{
    stroke = width;
    stroke_r = r;
    stroke_g = g;
    stroke_b = b;
}

void Button::setCorner(int r)
{
    corner = r;
}


void Button::setEnlarge(bool en)
{
    enlarge = en;
}


void Button::setX(int x)
{
    Object::setX(x);
    text.setX(getX() + getWidth() / 2 - text.getWidth() / 2);
}

void Button::setY(int y)
{
    Object::setY(y);
    text.setY(getY() + getHeight() / 2 - text.getHeight() / 2);
}

bool Button::getInside()
{
    return inside;
}

int Button::getPress(int& mousePress, int mouseX, int mouseY)
{
    int press;
    bool lastInside = inside;
    if (shape == 0)
    {
        inside = mouseX >= getDst()->x &&
            mouseY >= getDst()->y &&
            mouseX < getDst()->x + getDst()->w &&
            mouseY < getDst()->y + getDst()->h;

        press = mousePress &&
            mouseX >= getDst()->x &&
            mouseY >= getDst()->y &&
            mouseX < getDst()->x + getDst()->w &&
            mouseY < getDst()->y + getDst()->h;
    }
    else if (shape == 1)
    {
        inside =
            mouseX >= getDst()->x &&
            mouseY >= getDst()->y &&
            mouseX < getDst()->x + radius * 2 &&
            mouseY < getDst()->y + radius * 2;

        press = mousePress &&
            mouseX >= getDst()->x &&
            mouseY >= getDst()->y &&
            mouseX < getDst()->x + radius * 2 &&
            mouseY < getDst()->y + radius * 2;
    }

    if (enlarge && inside && !shape && getWidth() < 1.2 * originW)
    {
        int midX = getDst()->x + getDst()->w / 2;
        int midY = getDst()->y + getDst()->h / 2;
        setWidth((int)(getWidth() * 1.05));
        setHeight((int)(getHeight() * 1.05));
        getDst()->x = midX - getDst()->w / 2;
        getDst()->y = midY - getDst()->h / 2;
    }
    else if (enlarge && !inside)
    {
        if (!shape && getWidth() > originW)
        {
            int midX = getDst()->x + getDst()->w / 2;
            setWidth((int)(getWidth() * 0.95));
            getDst()->x = midX - getDst()->w / 2;
        }
        if (!shape && getHeight() > originH)
        {
            int midY = getDst()->y + getDst()->h / 2;
            setHeight((int)(getHeight() * 0.95));
            getDst()->y = midY - getDst()->h / 2;
        }
    }

    if (!lastInside && inside)
    {
        Mix_PlayChannel(-1, BtnInsideEffect, 0);
    }

    if (press)
    {
        Mix_PlayChannel(-1, BtnPressEffect, 0);
    }

    //mousePress = 0;
    return press;
}