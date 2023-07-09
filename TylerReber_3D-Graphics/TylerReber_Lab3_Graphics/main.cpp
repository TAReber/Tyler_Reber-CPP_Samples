#include "View.h"
#include "Model.h"
#include "Controller.h"
#include "Points.h"
#include <thread>
#include "Utility.h"

//SOURCE https://learn.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDGB_MAP_ALLOC


#define WIDTH 750
#define HEIGHT 500

Model* InitializeGrid();
Model* InitializeCube();

Model* InitializeSingleTriangle();

/*
	The Decided to try to the MVC design patter for this lab.

	The model will contain the 3D model of vector points and the matrice

	The controller will be responsible for Manipulating the points and passing the data to the View. It might not have a user input,
	But it will have the functions to transform a model vector points. Because each object can have a unique transform, the view
	will need to handle the view transforms and each object I make will need to have the capacity to transform uniquely.

	The view will contain the the raster Data for the display Window. It will be a singleton because I only need 1

*/

View* View::instance = NULL;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	View* view = View::Get_View(WIDTH, HEIGHT);
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	view->RotateCamera(vector3(-18.0f, 0, 0));
	view->RotateWorld(vector3(0, 0, 0));
	
	//Create Cube and Grid for Lab 2
	Model* grid_mesh = InitializeGrid();
	Controller* grid = new Controller(view, grid_mesh);
	grid->SetTranslation(vector3(0, 0, 0));
	grid->SetScale(vector3(1, 1, 1));

	Model* box = InitializeCube();
	Controller* cube = new Controller(view, box);
	cube->SetTranslation(vector3(0, 0.25f, 0));
	cube->SetScale(vector3(1, 1, 1));

	Model* poly = InitializeSingleTriangle();
	Controller* triangle = new Controller(view, poly);
	triangle->SetTranslation(vector3(0, 0.25f, 0));
	triangle->SetScale(vector3(1, 1, 1));
	triangle->UpdateAngle(vector3(0, 0, 0));

	bool isRunning = true;


	view->UpdateCamera();
	RS_Initialize("Tyler A Reber", WIDTH, HEIGHT);

	while (isRunning) {
		view->ClearRaster();

		//Camera Rotation Test
		//view->RotateCamera(vector3(0, 0, 0));
		//view->RotateWorld(vector3(0, 0.1f, 0));

		grid->UpdateAngle(vector3(0, 0, 0));

		//cube->UpdateAngle(vector3(0, 0.01f, 0));

		triangle->UpdateAngle(vector3(0, 0.1f, 0));
		cube->UpdateAngle(vector3(0, 0.1f, 0));
		isRunning = RS_Update(view->GetRaster()->data, WIDTH * HEIGHT);
	}
	RS_Shutdown();

	delete grid;
	delete cube;
	delete triangle;
	delete view;

	_CrtDumpMemoryLeaks();
	return 0;
}

Model* InitializeCube() {
	WireFrame* box = new WireFrame(12);

	unsigned int color = 0xffff0000;

	float p = 0.25f;
	float n = -0.25f;

	//Front
	vector4 ftl(n, p, n, 1);
	vector4 fbl(n, n, n, 1);
	vector4 ftr(p, p, n, 1);
	vector4 fbr(p, n, n, 1);

	//Back
	vector4 btl(n, p, p, 1);
	vector4 bbl(n, n, p, 1);
	vector4 btr(p, p, p, 1);
	vector4 bbr(p, n, p, 1);

	//Define 12 Lines
	// (f = front, b = back), (t = top, b = bottom), (left or right)
	box->AddPoints(Line(ftl, ftr, color));
	box->AddPoints(Line(ftr, fbr, color));
	box->AddPoints(Line(ftl, fbl, color));
	box->AddPoints(Line(fbl, fbr, color));

	box->AddPoints(Line(ftl, btl, color));
	box->AddPoints(Line(ftr, btr, color));
	box->AddPoints(Line(fbl, bbl, color));
	box->AddPoints(Line(fbr, bbr, color));

	box->AddPoints(Line(btl, btr, color));
	box->AddPoints(Line(btr, bbr, color));
	box->AddPoints(Line(btl, bbl, color));
	box->AddPoints(Line(bbl, bbr, color));

	return box;
}

