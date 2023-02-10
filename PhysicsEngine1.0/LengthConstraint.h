#pragma once
#include "Constraint.h"
#include "RigidBody.h"

class LengthConstraint : public Constraint
{
public:
	LengthConstraint() {};
	virtual ~LengthConstraint() {};

	void Apply() override
	{
		double xDistance = body2->xPosition - body1->xPosition;
		double yDistance = body2->yPosition - body1->yPosition;
		double distance = sqrt(xDistance * xDistance + yDistance * yDistance);
		double correction = (length - distance) / distance / (body1->inverseMass + body2->inverseMass);
		body1->MovePosition(-xDistance * correction * body1->inverseMass, -yDistance * correction * body1->inverseMass);
		body2->MovePosition(xDistance * correction * body2->inverseMass, yDistance * correction * body2->inverseMass);
	}

	void Draw(olc::PixelGameEngine* pge) override
	{
		pge->DrawLine(body1->xPosition, body1->yPosition, body2->xPosition, body2->yPosition, olc::GREEN);
	}

	double length;
	RigidBody* body1;
	RigidBody* body2;
};