#pragma once

#include "RasterSurface.h"
#include "XTime.h"
//#include <cmath>
#include "Math.h"
#include "Utility.h"

//#include "vector3.h"
#include "Points.h"
//#include "Line.h"
#include "Transform.h"
#include "shaders.h"



#ifndef RAD
#define RAD 3.14156f / 180
#endif


//View will have no knowledge or information of the model, mesh or object its trying to draw. It simply Recieces a line
//of normalized points. Applies the worldspace transforms to it.
//Converts the line cooridinates from normalized space to screen space.
//Then updates the Raster Data array color at the respective indexes.


class View
{
public:
	struct Raster {
		int width;
		int height;
		float aspect_ratio;
		float aspect_inverse;
		unsigned int* data;
		float* depthbuffer;

		float FOV;
		float scale;
		float near_plane;
		float far_plane;
	};

private:
	static View* instance;
	Raster raster2d;
	vector3 view_angle;
	vector3 world_angle;

	/// <summary>
	/// Camera Represent a View Matrix
	/// </summary>
	Transform Camera;

	Transform viewport;
	Transform translation;
	Transform projection;

	Transform view_rotation;
	Transform world_rotation;

	//shaders shader;
	//World Model, a grid for this project
	// World Matrix
	// View Matrix - Camera Angle
	//Perspective Matrix
	// Scale Matrix
	View() {};
	void InitializeView(int _width, int _height);
	
public:
	~View();
	/// <summary>
	/// Used to Initialize the View Singleton
	/// </summary>
	/// <param name="_width"> #defined in main.cpp </param>
	/// <param name="_height"> #defined in main.cpp </param>
	/// <returns> Returns this singleton </returns>
	static View* Get_View(int _width, int _height);
	const Raster* GetRaster() const;
	/// <summary>
	/// Setter to change field of view during run time for some reason.
	/// </summary>
	void SetFOV_and_Scale(float _FOV);
	// Rotates the View around an axis
	void RotateCamera(vector3 _euler);
	void RotateWorld(vector3 _euler);
	//Resets Color to default in the raster array
	void ClearRaster();
	void ApplyLineToRaster(Line ln, Transform* _matrix);
	void ApplyLineToRaster(Tri tri, Transform* _matrix);
	void SchoolBarametricTriangle(Tri* tri, Transform* _matrix);
	void CalculateScreenSpace(Line ln);
	
	void ParametricLine(vector3 _start, vector3 _end, unsigned int _color); //(vector3 _start, vector3 _end);
	void PlotPixel(int _x, int _y, unsigned int _Color, float _zDepth);

	void UpdateCamera();
	void UpdateRotations(Transform* _matrix, vector3 _angles);
	void UpdateProjection();


	
};

