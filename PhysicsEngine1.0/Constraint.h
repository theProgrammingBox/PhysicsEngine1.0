#pragma once
#include "Header.h"

class Constraint
{
public:
	Constraint() {};
	virtual ~Constraint() {};

	virtual void Apply() = 0;
	virtual void Draw(olc::PixelGameEngine* pge) = 0;
};