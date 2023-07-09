#pragma once
#include "Transform.h"
#include "Points.h"
#include <iostream>
#include "Utility.h"
#include "vector2.h"
static int Clamp(int _value, int _max) {
	int result = 0;
	if (_value < 0)
		result = 0;
	if (_value >= _max)
		result = _max;
	return result;
}

static float Clmap_Overflow(float _value, float _max) {
	float result = 0;
	if (_value < 0) {
		result = _max + _value;
	}
	if (_value > _max) {
		result += _value - _max;
	}

	return result;
}

static bool NDC_Space_Checker(float start, float end, float min_range, float max_range) {
	bool check = true;
	if ((start < min_range || start > max_range) && (end < min_range || end > max_range)) {
		check = false;
	}
	return check;
}

static Transform FastInverse(Transform t) {
	Transform result;
	//Transpose by swapping row and colums
	for (int i = 0; i < 3; i++) {
		for (int n = 0; n < 3; n++) {
			result.transform[i][n] = t.transform[n][i];
		}
	}
	vector4 vec(t.transform[3][0], t.transform[3][1], t.transform[3][2], 1);
	vec = result * vec;
	result.transform[3][0] = -vec.x;
	result.transform[3][1] = -vec.y;
	result.transform[3][2] = -vec.z;

	return result;
}

static float ImpliciteLineEquation(Line ln, vector4 position) {
	float result =
		(ln.start.y - ln.end.y) * position.x +
		(ln.end.x - ln.start.x) * position.y +
		(ln.start.x * ln.end.y) -
		(ln.start.y * ln.end.x);


	return result;
}

static vector3 Convert_NDC_to_ScreenSpace(vector4 _point, int raster_width, int raster_height) {
	float x = (1 + _point.x);
	float y = (1 - _point.y);
	
	x = (int)(x * (raster_width >> 1));
	y = (int)(y * (raster_height >> 1));

	return vector3(x, y, 0);
}

static unsigned int BGRA_to_ARGB(unsigned int _color) {

	unsigned int r = (_color & 0x0000ff00) << 8;
	unsigned int g = (_color & 0x00ff0000) >> 8;
	unsigned int b = (_color & 0xff000000) >> 24;

	return r + g + b;
	
}