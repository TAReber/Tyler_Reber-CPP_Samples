#include "View.h"


View::~View()
{
	delete raster2d.data;
	delete raster2d.depthbuffer;
}

void View::InitializeView(int _width, int _height)
{
	instance->raster2d.width = _width;
	instance->raster2d.height = _height;

	instance->raster2d.aspect_ratio = (float)_width / (float)_height;
	instance->raster2d.aspect_inverse = (float)_height / (float)_width;
	instance->raster2d.data = new unsigned int[_width * _height];
	instance->raster2d.depthbuffer = new float[_width * _height];

	SetFOV_and_Scale(90.0f);
	instance->raster2d.near_plane = 0.1f;
	instance->raster2d.far_plane = 10.0f;

	view_angle = vector3(0, 0, 0);
	world_angle = vector3(0, 0, 0);

	//UpdateRotations();

	float trans[4][4] = {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0},
		{ 0, 0, 1, 0},
		{ 0, 0, -1, 1 } };
	translation.SetTransform(trans);

	UpdateProjection();

}



View* View::Get_View(int _width, int _height) {
	if (!instance) {
		instance = new View();
		instance->InitializeView(_width, _height);
	}
	return instance;
}

const View::Raster* View::GetRaster() const
{
	return &raster2d;
}

void View::ClearRaster()
{
	unsigned int BackGround_Color = 0x00000000;

	for (int i = 0; i < raster2d.width * raster2d.height; i++) {
		raster2d.data[i] = BackGround_Color;
		raster2d.depthbuffer[i] = -1;
	}
}


void View::SetFOV_and_Scale(float _FOV)
{
	raster2d.FOV = _FOV;
	raster2d.scale = 1 / std::tan((raster2d.FOV * 0.5f) * RAD);
}

void View::RotateCamera(vector3 _euler)
{
	view_angle = view_angle + _euler;
	UpdateRotations(&view_rotation, view_angle);
}

void View::RotateWorld(vector3 _euler)
{
	world_angle = world_angle + _euler;
	UpdateRotations(&world_rotation, world_angle);
}

void View::UpdateRotations(Transform* _matrix, vector3 _angles)
{

	float x_rot[4][4] = {
	{ 1, 0, 0, 0 },
	{ 0, std::cos(_angles.x * RAD), -std::sin(_angles.x * RAD), 0},
	{ 0, std::sin(_angles.x * RAD), std::cos(_angles.x * RAD), 0},
	{ 0, 0, 0, 1 } };
	Transform xrot(x_rot);

	float y_rot[4][4] = {
		{ std::cos(_angles.y * RAD), 0, std::sin(_angles.y * RAD), 0},
		{ 0, 1, 0, 0},
		{ -std::sin(_angles.y * RAD), 0, std::cos(_angles.y * RAD), 0},
		{ 0, 0, 0, 1 } };
	Transform yrot(y_rot);

	float z_rot[4][4] = {
		{ std::cos(_angles.z * RAD), -std::sin(_angles.z * RAD), 0, 0},
		{ std::sin(_angles.z * RAD), std::cos(_angles.z * RAD), 0, 0},
		{ 0, 0, 1, 0},
		{ 0, 0, 0, 1 } };
	Transform zrot(z_rot);

	*_matrix = zrot * yrot * xrot; //z_rotation_matrix * y_rotation_matrix * x_rotation_matrix;

	UpdateCamera();
}

void View::UpdateCamera()
{
	//Apply Rotations;
	//Camera = translation * (z_rotation_matrix * y_rotation_matrix * x_rotation_matrix);
	Camera = translation * view_rotation;// *world_rotation;
	//inverse;
	Camera = FastInverse(Camera);
	//Camera = Camera.FastInverse();
	world_rotation = FastInverse(world_rotation);
	//world_rotation = world_rotation.FastInverse();
}


void View::ApplyLineToRaster(Line ln, Transform* _local)
{

	vector4 s = (*_local * Camera) * world_rotation * ln.start;
	vector4 e = (*_local * Camera) * world_rotation * ln.end;

	//s = world_rotation * s;
	//e = world_rotation * e;

	//Projection Matrix
	s = projection * s;
	e = projection * e;

	//Perspective Divide only if line is within the range of the planes
	if (NDC_Space_Checker(s.z, e.z, raster2d.near_plane, raster2d.far_plane)) {
		//I Took the recciprocal of w and did a Perspective Multiplication
		float s_recip = 1 / s.w;
		float e_recip = 1 / e.w;

		vector4 start(s.x * s_recip, s.y * s_recip, s.z, 1);
		vector4 end(e.x * e_recip, e.y * e_recip, e.z, 1);

		//PrintVector(start);
		//PrintVector(end);
		unsigned int color = ln.color;
		CalculateScreenSpace(Line(start, end, color));
	}
}

