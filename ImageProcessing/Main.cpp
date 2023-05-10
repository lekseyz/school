#include "tga_library.h"
#include <iostream>
#include <string>

unsigned char* readImage(TGAImage &image)
{
	unsigned char* buffer;
	std::string filePath;
	std::cin >> filePath;
	if (!image.read_tga_file(filePath.c_str()))
	{
		std::cout << "Bad path.\n";
		return nullptr;
	}
	buffer = (unsigned char*)malloc(image.get_height() * image.get_width() * image.get_bytespp());
	buffer = image.buffer();
	for (int i = 0; i < image.get_width() * image.get_height() * image.get_bytespp(); i++)
	{
		(int)buffer[i];
	}
	return buffer;
}

bool writeImage(TGAImage& image)
{
	std::string filePath;
	std::cin >> filePath;
	if (!image.write_tga_file(filePath.c_str()))
	{
		std::cout << "Bad path.\n";
		return false;
	}
}

void toGray(TGAImage& image)
{
	TGAImage newimage(image.get_width(), image.get_height(), 1);
	for (int x = 0; x < image.get_width(); x++)
	{
		for (int y = 0; y < image.get_height(); y++)
		{
			newimage.set(x, y, TGAColor(image.get(x, y).r * 0.3 + image.get(x, y).g * 0.59 + image.get(x, y).b * 0.11, 1));
		}
	}
	image = newimage;
}

void toNegative(TGAImage& image)
{
	for (int x = 0; x < image.get_width(); x++)
	{
		for (int y = 0; y < image.get_height(); y++)
		{
			image.set(x, y, TGAColor(255 - image.get(x, y).r, 255 - image.get(x, y).g, 255 - image.get(x, y).b, image.get(x, y).a));
		}
	}
}

void toGreyNegative(TGAImage& image)
{
	for (int x = 0; x < image.get_width(); x++)
	{
		for (int y = 0; y < image.get_height(); y++)
		{
			unsigned char med = (image.get(x, y).r + image.get(x, y).g + image.get(x, y).b) / 3;
			image.set(x, y, TGAColor(255 - med, 255 - med, 255 - med, image.get(x, y).a));
		}
	}
}

void patterConvertion(TGAImage& image)
{
	unsigned long long r, g, b, rmid = 0, gmid = 0, bmid = 0;
	std::cin >> r >> g >> b;
	for (int x = 0; x < image.get_width(); x++)
	{
		for (int y = 0; y < image.get_height(); y++)
		{
			rmid += image.get(x, y).r;
			gmid += image.get(x, y).g;
			bmid += image.get(x, y).b;
		}
	}

	rmid /= image.get_height() * image.get_width();
	gmid /= image.get_height() * image.get_width();
	bmid /= image.get_height() * image.get_width();

	for (int x = 0; x < image.get_width(); x++)
	{
		for (int y = 0; y < image.get_height(); y++)
		{
			image.set(x, y, TGAColor(image.get(x, y).r * ((float)r / rmid), image.get(x, y).g * ((float)g / gmid), image.get(x, y).b * ((float)b / bmid), image.get(x, y).a));
		}
	}
}

int main()
{
	using namespace std;
	unsigned char* imageBuffer = nullptr;
	TGAImage image;

	char ch;
	

	while(true)
	{
		cin >> ch;
		if (ch == '-')
		{
			cin >> ch;
			switch(ch)
			{
			case 'r':
				imageBuffer = readImage(image);
				cout << "Image read\n";
				break;

			case 'w':
				writeImage(image);
				cout << "Image written\n";
				break;

			case 'g':
				toGray(image);
				break;

			case 'n':
				toNegative(image);
				break;

			case 'a':
				toGreyNegative(image);
				break;

			case 'p':
				patterConvertion(image);
				break;

			default:
				cout << "I don't know the command: -" << ch << endl;
				cout << "For help type -h\n";
			}
		}
		if (ch == '/')
		{
			break;
		}
	}
}