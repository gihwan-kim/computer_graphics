#include <iostream>
class Vector2D
{
public:
	float x_, y_;
	// 생성자
	Vector2D()
		: x_(0.0), y_(0.0)
	{}
	void assign(const float& _x, const float& _y)
	{
		x_ = _x;
		y_ = _y;
	}
	void print()
	{
		std::cout << x_ << " " << y_ << std::endl;
	}
	Vector2D operator += (const Vector2D& v_input)
	{
		x_ += v_input.x_;
		y_ += v_input.y_;
		return *this;
	}
	// dot product - 내적
};
float dotProduct(const Vector2D& v0, const Vector2D& v1)
{
	return v0.x_* v1.x_ + v0.y_ * v1.y_;
}