void View::ApplyLineToRaster(Tri _tri, Transform* _local) {

	//vector4 a = _tri.a;
	//vector4 b = _tri.b;
	//vector4 c = _tri.c;

	vector4 a = (*_local * Camera) * world_rotation * _tri.a;
	vector4 b = (*_local * Camera) * world_rotation * _tri.b;
	vector4 c = (*_local * Camera) * world_rotation * _tri.c;

	a = projection * a;
	b = projection * b;
	c = projection * c;
	
	////I Took the recciprocal of w and did a Perspective Multiplication
	float a_recip = 1 / a.w;
	float b_recip = 1 / b.w;
	float c_recip = 1 / c.w;

	a = vector4(a.x * a_recip, a.y * a_recip, a.z, 1);
	b = vector4(b.x * b_recip, b.y * b_recip, b.z, 1);
	c = vector4(c.x * c_recip, c.y * c_recip, c.z, 1);

	//float b_max, g_max, a_max = { 0 };
	float a_pnt, b_pnt, c_pnt = { 0 };

	//Notes
	//Triangles work in NDC Space
	// Barycentric coordinates the ratio of distance between triangle points.
	// Calculate alpha, beta and gamma

	//Calculates the maximum distance I can be from a the line.

	for (int y = 0; y < raster2d.height; y++) {
		for (int x = 0; x < raster2d.width; x++) {

			float ndc_x = ((float)x / (float)(raster2d.width >> 1)) - 1;
			float ndc_y = -(((float)y / (float)(raster2d.height >> 1)) - 1);
			vector4 p(ndc_x, ndc_y, 0, 0);

			a_pnt = ImpliciteLineEquation(Line(a, b, 0), p);
			b_pnt = ImpliciteLineEquation(Line(b, c, 0), p);
			c_pnt = ImpliciteLineEquation(Line(c, a, 0), p);
			
			if((a_pnt <= 0 && b_pnt <= 0 && c_pnt <= 0) || (a_pnt >= 0 && b_pnt >= 0 && c_pnt >= 0))
			{

				//std::cout << test << std::endl;
				PlotPixel(x, y, 0xffff0000, 1);
			}
			else {
				//std::cout << test << std::endl;
			}
		}
	}


	unsigned int color = _tri.color;
	//CalculateScreenSpace(Tri(a, b, c, color));

}



void View::CalculateScreenSpace(Line ln)
{
	/* Convert Normalized device cooridinates to screen Space
		NDC are a range between -1 to +1 in cartesian cooridinates.

		# BUG -- If the component is outside that range, Its not needed to be converted
		to screen space or drawn.

		The chellenge is the NDC roll over, so end points will turn over and draw
		once the object rotates far enough.

		In order to draw a line. Both x values need to be in NDC space.
		Both Y values need to be in NDC Space.
	*/

	float sx = ln.start.x + 1;
	float ex = ln.end.x + 1;
	float sy = 1 - ln.start.y;
	float ey = 1 - ln.end.y;

	if (NDC_Space_Checker(sx, ex, 0, 2) && NDC_Space_Checker(sy, ey, 0, 2)) {

		float start_x = sx * (raster2d.width >> 1);
		float start_y = sy * (raster2d.height >> 1);
		vector3 start(start_x, start_y, 0);

		float end_x = ex * (raster2d.width >> 1);
		float end_y = ey * (raster2d.height >> 1);
		vector3 end(end_x, end_y, 0);
		unsigned int color = ln.color;
		ParametricLine(start, end, color);
	}


}

void View::ParametricLine(vector3 _start, vector3 _end, unsigned int _color)
{


	float deltax = std::fabsf(_end.x - _start.x);
	float deltay = std::fabsf(_end.y - _start.y);
	//Find the Magnitude with Pythagorean
	int length = std::sqrt(deltax * deltax + deltay * deltay);

	//int length = std::fmaxf(deltax, deltay);

	for (int i = 0; i < length; i++) {
		float ratio = (float)i / (float)length;

		int x = (_end.x - _start.x) * ratio + _start.x + 0.5f;
		//x = Clamp(x, raster2d.width - 1);
		int y = (_end.y - _start.y) * ratio + _start.y + 0.5f;
		//y = Clamp(y, raster2d.height - 1);
		
		if((x >= 0 && x < raster2d.width) && (y >= 0 && y < raster2d.height))
			PlotPixel(x, y, _color, 1);
	}

}

void View::PlotPixel(int _x, int _y, unsigned int _color, float _zDepth)
{
	//unsigned int col = _color;

	//PixelShader = &PS_Blue;
	//PixelShader(col);


	if (_zDepth > raster2d.depthbuffer[_y * raster2d.width + _x]) {
		raster2d.depthbuffer[_y * raster2d.width + _x] = _zDepth;
		raster2d.data[_y * raster2d.width + _x] = _color;
	}

	

}

