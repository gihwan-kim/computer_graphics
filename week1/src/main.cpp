#include <iostream>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix3X3.h"
int main()
{
	Vector3D<float> v0(1.0, 0.0, 0.0), v1(0.0, 1.0, 0.0);
	Vector3D<float> cr = crossProduct(v0, v1);
	cr.print();

	Matrix m;

	int count = 0;
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
		{
			m.value_[row][col] = (float)count++;
		}
	m.print();
	return 0;
}