#pragma once
#include <iostream>
#include "vector3.h"
#include "vector4.h"
#include "transform.h"

static void PrintVector(vector2 _vector) {
	std::cout << "(" << _vector.x << ", " << _vector.y << ")" << std::endl;
}

static void PrintVector(vector3 _vector) {
	std::cout << "(" << _vector.x << ", " << _vector.y << ", " << _vector.z << ")" << std::endl;
}

static void PrintVector(vector4 _vector) {
	std::cout << "(" << _vector.x << ", " << _vector.y << ", " << _vector.z << ", " << _vector.w << ")" << std::endl;
}

static void PrintMatrix(Transform _matrix) {
	std::cout << "| " << _matrix.transform[0][0] << ", " << _matrix.transform[0][1] << ", " << _matrix.transform[0][2] << ", " << _matrix.transform[0][3] << " |" << std::endl;
	std::cout << "| " << _matrix.transform[1][0] << ", " << _matrix.transform[1][1] << ", " << _matrix.transform[1][2] << ", " << _matrix.transform[1][3] << " |" << std::endl;
	std::cout << "| " << _matrix.transform[2][0] << ", " << _matrix.transform[2][1] << ", " << _matrix.transform[2][2] << ", " << _matrix.transform[2][3] << " |" << std::endl;
	std::cout << "| " << _matrix.transform[3][0] << ", " << _matrix.transform[3][1] << ", " << _matrix.transform[3][2] << ", " << _matrix.transform[3][3] << " |" << std::endl;
}