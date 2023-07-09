#include "vector4.h"

vector4::vector4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

vector4 vector4::operator+(const vector4& other) const
{
	float x = this->x + other.x;
	float y = this->y + other.y;
	float z = this->z + other.z;
	float w = 1;

	return vector4(x, y, z, w);
}

vector4 vector4::operator/(const float& other) const {
	float x = this->x / other;
	float y = this->y / other;
	float z = this->z / other;
	float w = this->w / other;

	return vector4(x, y, z, w);
}