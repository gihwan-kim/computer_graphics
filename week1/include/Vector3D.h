
// 템블릿 만드는법
// 여러 자료형에 적용하는법

/*
# 클래스의 기초적인 사용법

  [참조]
  참조하는 변수는 참조당하는 변수와 동일한 주소, 값을 가진다.
  값 그대로를 사용하기 때문에 함수의 매개변수의 데이터형에 참조를 넣어주면 값을 복사하지 않아도된다. (c 랑 차이점)

  [클래스 설계] -> 추상화, 데이터은닉 -> 캡슐화
  1. 클래스 선언
		구조체 선언과 비슷
		멤버 변수, 멤버 함수를 가짐
		private : 멤버 함수를 통해서만 접근 가능
		public	: 클래스 객체를 사용하여 접근 가능
  2. 클래스 멤버 함수 구현
		클래스 선언에 함수 원형 대신 함수 정의를 넣을 수도 있음
		보통은 따로 파일을 만들어서 함수 정의를 만들어줌 ->	어느 클래스에 속하는지 :: 연산자 (사용범위 결정 연산자)를 사용해서 알려줘야함!
  3. 클래스의 객체를 만드려면 클래스를 데이터형 처럼 사용

  [클래스 생성자 - constructor]
  - 보통의 데이터 형처럼 초기화할 수 없음 -> 멤버 변수들이 보통 private 이기 때문 -> 멤버함수를 사용해서 접근
  - 데이터들을 public 으로 만든다면 보통의 데이터형 처럼 초기화 가능하긴 함 -> 클래스 사용 의미가 없어짐
  - 생성자 : 객체가 생성될때 자동으로 초기화 되도록
  - 객체를 생성해주는 역할
  
  1. 생성자의 이름은 클래스 이름과 동일
		리턴 값 x, 데이터 형 선언 x
  2. 생성자의 매개변수는 클래스 멤버가 아니라 멤버에 대입될 값이다.
  		매개변수 이름, 멤버 변수 이름 구별해줘야함!

  [클래스 생성자 사용법]
  1. 명시적 호출
		ClassName val = ClassName(arg1, arg2, ...);
  2. 암시적 호출
		className vla(arg1, arg2, ...);	
  - 클래스 객체를 사용할때마다 생성자를 사용해줘야함
  - new 를 사용하여 동적할당을 할때 또한 동일하다.
  
  [생성자 종류]
  1. 디폴트 생성자
		매개변수를 가지지 않음
		아무 생성자도 안만들어 둘 경우 자동으로 디폴트 생성자를 제공해줌
		- 만드는법
			방법 1 : 기존 생성자의 모든 매개변수에 디폴트 값을 넣어준다.
			방법 2 : 함수 오버로딩을 사용해서 매개변수가 없는 생성자를 만들어준다.
			! 둘중 하나의 방법만 사용

   [클래스 파괴자 - destructor]
	- 객체의 수명이 끝나는 시점에 멤버함수로 자동으로 호출됨
	- 동적할당한 메모리가 있을 경우 destructor 에서 따로 해제해주는 코드를 넣어줘야함
	- 따로 안만들어두면 컴파일러가 만들어줌
	- 리턴 값 x, 매개변수 x
	1. 모양
		~ClassName()
		or
		~CalssName()
		{

		}
    2. 보통은 사용자가 destructor 를 호출해주면 안됨
		객체가 정의된 코드 블럭을 벗어날때 도는 프로그램이 종료될때 자동으로 호출됨

  [this 포인터]
   - 멤버함수를 호출하는데 사용된 객체

  [객체 배열]
   - 표준 데이터형의 배열을 선언하는 방식과 동일하다.
   - 명시적으로 초기화 하지 않은 객체들을 생성할떄는 디폴트 생성자가 호출됨

  [템플릿]
  template <class Type>
 
  template 키워드: 컴파일러에게 템플릿을 정의한다고 알림
  class 키워드   : 데이터 형을 값으로 받아들이는 어떤 변수의 데이터형 이름의 역할
				type 이 반드시 클래스여야 한다는 의미가 아님
  Type          : 변수의 이름, 사용자가 원하는 포괄적인 데이텨형

  [멤버 함수]
  - 멤버함수를 정의할때 어느 클래스에 속하는지 :: 연산자를 사용
		DataType className::functionName (parameter)
		같은 클래스에서는 다른 멤버함수를 호출할때 사용범위 결정 연산자(::) 를 사용안해도됨
 */
#include <iostream>

template <class TT>

class Vector3D
{
public:
	TT x_, y_, z_;
	// 생성자
	Vector3D()
		: x_(TT()), y_(TT()), z_(TT())
	{}
	Vector3D(const TT &_x, const TT &_y, const TT &_z)
		: x_(_x), y_(_y), z_(_z)
	{}

	void assign(const TT &_x, const TT &_y, const TT &_z)
	{
		x_ = _x;
		y_ = _y;
		z_ = _z;
	}
	void print()
	{
		std::cout << x_ << " " << y_ << " " << z_ << std::endl;
	}
	Vector3D operator+=(const Vector3D &v_input)
	{
		x_ += v_input.x_;
		y_ += v_input.y_;
		z_ += v_input.z_;
		return *this;
	}

};

template<class TT> TT dotProduct(const Vector3D<TT> &v0, const Vector3D<TT> &v1)
{
	return v0.x_ * v1.x_ + v0.y_ * v1.y_ + v0.z_ * v1.z_;
}
/*
	[외적 - CrossProduct]
	벡터 곱
*/
template<class TT> Vector3D<TT> crossProduct(const Vector3D<TT> &v0, const Vector3D<TT> &v1)
{
	return Vector3D<TT>(v0.y_ * v1.z_ - v0.z_ * v1.y_,
						v0.z_ * v1.x_ - v0.x_ * v1.z_,
						v0.x_ * v1.y_ - v0.y_ * v1.x_);
}
