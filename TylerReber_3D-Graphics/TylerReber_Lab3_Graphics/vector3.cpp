#include "vector3.h"

vector3::vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

vector3 vector3::operator+(const vector3& other) const
{
	float x = this->x + other.x;
	float y = this->y + other.y;
	float z = this->z + other.z;

	return vector3(x,y,z);
}

vector3 vector3::operator/(const float& other) const {
	float x = this->x / other;
	float y = this->y / other;
	float z = this->z / other;
	return vector3(x, y, z);
}