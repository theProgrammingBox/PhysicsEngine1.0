#pragma once
#include "Force.h"

class UserForce : public Force
{
public:
	UserForce() {};
	virtual ~UserForce() {};

	void Apply(double dt) override
	{
		if (pge->GetMouse(0).bPressed)
		{
			for (RigidBody* rigidBody : *rigidBodies)
			{
				double xDistance = rigidBody->xPosition - pge->GetMouseX();
				double yDistance = rigidBody->yPosition - pge->GetMouseY();
				double distance = xDistance * xDistance + yDistance * yDistance;
				if (distance < rigidBody->radius * rigidBody->radius)
				{
					selectedRigidBody = rigidBody;
					break;
				}
			}
		}
		if (pge->GetMouse(0).bHeld)
		{
			if (selectedRigidBody != nullptr)
			{
				double xDistance = selectedRigidBody->xPosition - pge->GetMouseX();
				double yDistance = selectedRigidBody->yPosition - pge->GetMouseY();
				double distance = sqrt(xDistance * xDistance + yDistance * yDistance);
				selectedRigidBody->MoveVelocity(-xDistance * force / distance, -yDistance * force / distance);
			}
		}
		if (pge->GetMouse(0).bReleased)
		{
			selectedRigidBody = nullptr;
		}
	}

	void Draw(olc::PixelGameEngine* pge) override
	{
		this->pge = pge;
		
		if (selectedRigidBody != nullptr)
		{
			double xDistance = selectedRigidBody->xPosition - pge->GetMouseX();
			double yDistance = selectedRigidBody->yPosition - pge->GetMouseY();
			double distance = sqrt(xDistance * xDistance + yDistance * yDistance);
			pge->DrawLine(selectedRigidBody->xPosition, selectedRigidBody->yPosition, pge->GetMouseX(), pge->GetMouseY(), olc::RED);
		}
	}
	
	RigidBody* selectedRigidBody = nullptr;
	olc::PixelGameEngine* pge;
};