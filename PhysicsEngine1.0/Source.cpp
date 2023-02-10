#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define M_PI 3.14159265358979323846

class RigidBody
{
public:
	RigidBody() {};
	virtual ~RigidBody() {};

	virtual void MovePosition(double dx, double dy) = 0;
	virtual void MoveVelocity(double dx, double dy) = 0;
	virtual void UpdateVelocity(double dt) = 0;
	
	double xPosition;
	double yPosition;
	double xPastPosition;
	double yPastPosition;
	double xVelocity;
	double yVelocity;
	double radius;
	double inverseMass;
};

class Circle : public RigidBody
{
public:
	Circle() {};
	virtual ~Circle() {};
	
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
};

class FixedPoint : public RigidBody
{
public:
	FixedPoint() {};
	virtual ~FixedPoint() {};
	
	void MovePosition(double dx, double dy) override {};
	void MoveVelocity(double dx, double dy) override {};
	void UpdateVelocity(double dt) override {};
};

class Force
{
public:
	Force() {};
	virtual ~Force() {};

	virtual void Apply(double dt) = 0;
};

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

	double gravity;
	std::vector<RigidBody*> rigidBodies;
};

class Constraint
{
public:
	Constraint() {};
	virtual ~Constraint() {};

	virtual void Apply() = 0;
};

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
	
	double length;
	RigidBody* body1;
	RigidBody* body2;
};

class SystemVisualizer : public olc::PixelGameEngine
{
public:
	std::vector<RigidBody*> rigidBodies;
	std::vector<Force*> forces;
	std::vector<Constraint*> constraints;
	
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
		circle->xPosition = ScreenWidth() / 3;
		circle->yPosition = ScreenHeight() / 3;
		circle->xVelocity = 0;
		circle->yVelocity = 0;
		circle->radius = 10;
		circle->inverseMass = 1.0f / (circle->radius * circle->radius * M_PI);
		rigidBodies.push_back(circle);
		
		LengthConstraint* lengthConstraint = new LengthConstraint();
		lengthConstraint->length = 100;
		lengthConstraint->body1 = rigidBodies[0];
		lengthConstraint->body2 = rigidBodies[1];
		constraints.push_back(lengthConstraint);

		Gravity* gravity = new Gravity();
		gravity->gravity = 9.8f;
		gravity->rigidBodies = rigidBodies;
		forces.push_back(gravity);
		
		return true;
	}

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
		{
			DrawCircle(rigidBody->xPosition, rigidBody->yPosition, rigidBody->radius, olc::WHITE);
			DrawLine(rigidBody->xPosition, rigidBody->yPosition, rigidBody->xPosition + rigidBody->xVelocity, rigidBody->yPosition + rigidBody->yVelocity, olc::RED);
		}

		for (Constraint* constraint : constraints)
		{
			LengthConstraint* lengthConstraint = dynamic_cast<LengthConstraint*>(constraint);
			if (lengthConstraint)
			{
				RigidBody* body1 = lengthConstraint->body1;
				RigidBody* body2 = lengthConstraint->body2;
				DrawLine(body1->xPosition, body1->yPosition, body2->xPosition, body2->yPosition, olc::GREEN);
			}
		}
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