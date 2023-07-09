#include "Transform.h"


Transform::Transform(float _matrix[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			transform[i][n] = _matrix[i][n];
		}
	}
}

void Transform::SetTransform(const float(&matrix)[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			transform[i][n] = matrix[i][n];
		}
	}

}

vector4 Transform::operator*(const vector4& other) const
{
	vector4 result;

	result.x = (float)(other.x * this->transform[0][0]) + (float)(other.y * transform[1][0]) + (float)(other.z * transform[2][0]) + (float)(other.w * transform[3][0]);
	result.y = (float)(other.x * this->transform[0][1]) + (float)(other.y * transform[1][1]) + (float)(other.z * transform[2][1]) + (float)(other.w * transform[3][1]);
	result.z = (float)(other.x * this->transform[0][2]) + (float)(other.y * transform[1][2]) + (float)(other.z * transform[2][2]) + (float)(other.w * transform[3][2]);
	result.w = (float)(other.x * this->transform[0][3]) + (float)(other.y * transform[1][3]) + (float)(other.z * transform[2][3]) + (float)(other.w * transform[3][3]);

	return result;
}

Transform Transform::operator*(const Transform& other) const
{
	Transform matrice;

	matrice.transform[0][0] = (this->transform[0][0] * other.transform[0][0]) + (this->transform[0][1] * other.transform[1][0]) + (this->transform[0][2] * other.transform[2][0]) + (this->transform[0][3] * other.transform[3][0]);
	matrice.transform[0][1] = (this->transform[0][0] * other.transform[0][1]) + (this->transform[0][1] * other.transform[1][1]) + (this->transform[0][2] * other.transform[2][1]) + (this->transform[0][3] * other.transform[3][1]);
	matrice.transform[0][2] = (this->transform[0][0] * other.transform[0][2]) + (this->transform[0][1] * other.transform[1][2]) + (this->transform[0][2] * other.transform[2][2]) + (this->transform[0][3] * other.transform[3][2]);
	matrice.transform[0][3] = (this->transform[0][0] * other.transform[0][3]) + (this->transform[0][1] * other.transform[1][3]) + (this->transform[0][2] * other.transform[2][3]) + (this->transform[0][3] * other.transform[3][3]);

	matrice.transform[1][0] = (this->transform[1][0] * other.transform[0][0]) + (this->transform[1][1] * other.transform[1][0]) + (this->transform[1][2] * other.transform[2][0]) + (this->transform[1][3] * other.transform[3][0]);
	matrice.transform[1][1] = (this->transform[1][0] * other.transform[0][1]) + (this->transform[1][1] * other.transform[1][1]) + (this->transform[1][2] * other.transform[2][1]) + (this->transform[1][3] * other.transform[3][1]);
	matrice.transform[1][2] = (this->transform[1][0] * other.transform[0][2]) + (this->transform[1][1] * other.transform[1][2]) + (this->transform[1][2] * other.transform[2][2]) + (this->transform[1][3] * other.transform[3][2]);
	matrice.transform[1][3] = (this->transform[1][0] * other.transform[0][3]) + (this->transform[1][1] * other.transform[1][3]) + (this->transform[1][2] * other.transform[2][3]) + (this->transform[1][3] * other.transform[3][3]);

	matrice.transform[2][0] = (this->transform[2][0] * other.transform[0][0]) + (this->transform[2][1] * other.transform[1][0]) + (this->transform[2][2] * other.transform[2][0]) + (this->transform[2][3] * other.transform[3][0]);
	matrice.transform[2][1] = (this->transform[2][0] * other.transform[0][1]) + (this->transform[2][1] * other.transform[1][1]) + (this->transform[2][2] * other.transform[2][1]) + (this->transform[2][3] * other.transform[3][1]);
	matrice.transform[2][2] = (this->transform[2][0] * other.transform[0][2]) + (this->transform[2][1] * other.transform[1][2]) + (this->transform[2][2] * other.transform[2][2]) + (this->transform[2][3] * other.transform[3][2]);
	matrice.transform[2][3] = (this->transform[2][0] * other.transform[0][3]) + (this->transform[2][1] * other.transform[1][3]) + (this->transform[2][2] * other.transform[2][3]) + (this->transform[2][3] * other.transform[3][3]);

	matrice.transform[3][0] = (this->transform[3][0] * other.transform[0][0]) + (this->transform[3][1] * other.transform[1][0]) + (this->transform[3][2] * other.transform[2][0]) + (this->transform[3][3] * other.transform[3][0]);
	matrice.transform[3][1] = (this->transform[3][0] * other.transform[0][1]) + (this->transform[3][1] * other.transform[1][1]) + (this->transform[3][2] * other.transform[2][1]) + (this->transform[3][3] * other.transform[3][1]);
	matrice.transform[3][2] = (this->transform[3][0] * other.transform[0][2]) + (this->transform[3][1] * other.transform[1][2]) + (this->transform[3][2] * other.transform[2][2]) + (this->transform[3][3] * other.transform[3][2]);
	matrice.transform[3][3] = (this->transform[3][0] * other.transform[0][3]) + (this->transform[3][1] * other.transform[1][3]) + (this->transform[3][2] * other.transform[2][3]) + (this->transform[3][3] * other.transform[3][3]);

	return matrice;
}



