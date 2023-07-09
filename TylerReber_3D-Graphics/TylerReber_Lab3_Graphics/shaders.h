#pragma once
#include "vector3.h"
#include "Points.h"
#include "Transform.h"
#include "Math.h"

#include "celestial.h"

#ifndef SHADERS_H
#define SHADERs_H

static void (*VertexShader)(vector3&) = 0;
static void (*PixelShader)(unsigned int&) = 0;


static Transform SV_WorldMatrix;


static void PS_White(unsigned int& _color) {
	_color = 0xffffffff;
}

static void PS_Blue(unsigned int& _color) {
	_color = 0xff0000ff;
}

static unsigned int PS_Image(float _x, float _y) {
	//celestial_width

	//std::cout << _x << " " << _y << std::endl;
	float x = _x * celestial_width;
	float y = _y * celestial_height;

	unsigned int color = celestial_pixels[(int)y * celestial_width + (int)x];
	return BGRA_to_ARGB(color);
}

static vector3 operator*(const Transform& _other);

#endif // SHADERS_H