Model* InitializeGrid() {
	WireFrame* newGrid = new WireFrame(22);
	
	unsigned int color = 0xffffffff;

	float x = 0.5;
	float y = 0;
	float z = 0;
	float w = 0;

	for (int i = 0; i < 11; i++) {
		z = (i * 0.1f) - 0.5f;
		vector4 start(-x, y, z, 1);
		vector4 end(x, y, z, 1);
		newGrid->AddPoints(Line(start, end, color));
	}

	z = 0.5f;

	for (int i = 0; i < 11; i++) {
		x = (i * 0.1f) - 0.5f;
		vector4 start(x, y, -z, 1);
		vector4 end(x, y, z, 1);
		newGrid->AddPoints(Line(start, end, color));

	}

	return newGrid;
}

Model* InitializeSingleTriangle() {
	Polygonal* poly = new Polygonal(6);
	
	unsigned int color = 0xffff0000;

	float p = 0.25f;
	float n = -0.25f;

	//Front
	vector4 ftl(n, p, n, 1);
	vector4 fbl(n, n, n, 1);
	vector4 ftr(p, p, n, 1);
	vector4 fbr(p, n, n, 1);

	//Back
	vector4 btl(n, p, p, 1);
	vector4 bbl(n, n, p, 1);
	vector4 btr(p, p, p, 1);
	vector4 bbr(p, n, p, 1);

	//front
	Tri tri_1(ftl, ftr, fbr, 0x00ff0000);
	tri_1.SetUV(vector2(0, 0), vector2(0, 1), vector2(1, 1)); //right = 1 on x // bottom = 1 on y
	poly->AddPoints(tri_1);
	Tri tri_2(ftl, fbr, fbl, 0x00ff0000);
	tri_2.SetUV(vector2(0, 0), vector2(1, 1), vector2(0, 1));
	poly->AddPoints(tri_2);

	//left
	Tri tri_3(btl, ftl, fbl, 0x0000ff00);
	tri_3.SetUV(vector2(0, 0), vector2(0, 1.0f), vector2(1.0f, 1.0f));
	poly->AddPoints(tri_3);

	Tri tri_4(btl, fbl, bbl, 0x0000ff00);
	tri_4.SetUV(vector2(0, 0), vector2(1.0f, 1.0f), vector2(0, 1.0f));
	poly->AddPoints(tri_4);

	////right
	Tri tri_5(ftr, btr, bbr, 0x000000ff);
	tri_5.SetUV(vector2(0, 0), vector2(0, 1.0f), vector2(1.0f, 1.0f));
	poly->AddPoints(tri_5);
	Tri tri_6(ftr, bbr, fbr, 0x000000ff);
	tri_6.SetUV(vector2(0, 0), vector2(1.0f, 1.0f), vector2(0, 1.0f));
	poly->AddPoints(tri_6);
	

	//////back
	Tri tri_7(btr, btl, bbl, 0x00ff00ff);
	tri_7.SetUV(vector2(0, 0), vector2(0, 1.0f), vector2(1.0f, 1.0f));
	poly->AddPoints(tri_7);
	Tri tri_8(btr, bbl, bbr, 0x00ff00ff);
	tri_8.SetUV(vector2(0, 0), vector2(1.0f, 1.0f), vector2(0, 1.0f));
	poly->AddPoints(tri_8);
	
	//////top
	Tri tri_9(ftl, btr, ftl, 0x000f00ff0);
	tri_9.SetUV(vector2(0, 0), vector2(0, 1.0f), vector2(1.0f, 1.0f));
	poly->AddPoints(tri_9);	
	Tri tri_10(ftl, btl, btr, 0x00f00ff0);
	tri_10.SetUV(vector2(0, 0), vector2(1.0f, 1.0f), vector2(0, 1.0f));
	poly->AddPoints(tri_10);
	
	//////bottom
	Tri tri_11(fbl, bbr, bbl, 0x00ffffff);
	tri_11.SetUV(vector2(0, 0), vector2(0, 1.0f), vector2(1.0f, 1.0f));
	poly->AddPoints(tri_11);
	Tri tri_12(fbl, fbr, bbr, 0x00ffffff);
	tri_12.SetUV(vector2(0, 0), vector2(1.0f, 1.0f), vector2(0, 1.0f));
	poly->AddPoints(tri_12);
	
	return poly;
}