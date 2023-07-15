#include "Sprite.h"


Sprite::Sprite()
{

}

Sprite::Sprite(SDL_Renderer* renderer, int x, int y, int w, int h,
	int n, int hhn, int wwn, bool loop, const char* path)
	: Image(path, renderer)
{
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);

	num = n;
	frame = 0;
	fstart = 0;
	hn = hhn;
	wn = wwn;
	isLoop = loop;

	setSrcX(0);
	setSrcY(0);
	setSrcW(getSrcW() / wn);
	setSrcH(getSrcH() / hn);
}

void Sprite::setPosition(int x, int y)
{
	setX(x);
	setY(y);
}

int Sprite::getFrame()
{
	return frame;
}

int Sprite::getNum()
{
	return num;
}

Uint32 Sprite::changeData(Uint32 interval, void* param)
{
	Sprite* p = (Sprite*)param;


	if (p->time != 0)
	{
		if (p->isLoop)
		{

			p->frame = (p->frame + 1) % p->num;
		}
		else
		{
			if (p->frame < p->fend)
			{
				p->frame = (p->frame + 1) % p->num + p->fstart;
			}
			else
			{
				p->frame = 14;
				return 0;
			}
		}
		//p->frame = (p->frame + 1) % p->num;
		return interval;
	}
	else
	{
		return 0;
	}
}

void Sprite::startTimer(Uint32 t)
{
	SDL_RemoveTimer(timerID);
	time = t;
	timerID = SDL_AddTimer(time, changeData, this);
}

void Sprite::stopTimer()
{
	time = 0;
	SDL_RemoveTimer(timerID);
}

void Sprite::draw()
{
	int wc = frame / hn;
	int hc = frame % hn;

	setSrcX(getSrcW() * wc);
	setSrcY(getSrcH() * hc);
	Image::draw();
}


void Sprite::setFrame(int f)
{
	frame = f;
}

void Sprite::setStartEnd(int start, int end, bool loop)
{
	fstart = start;
	fend = end;
	frame = fstart;
	num = fend - fstart + 1;
	isLoop = loop;
}

void Sprite::close()
{
	Image::close();
	SDL_RemoveTimer(timerID);
}