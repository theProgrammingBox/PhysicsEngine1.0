#pragma once
#include "Header.h"

class RigidBody
{
public:
	RigidBody() {};
	virtual ~RigidBody() {};

	virtual void MovePosition(double dx, double dy) = 0;
	virtual void MoveVelocity(double dx, double dy) = 0;
	virtual void UpdateVelocity(double dt) = 0;
	virtual void Draw(olc::PixelGameEngine* pge) = 0;

	double xPosition;
	double yPosition;
	double xPastPosition;
	double yPastPosition;
	double xVelocity;
	double yVelocity;
	double radius;
	double inverseMass;
};