#pragma once
#include "Force.h"

class Gravity : public Force
{
public:
	Gravity() {};
	virtual ~Gravity() {};

	void Apply(double dt) override
	{
		for (RigidBody* rigidBody : rigidBodies)
			rigidBody->MoveVelocity(0, gravity * dt);
	}

	void Draw(olc::PixelGameEngine* pge) override
	{
		for (RigidBody* rigidBody : rigidBodies)
			pge->DrawLine(rigidBody->xPosition, rigidBody->yPosition, rigidBody->xPosition, rigidBody->yPosition + gravity, olc::BLUE);
	}

	double gravity;
	std::vector<RigidBody*> rigidBodies;
};