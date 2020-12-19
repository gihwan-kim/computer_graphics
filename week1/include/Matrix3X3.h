 #include <iostream>
 #include "Vector3D.h"
class Matrix
{
public:
	// 고정된 크기의 매트릭스
	// [row][col]
	float value_[3][3];

	// 임의의 M by N 메트릭스 만들어보기
	// mxn 매트릭스 클래스
	// mxn 매트릭스 곱
	float *values_ = nullptr;

	void print()
	{
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				std::cout << value_[row][col];
			}
			std::cout << std::endl;
		}
	}
};
/*
	Matrix multiply
		두개의 행렬에서 한개의 행렬을 만드는 연산
		I x M * M * N = I x N
		앞 행렬의 행 갯수와 둘째 행렬의 열 갯수를 가진다.
*/

// 3x3 mutiply 3x1 (vector) = 3x1 matrix (vector)
template <class TT> Vector3D<TT> mutiply(const Matrix &m, const Vector3D<TT> &v)
{
	Vector3D ans;

	ans.x_ = m.value_[0][0] * v.x_ + m.value_[0][0] * v.y_ + m.value_[0][2] * v.z_;
	ans.y_ = m.value_[0][0] * v.y_ + m.value_[0][1] * v.y_ + m.value_[0][2] * v.z_;	
	ans.z_ = m.value_[0][0] * v.z_ + m.value_[0][1] * v.y_ + m.value_[0][2] * v.z_;
}