void View::UpdateProjection()
{	
	//Aspect Ratio Math Error Correction
	/*
		#BUG >> Multiplying the scale by the aspect ratio stretches images by that amount.
		That aspect ratio is already applied, so a 2:1 aspect ratio will double the width, multiplying it again will quadruple it.
		
		So I want to multiply it by the inverse to make apear like a 1:1 aspect ratio.

		The height will do that same thing. If I assume the view window will always be wider than the height,
		then I can just divide the x_scale by the aspect ratio. If the height is greater than the width, I can do the same
		to hieght.

		The goal of this algorithim to convert a 2:1 aspect ratio to a 1:1 aspect ratio before applying it to the x and y scales.
	*/

	float x_ratio = 1;
	float y_ratio = 1;

	if (raster2d.aspect_ratio > 1)
		x_ratio = raster2d.scale * raster2d.aspect_inverse;
	else
		y_ratio = raster2d.scale * raster2d.aspect_ratio;

	projection.transform[0][0] = raster2d.scale * x_ratio;
	projection.transform[1][1] = raster2d.scale * y_ratio;
	projection.transform[2][2] = raster2d.far_plane / (raster2d.far_plane - raster2d.near_plane);
	projection.transform[3][2] = -((raster2d.far_plane * raster2d.near_plane) / (raster2d.far_plane - raster2d.near_plane)); 
	projection.transform[2][3] = 1;
}


void View::SchoolBarametricTriangle(Tri* _tri, Transform* _local)
{
	vector4 a = (*_local * Camera) * world_rotation * _tri->a;
	vector4 b = (*_local * Camera) * world_rotation * _tri->b;
	vector4 c = (*_local * Camera) * world_rotation * _tri->c;

	a = projection * a;
	b = projection * b;
	c = projection * c;

	//I Took the recciprocal of w and did a Perspective Multiplication
	float a_recip = 1 / a.w;
	float b_recip = 1 / b.w;
	float c_recip = 1 / c.w;

	a = vector4(a.x * a_recip, a.y * a_recip, a.z, 1);
	b = vector4(b.x * b_recip, b.y * b_recip, b.z, 1);
	c = vector4(c.x * c_recip, c.y * c_recip, c.z, 1);

	float A, B, C = { 0 };
	float alpha, beta, gamma = { 0 };

	//Notes
	//Triangles work in NDC Space
	// Barycentric coordinates the ratio of distance between triangle points.
	// Calculate alpha, beta and gamma

	//Calculates the maximum distance I can be from a the line on each axis.
	A = ImpliciteLineEquation(Line(c, b, 0), a);
	B = ImpliciteLineEquation(Line(a, c, 0), b);
	C = ImpliciteLineEquation(Line(b, a, 0), c);

	//Check Direction of Triangle using the center point.
	//If Interplolated z value is less than 0, the back side is facing the view.
	if ((A * a.z + B * b.z + C * c.z) >= 0) {

		//Better Brute
		float xstart = 0;
		float xend = 0;
		xstart = (a.x < b.x ? a.x : b.x);
		xstart = (xstart < c.x ? xstart : c.x);
		xend = (a.x > b.x ? a.x : b.x);
		xend = (xend > c.x ? xend : c.x);

		float ystart = 0;
		float yend = 0;
		ystart = (a.y > b.y ? a.y : b.y);
		ystart = (ystart > c.y ? ystart : c.y);
		yend = (a.y < b.y ? a.y : b.y);
		yend = (yend < c.y ? yend : c.y);

		vector3 start = Convert_NDC_to_ScreenSpace(vector4(xstart, ystart, 0, 0), raster2d.width, raster2d.height);
		vector3 end = Convert_NDC_to_ScreenSpace(vector4(xend, yend, 0, 0), raster2d.width, raster2d.height);

		for (int y = start.y; y < end.y; y++) {
			float depth = 0;
			for (int x = start.x; x < end.x; x++) {

				float ndc_x = ((float)x / (float)(raster2d.width >> 1)) - 1;
				float ndc_y = -(((float)y / (float)(raster2d.height >> 1)) - 1);
				vector4 p(ndc_x, ndc_y, 0, 0);

				alpha = ImpliciteLineEquation(Line(c, b, 0), p); //A
				beta = ImpliciteLineEquation(Line(a, c, 0), p); //B
				gamma = ImpliciteLineEquation(Line(b, a, 0), p); //C

				//If Triangle face is wrong way, no pixels will be drawn for that triangle


				vector3 ratio((alpha / A), (beta / B), (gamma / C) );
				if ((ratio.x >= 0 && ratio.x <= 1) && (ratio.y >= 0 && ratio.y <= 1) && (ratio.z >= 0 && ratio.z <= 1))
				{
					//Get UV Coordinates
					float uv_x = float(ratio.x * _tri->uv_a.x + ratio.y * _tri->uv_b.x + ratio.z * _tri->uv_c.x);
					float uv_y = float(ratio.x * _tri->uv_a.y + ratio.y * _tri->uv_b.y + ratio.z * _tri->uv_c.y);
					//std::cout << uv_x << " " << uv_y << std::endl;
					unsigned int color = PS_Image(uv_x, uv_y);

					//Barycentric Interoplation
					float depth = alpha * a.z + beta * b.z + gamma * c.z;
					PlotPixel(x, y, color, depth);

				}
			}
		}
	}




}

