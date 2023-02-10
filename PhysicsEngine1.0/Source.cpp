#include "LengthConstraint.h"
#include "Gravity.h"
#include "FixedPoint.h"
#include "Circle.h"

class SystemVisualizer : public olc::PixelGameEngine
{
public:
	std::vector<RigidBody*> rigidBodies;
	std::vector<Force*> forces;
	std::vector<Constraint*> constraints;

	void Stimulate(double dt, double gravity)
	{
		for (Force* force : forces)
			force->Apply(dt);
		for (RigidBody* rigidBody : rigidBodies)
		{
			rigidBody->xPastPosition = rigidBody->xPosition;
			rigidBody->yPastPosition = rigidBody->yPosition;
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
		FixedPoint* fixedPoint = new FixedPoint();
		fixedPoint->xPosition = ScreenWidth() / 2;
		fixedPoint->yPosition = ScreenHeight() / 2;
		fixedPoint->xVelocity = 0;
		fixedPoint->yVelocity = 0;
		fixedPoint->radius = 10;
		fixedPoint->inverseMass = 0.0f;
		rigidBodies.push_back(fixedPoint);
		
		Circle* circle = new Circle();
		circle->xPosition = rigidBodies[0]->xPosition + 100;
		circle->yPosition = rigidBodies[0]->yPosition;
		circle->xVelocity = 0;
		circle->yVelocity = 0;
		circle->radius = 10;
		circle->inverseMass = 1.0f / (circle->radius * circle->radius * M_PI);
		rigidBodies.push_back(circle);

		Circle* circle2 = new Circle();
		circle2->xPosition = rigidBodies[1]->xPosition + 100;
		circle2->yPosition = rigidBodies[1]->yPosition;
		circle2->xVelocity = 0;
		circle2->yVelocity = 0;
		circle2->radius = 10;
		circle2->inverseMass = 1.0f / (circle2->radius * circle2->radius * M_PI);
		rigidBodies.push_back(circle2);

		Circle* circle3 = new Circle();
		circle3->xPosition = rigidBodies[2]->xPosition + 100;
		circle3->yPosition = rigidBodies[2]->yPosition;
		circle3->xVelocity = 0;
		circle3->yVelocity = 0;
		circle3->radius = 10;
		circle3->inverseMass = 1.0f / (circle3->radius * circle3->radius * M_PI);
		rigidBodies.push_back(circle3);
		
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

		Gravity* gravity = new Gravity();
		gravity->gravity = 9.8f;
		gravity->rigidBodies = rigidBodies;
		forces.push_back(gravity);
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/*if (GetKey(olc::SPACE).bPressed)
		{*/
			int substeps = 1000;
			double dt = 1.0f / 10.0f / substeps;
			double gravity = 9.8;
			for (int i = 0; i < substeps; i++)
				Stimulate(dt, gravity);
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