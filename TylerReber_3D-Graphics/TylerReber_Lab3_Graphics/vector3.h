#pragma once
struct vector3
{
	float x = 0;
	float y = 0;
	float z = 0;

	vector3() { };
	vector3(float _x, float _y, float _z);

	vector3 operator+ (const vector3& other) const;
	vector3 operator/ (const float& other) const;
};

