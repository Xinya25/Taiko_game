#include "Object.h"

Object::Object()
{
	src.x = 0;
	src.y = 0;
	src.h = -1;
	src.w = -1;
}

Object::Object(SDL_Renderer* renderer)
{
	setRenderer(renderer);
	src.x = 0;
	src.y = 0;
	src.h = -1;
	src.w = -1;
}

Object::Object(SDL_Renderer* renderer, int x, int y)
{
	src.x = 0;
	src.y = 0;
	src.h = -1;
	src.w = -1;
	setX(x);
	setY(y);
	setRenderer(renderer);
}

void Object::setX(int x)
{
	int y = 0;
	modify(x, y);
	dst.x = x;
}

void Object::setY(int y)
{
	int x = 0;
	modify(x, y);
	dst.y = y;
}

void Object::setWidth(int w)
{
	int h = 0;
	modify(w, h);
	dst.w = w;
}

void Object::setHeight(int h)
{
	int w = 0;
	modify(w, h);
	dst.h = h;
}

void Object::setSrcX(int x)
{
	src.x = x;
}

void Object::setSrcY(int y)
{
	src.y = y;
}

void Object::setSrcW(int w)
{
	src.w = w;
}

void Object::setSrcH(int h)
{
	src.h = h;
}

void Object::setPath(int size, int* pathx, int* pathy)
{
	pathSize = size;
	for (int i = 0; i < size; i++)
	{
		modify(pathx[i], pathy[i]);
	}
	pathX = pathx;
	pathY = pathy;
}

void Object::setPathSize(int size)
{
	pathSize = size;
}

void Object::setPathIndex(int x)
{
	pathIndex = x;
}

void Object::setRenderer(SDL_Renderer* ren)
{
	renderer = ren;
}

int Object::getX()
{
	int x = dst.x, y = 0;
	demodify(x, y);
	return x;
}

int Object::getY()
{
	int x = 0, y = dst.y;
	demodify(x, y);
	return y;
}

int Object::getWidth()
{
	int w = dst.w, h = 0;
	demodify(w, h);
	return w;
}

int Object::getHeight()
{
	int w = 0, h = dst.h;
	demodify(w, h);
	return h;
}

int Object::getSrcX()
{
	return src.x;
}

int Object::getSrcY()
{
	return src.y;
}

int Object::getSrcW()
{
	return src.w;
}

int Object::getSrcH()
{
	return src.h;
}

SDL_Rect* Object::getDst()
{
	return &dst;
}

SDL_Rect* Object::getSrc()
{
	return &src;
}

SDL_Renderer* Object::getRenderer()
{
	return renderer;
}

int* Object::getPathX()
{
	int* x = new int[pathSize];
	int y = 0;
	for (int i = 0; i < pathSize; i++)
	{
		x[i] = pathX[i];
		demodify(x[i], y);
	}
	return x;
}

int* Object::getPathY()
{
	int* y = new int[pathSize];
	int x = 0;
	for (int i = 0; i < pathSize; i++)
	{
		y[i] = pathY[i];
		demodify(x, y[i]);
	}
	return y;
}

int Object::getPathSize()
{
	return pathSize;
}

int Object::getPathIndex()
{
	return pathIndex;
}

void Object::modify(int& x, int& y)
{
	double mx, my;
	RenderWindow::getmodify(mx, my);

	x = (int)(x * mx);
	y = (int)(y * my);
}

void Object::demodify(int& x, int& y)
{
	double mx, my;
	RenderWindow::getmodify(mx, my);

	x = (int)(x / mx);
	y = (int)(y / my);
}
