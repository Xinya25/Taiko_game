#include "Beat.h"
#include <stdio.h>

Beat::Beat() : Image()
{
}

Beat::Beat(SDL_Renderer* renderer, int col, bool siz, int index, int start) :Image()
{
	available = true;
	prop = col;
	size = siz;
	red = { 241, 85, 45 };
	blue = { 101, 190, 188 };
	setPath(); // drums out of window
	setImage(renderer, size, col);
	setPane(index, start);
}

void Beat::setPosition(int x, int y)
{
	setX(x);
	setY(y);
}

int Beat::getStartPostion()
{
	int y = 0;
	int x = startPosition;
	demodify(x, y);
	return x;
}

bool Beat::getAvailable()
{
	return available;
}

void Beat::setAvailable(bool avai)
{
	available = avai;
}

void Beat::hitAnimation()
{
	available = false;
	setPathIndex(0);
	time = 1;
	timerID = SDL_AddTimer(time, changeData, this);
}

Uint32 Beat::changeData(Uint32 interval, void* param)
{
	Beat* p = (Beat*)param;

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
			p->available = true;
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

void Beat::setPath()
{
	SDL_Point p1 = { 449, 342 }, p2 = { 990, 0 }, p3 = { 1770, 210 };
	SDL_Point tmpp1 = p1;

	p2.x -= p1.x;
	p2.y -= p1.y;
	p3.x -= p1.x;
	p3.y -= p1.y;
	p1.x = 0;
	p1.y = 0;

	double a = (double)(p2.x * p3.y - p3.x * p2.y) / (p2.x * p3.x * (p3.x - p2.x));
	double b = (double)p2.y / p2.x - p2.x * a;
	double c = 0;

	int size = p3.x - p1.x + 1;
	int* pathX = new int[size];
	int* pathY = new int[size];
	for (int i = p1.x; i < size; i++)
	{
		pathX[i] = tmpp1.x + i;
		pathY[i] = (int)(a * i * i + b * i + tmpp1.y);
	}
	Object::setPath(size, pathX, pathY);
}

void Beat::setPane(int index, int start)
{
	setWidth(100);
	setHeight(100);
	setX(index * 14 + start);
	setY(342);
	startPosition = index * 14 + start;

	int y = 0;
	modify(startPosition, y);
	setSrcX(0);
	setSrcW(100);
	setSrcH(100);
}

void Beat::setImage(SDL_Renderer* renderer, bool size, int property)
{
	if (property == RED)
		color = red;
	else if (property == BLUE)
		color = blue;
	else
		color = blue;

	Image::set("../rsc/image/beats.png", renderer);

}

void Beat::setSize(bool siz)
{
	size = siz;
	setSrcY(size ? 200 : 0);
}

void Beat::setColor(int col)
{
	if (col == RED)
		color = red;
	else if (col == BLUE)
		color = blue;
}

void Beat::setOrangeLen(int dis)
{
	int y = 0;
	orangeLen = dis * 14;
	modify(orangeLen, y);
}


int Beat::getColor()
{
	return prop;
}

bool Beat::getSize()
{
	return size;
}

void Beat::draw()
{
	int rad = size ? 2 * getDst()->w / 5 : getDst()->w / 4;
	setSrcY(size ? 200 : 0);

	if (prop == 1 || prop == 2)
		filledCircleRGBA(getRenderer(),
			getDst()->x + getDst()->w / 2,
			getDst()->y + getDst()->h / 2,
			rad, color.r, color.g, color.b, 255);

	else if (prop == 3) {
		roundedBoxRGBA(getRenderer(),
			getDst()->x + getDst()->w / 2 - rad - 6,
			getDst()->y + getDst()->h / 2 - rad - 6,
			getDst()->x + getDst()->w / 2 + rad + 6 + orangeLen,
			getDst()->y + getDst()->h / 2 + rad + 6,
			rad + 6, 0, 0, 0, 255);
		roundedBoxRGBA(getRenderer(),
			getDst()->x + getDst()->w / 2 - rad - 3,
			getDst()->y + getDst()->h / 2 - rad - 3,
			getDst()->x + getDst()->w / 2 + rad + 3 + orangeLen,
			getDst()->y + getDst()->h / 2 + rad + 3,
			rad + 3, 255, 255, 255, 255);
		roundedBoxRGBA(getRenderer(),
			getDst()->x + getDst()->w / 2 - rad,
			getDst()->y + getDst()->h / 2 - rad,
			getDst()->x + getDst()->w / 2 + rad + orangeLen,
			getDst()->y + getDst()->h / 2 + rad,
			rad, 255, 153, 0, 255);
	}
	Image::draw();
}