#pragma once
#include "Header.h"
#include "RigidBody.h"

class Force
{
public:
	Force() {};
	virtual ~Force() {};

	virtual void Apply(double dt) = 0;
	virtual void Draw(olc::PixelGameEngine* pge) = 0;
	
	double force;
	std::vector<RigidBody*>* rigidBodies;
};