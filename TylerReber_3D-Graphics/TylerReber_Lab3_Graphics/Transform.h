#pragma once
#include "vector3.h"
#include "vector4.h"

struct Transform
{
	float transform[4][4];

	Transform() : transform{ {0} } {};
	Transform(float _matrix[4][4]);
	
	/// <summary>
	/// Set transform Matrix to 2D array matrix in parameter
	/// </summary>
	void SetTransform(const float(&matrix)[4][4]);

	vector4 operator* (const vector4& other) const;
	Transform operator* (const Transform& other) const;

};

