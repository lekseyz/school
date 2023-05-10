#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <condition_variable>
#include <atomic>
#include <complex>
#include <cstdlib>
#include <immintrin.h>
class Example : public olc::PixelGameEngine
{
	int *iFracral;
	long iterations = 64;
	double scale = 0.005;
	float defScale = scale;
	double a = 0.1f;
	olc::vd2d offSet{ 2.0, 2.0 };
	int numberOfFrames;
	int ifItPartOfMondelbrot(double coordinateX, double coordinateY)
	{
		float f = 0.1;
		olc::vd2d c{ coordinateX, coordinateY };
		olc::vd2d Z{ 0.0, 0.0 };
		register int i = 0;
		while ((Z.x * Z.x + Z.y * Z.y) < 4.0 && i < iterations) 
		{
			i++;
			Z = { (Z.x * Z.x) - (Z.y * Z.y), 2 * Z.x * Z.y };
			Z = { Z.x + coordinateX, Z.y + coordinateY };
		}
		return i;
	}


public:
	Example()
	{
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		numberOfFrames = 0;
		iFracral = new int(ScreenWidth() * ScreenHeight());
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::Pixel(255, 255, 255));

		olc::vd2d fourthCoordinateBefore = { ScreenWidth() / 2 * scale, ScreenHeight() / 2 * scale };
		if (GetKey(olc::Key::UP).bHeld) scale *= 0.9;
		if (GetKey(olc::Key::DOWN).bHeld) scale *= 1.1;
		olc::vd2d fourthCoordinateAfter  = { ScreenWidth() / 2 * scale, ScreenHeight() / 2 * scale };
		offSet -= (fourthCoordinateBefore - fourthCoordinateAfter);

		if (GetKey(olc::Key::W).bHeld) offSet.y += a;
		if (GetKey(olc::Key::A).bHeld) offSet.x += a;
		if (GetKey(olc::Key::S).bHeld) offSet.y -= a;
		if (GetKey(olc::Key::D).bHeld) offSet.x -= a;

		if (GetKey(olc::Key::Q).bHeld) a *= 0.1;
		if (GetKey(olc::Key::E).bHeld) a /= 0.1;

		if (GetKey(olc::Key::H).bHeld) iterations += 64;
		if (GetKey(olc::Key::L).bHeld) iterations -= 64;

		double X;
		double Y;
		double a, n;
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
			{
				X = (double)x * scale - offSet.x;
				Y = (double)y * scale - offSet.y;
				n = (double)ifItPartOfMondelbrot(X, Y);
				a = 0.1f;
				//With coloring
				Draw(x, y, olc::PixelF(0.5f * std::sin(a * n) + 0.5f, 0.5f * std::sin(a * n + 2.094f) + 0.5f, 0.5f * std::sin(a * n + 10.188f) + 0.5f));
				//With out coloring
				////if(n >= iterations-1)
				////	Draw(x, y, olc::BLACK);
			}
		return true;
	}
};



int main()
{
	Example demo;
	if (demo.Construct(800, 800, 1, 1))
		demo.Start();
	return 0;
}
