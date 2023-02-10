#pragma once
#include "RigidBody.h"

class FixedPoint : public RigidBody
{
public:
	FixedPoint() {};
	virtual ~FixedPoint() {};

	void MovePosition(double dx, double dy) override {};
	void MoveVelocity(double dx, double dy) override {};
	void UpdateVelocity(double dt) override {};
	void Draw(olc::PixelGameEngine* pge) override
	{
		pge->DrawCircle(xPosition, yPosition, radius, olc::WHITE);
	}
};