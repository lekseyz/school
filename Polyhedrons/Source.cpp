#include<iostream>

#define OLC_PGE_APPLICATION
#include "geometry.h"
#include "model.h"
#include "olcPixelGameEngine.h"

const double PI = 3.1415;
typedef std::vector<std::vector<Vec3f>> figureType;


figureType createFigure(Model& model)
{
	figureType figure;

	figure.resize(model.nfaces());

	std::vector<int> temp;
	Vec3f vtemp;
	for (int i = 0; i < model.nfaces(); i++)
	{
		temp = model.face(i);
		for (int j = 0; j < temp.size(); j++)
		{
			vtemp = model.vert(temp[j]);
			figure[i].push_back(vtemp);
		}
	}
	return figure;
}

class Program : public olc::PixelGameEngine
{
public:
	Program(){}

	void initFigures(figureType a, figureType b, figureType c, figureType d, figureType e)
	{
		tetrahedron = a;
		hexahedron = b;
		octahedron = c;
		dodecahedron = d;
		icosahedron = e;
	}

	void rotate(float& x, float& y, const double& angle)
	{
		float tmp = x;
		x = x * std::cos(angle) - y * std::sin(angle);
		y = tmp * std::sin(angle) + y * std::cos(angle);
	}

	bool OnUserCreate() override
	{
		light_dir = Vec3f(-1, 0, 0);
		figure = tetrahedron;
		doRotate = true;
		showMesh = false;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(0);

		if (GetKey(olc::K1).bPressed) figure = tetrahedron;
		if (GetKey(olc::K2).bPressed) figure = hexahedron;
		if (GetKey(olc::K3).bPressed) figure = octahedron;
		if (GetKey(olc::K4).bPressed) figure = dodecahedron;
		if (GetKey(olc::K5).bPressed) figure = icosahedron;

		if (GetKey(olc::R).bPressed) doRotate = !doRotate;
		if (GetKey(olc::M).bPressed) showMesh = !showMesh;

		std::vector<std::vector<olc::vi2d>> coord;
		coord.resize(figure.size());
		if(doRotate)
			for (int i = 0; i < figure.size(); i++)
			{
				for (int j = 0; j < figure[i].size(); j++)
				{
					rotate(figure[i][j].z, figure[i][j].y, PI / 4 * fElapsedTime);
					rotate(figure[i][j].x, figure[i][j].y, PI / 4 * fElapsedTime);
				}
			}

		for (int i = 0; i < figure.size(); i++)
		{
			for (int j = 0; j < figure[i].size(); j++)
			{
				coord[i].push_back(olc::vi2d((figure[i][j].z + 1.) * 400, (figure[i][j].y + 1) * 400));
			}
		}
		
		for (int i = 0; i < coord.size(); i++)
		{
			Vec3f n = (figure[i][2] - figure[i][0]) ^ (figure[i][1] - figure[i][0]);
			n.normalize();
			float intensity = n * light_dir;
			if(intensity > 0)
			{
				FillTriangle(coord[i][0], coord[i][1], coord[i][2], olc::Pixel(255 * intensity, 255 * intensity, 255 * intensity, 255));
				if(showMesh) DrawTriangle(coord[i][0], coord[i][1], coord[i][2], olc::RED);
			}
		}
		return true;
	}

private:
	figureType tetrahedron;
	figureType hexahedron;
	figureType octahedron;
	figureType dodecahedron;
	figureType icosahedron;
	figureType figure;

	bool showMesh;
	bool doRotate;

	Vec3f light_dir;
};

int main()
{
	Program prog;

	Model tetrahedron  ("./resources/tetrahedron.obj");
	Model hexahedron   ("./resources/hexahedron.obj");
	Model octahedron   ("./resources/octohedron.obj");
	Model dodecahedron ("./resources/dodecahedron.obj");
	Model icosahedron  ("./resources/icosahedron.obj");
	
	
	

	prog.Construct(800, 800, 1, 1);
	prog.initFigures(createFigure(tetrahedron), createFigure(hexahedron), createFigure(octahedron), createFigure(dodecahedron), createFigure(icosahedron));
	prog.Start();

	return 0;
}