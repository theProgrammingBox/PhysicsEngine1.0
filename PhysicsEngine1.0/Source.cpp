#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Ball
{
public:
	double x;
	double y;
	double vx;
	double vy;
	double radius;
	double mass;
	double angle;
	double angularVelocity;
};

class SystemVisualizer : public olc::PixelGameEngine
{
public:
	std::vector<Ball> balls;
	
	SystemVisualizer() { sAppName = "System Visualizer"; }
	
	bool OnUserCreate() override
	{
		balls.push_back({ ScreenWidth() / 2.0f, ScreenHeight() / 2.0f, 0.0f, 0.0f, 10.0f });
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		double fps = fElapsedTime / 1000.0f;
		double invfps = 1000.0f / fElapsedTime;
		for (int i = 1000; i--;)
		{
			for (auto& ball : balls)
			{
				ball.vx += 10.0f * fps;
				ball.vy += 100.0f * fps;
				double tempX = ball.x;
				double tempY = ball.y;
				double tempVX = ball.vx;
				double tempVY = ball.vy;
				ball.x += ball.vx * fps;
				ball.y += ball.vy * fps;
				if (ball.y + ball.radius > ScreenHeight())
					ball.y = ScreenHeight() - ball.radius;
				if (ball.x + ball.radius > ScreenWidth())
					ball.x = ScreenWidth() - ball.radius;
				if (ball.x - ball.radius < 0)
					ball.x = ball.radius;
				ball.vx = (ball.x - tempX) * invfps;
				ball.vy = (ball.y - tempY) * invfps;
				double normalX = ball.vx - tempVX;
				double normalY = ball.vy - tempVY;
				ball.vx += normalX;
				ball.vy += normalY;
				
				
				DrawCircle(ball.x, ball.y, ball.radius, olc::WHITE);
				DrawLine(ball.x, ball.y, ball.x + ball.vx, ball.y + ball.vy, olc::RED);

			}
		}
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