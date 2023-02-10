#pragma once
#include "RigidBody.h"

class FixedPointRigidBody : public RigidBody
{
public:
	FixedPointRigidBody() {};
	virtual ~FixedPointRigidBody() {};

	void MovePosition(double dx, double dy) override {};
	void MoveVelocity(double dx, double dy) override {};
	void UpdateVelocity(double dt) override {};
	void Draw(olc::PixelGameEngine* pge) override
	{
		pge->DrawCircle(xPosition, yPosition, radius, olc::WHITE);
	}
};