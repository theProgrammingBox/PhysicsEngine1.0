#include "LengthConstraint.h"
#include "GravityForce.h"
#include "FixedPointRigidBody.h"
#include "CircleRigidBody.h"
#include "UserForce.h"

/*
TODO:
1. Use constructors and destructors, rework pge and naming.
2. Add a good user force.
*/

class SystemVisualizer : public olc::PixelGameEngine
{
public:
	std::vector<RigidBody*> rigidBodies;
	std::vector<Force*> forces;
	std::vector<Constraint*> constraints;

	void Stimulate(double dt)
	{
		for (Force* force : forces)
			force->Apply(dt);
		for (RigidBody* rigidBody : rigidBodies)
		{
			rigidBody->SetPastPosition();
			rigidBody->MovePosition(rigidBody->xVelocity * dt, rigidBody->yVelocity * dt);
		}
		for (Constraint* constraint : constraints)
			constraint->Apply();
		for (RigidBody* rigidBody : rigidBodies)
			rigidBody->UpdateVelocity(dt);
	}

	void DrawSystem()
	{
		Clear(olc::BLACK);

		for (RigidBody* rigidBody : rigidBodies)
			rigidBody->Draw(this);
		for (Force* force : forces)
			force->Draw(this);
		for (Constraint* constraint : constraints)
			constraint->Draw(this);
	}
	
	SystemVisualizer() { sAppName = "System Visualizer"; }
	
	bool OnUserCreate() override
	{
		FixedPointRigidBody* fixedPointRigidBody = new FixedPointRigidBody();
		fixedPointRigidBody->xPosition = ScreenWidth() / 2;
		fixedPointRigidBody->yPosition = ScreenHeight() / 2;
		fixedPointRigidBody->xVelocity = 0;
		fixedPointRigidBody->yVelocity = 0;
		fixedPointRigidBody->radius = 10;
		fixedPointRigidBody->inverseMass = 0.0f;
		rigidBodies.push_back(fixedPointRigidBody);
		
		CircleRigidBody* circleRigidBody = new CircleRigidBody();
		circleRigidBody->xPosition = rigidBodies[0]->xPosition + 100;
		circleRigidBody->yPosition = rigidBodies[0]->yPosition;
		circleRigidBody->xVelocity = 0;
		circleRigidBody->yVelocity = 0;
		circleRigidBody->radius = 10;
		circleRigidBody->inverseMass = 1.0f / (circleRigidBody->radius * circleRigidBody->radius * M_PI);
		rigidBodies.push_back(circleRigidBody);

		CircleRigidBody* circleRigidBody2 = new CircleRigidBody();
		circleRigidBody2->xPosition = rigidBodies[1]->xPosition + 100;
		circleRigidBody2->yPosition = rigidBodies[1]->yPosition;
		circleRigidBody2->xVelocity = 0;
		circleRigidBody2->yVelocity = 0;
		circleRigidBody2->radius = 10;
		circleRigidBody2->inverseMass = 1.0f / (circleRigidBody2->radius * circleRigidBody2->radius * M_PI);
		rigidBodies.push_back(circleRigidBody2);

		CircleRigidBody* circleRigidBody3 = new CircleRigidBody();
		circleRigidBody3->xPosition = rigidBodies[2]->xPosition + 100;
		circleRigidBody3->yPosition = rigidBodies[2]->yPosition;
		circleRigidBody3->xVelocity = 0;
		circleRigidBody3->yVelocity = 0;
		circleRigidBody3->radius = 10;
		circleRigidBody3->inverseMass = 1.0f / (circleRigidBody3->radius * circleRigidBody3->radius * M_PI);
		rigidBodies.push_back(circleRigidBody3);
		
		LengthConstraint* lengthConstraint = new LengthConstraint();
		lengthConstraint->length = 100;
		lengthConstraint->body1 = rigidBodies[0];
		lengthConstraint->body2 = rigidBodies[1];
		constraints.push_back(lengthConstraint);

		LengthConstraint* lengthConstraint2 = new LengthConstraint();
		lengthConstraint2->length = 100;
		lengthConstraint2->body1 = rigidBodies[1];
		lengthConstraint2->body2 = rigidBodies[2];
		constraints.push_back(lengthConstraint2);

		LengthConstraint* lengthConstraint3 = new LengthConstraint();
		lengthConstraint3->length = 100;
		lengthConstraint3->body1 = rigidBodies[2];
		lengthConstraint3->body2 = rigidBodies[3];
		constraints.push_back(lengthConstraint3);

		GravityForce* gravityForce = new GravityForce();
		gravityForce->force = 9.8f;
		gravityForce->rigidBodies = &rigidBodies;
		forces.push_back(gravityForce);

		UserForce* userForce = new UserForce();
		userForce->force = 1.0f;
		userForce->rigidBodies = &rigidBodies;
		userForce->pge = this;
		forces.push_back(userForce);
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/*if (GetKey(olc::SPACE).bPressed)
		{*/
			int substeps = 1000;
			double dt = 1.0f / 60.0f / substeps;
			for (int i = substeps; i--;)
				Stimulate(dt);
		//}

		DrawSystem();

		return true;
	}
};

int main()
{
	SystemVisualizer systemVisualizer;
	if (systemVisualizer.Construct(1920 * 0.666666f, 1080 * 0.666666f, 1, 1))
		systemVisualizer.Start();
	return 0;
}