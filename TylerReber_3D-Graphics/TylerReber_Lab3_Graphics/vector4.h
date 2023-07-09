#pragma once
struct vector4
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	vector4() {};
	vector4(float _x, float _y, float _z, float _w);

	vector4 operator+ (const vector4& other) const;
	vector4 operator/ (const float& other) const;
};

