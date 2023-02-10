#pragma once
#include "RigidBody.h"

class CircleRigidBody : public RigidBody
{
public:
	CircleRigidBody() {};
	virtual ~CircleRigidBody() {};

	void MovePosition(double dx, double dy) override
	{
		xPosition += dx;
		yPosition += dy;
	}

	void MoveVelocity(double dx, double dy) override
	{
		xVelocity += dx;
		yVelocity += dy;
	}

	void UpdateVelocity(double dt) override
	{
		xVelocity = (xPosition - xPastPosition) / dt;
		yVelocity = (yPosition - yPastPosition) / dt;
	}

	void Draw(olc::PixelGameEngine* pge) override
	{
		pge->DrawCircle(xPosition, yPosition, radius, olc::WHITE);
		pge->DrawLine(xPosition, yPosition, xPosition + xVelocity, yPosition + yVelocity, olc::RED);
	}
};