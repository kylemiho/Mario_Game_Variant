#pragma once

class Sprite
{
public:
	int x, y;
	int w, h;
	Sprite(int x, int y, int w, int h)
	:
	x(x), y(y), w(w), h(h)
	{
	}

	Sprite()
	:
	x(0), y(0), w(0), h(0)
	{
	}

	~Sprite()
	{}

};

