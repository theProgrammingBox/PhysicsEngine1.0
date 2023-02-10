#pragma once
#include "Force.h"

class GravityForce : public Force
{
public:
	GravityForce() {};
	virtual ~GravityForce() {};

	void Apply(double dt) override
	{
		for (RigidBody* rigidBody : *rigidBodies)
			rigidBody->MoveVelocity(0, force * dt);
	}

	void Draw(olc::PixelGameEngine* pge) override
	{
		for (RigidBody* rigidBody : *rigidBodies)
			pge->DrawLine(rigidBody->xPosition, rigidBody->yPosition, rigidBody->xPosition, rigidBody->yPosition + force, olc::BLUE);
	}
};