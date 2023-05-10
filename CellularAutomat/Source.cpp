#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <utility>
#include <iostream>
#include <thread>
#include <chrono>

const int WIDTH = 800;
const int HEIGHT = 800;

unsigned char fild[WIDTH * HEIGHT];
unsigned char secondFild[WIDTH * HEIGHT];

int mod(const int& first, const int& second)
{
	if (first < 0) return second - first % second;
	else return first % second;
}

int translateCoord(int x, int y)
{
	x = mod(x, WIDTH);
	y = mod(y, HEIGHT);
	return y * WIDTH + x;
}

class Automat : public olc::PixelGameEngine
{
public:
	Automat()
	{
	
	}

	bool OnUserCreate() override
	{
		for (int i = 0; i < WIDTH * HEIGHT; i++)
		{
			fild[i] = rand() % 2;
		}
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		FillRect(0, 0, WIDTH, HEIGHT, olc::BLACK);  //For updating screen
		
		//using namespace std::chrono_literals;
		//std::this_thread::sleep_for(16ms);
		
		int temp = 0;
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				temp = fild[translateCoord(x-1, y+1)] + fild[translateCoord(x, y+1)] + fild[translateCoord(x+1, y+1)] +
										fild[translateCoord(x-1, y)] + fild[translateCoord(x+1, y)] +
						fild[translateCoord(x-1, y-1)] + fild[translateCoord(x, y-1)] + fild[translateCoord(x+1, y-1)];

				if (temp == 3)
				{
					secondFild[translateCoord(x, y)] = 1;
				}
				else if (temp == 2)
				{
					secondFild[translateCoord(x, y)] = fild[translateCoord(x, y)];
				}
				else
				{
					secondFild[translateCoord(x, y)] = 0;
				}
				temp = 0;
			}
		}
		std::copy(secondFild, secondFild + WIDTH * HEIGHT, fild);

		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (fild[translateCoord(j, i)]) Draw(j, i);
			}
		}
		return true;
	}
};

int main()
{
	Automat program;
	program.Construct(WIDTH, HEIGHT, 2, 2);
	program.Start();
	return 0;
}