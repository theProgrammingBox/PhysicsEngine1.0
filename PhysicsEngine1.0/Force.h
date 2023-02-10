#pragma once
#include "Header.h"

class Force
{
public:
	Force() {};
	virtual ~Force() {};

	virtual void Apply(double dt) = 0;
	virtual void Draw(olc::PixelGameEngine* pge) = 0;
};