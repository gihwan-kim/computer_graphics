#include <GL/glew.h>
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>
#include <stdlib.h> // srand, rand
#include <thread>	// std::this_thread::sleep_for
#include <chrono>	// std::chrono::seconds
#include <iostream>
#include "math.h"

/*
    [ 파일 특징]
    삼각 형 두개를 생성하는데
    맞 붙은 삼각형은 점 2개를 공유하게 만들경우 점 4개만 필요하다.

    T1 : v0, v1, v2 가 모여 삼각형을 형성한다.
    T2 : v0, v2, v3
       v0     v3
      /  \   /
    v1     v2

    6 개의 정점을 보내는 대신 4개의 정점과 연결성을 보내면 된다.
    -> incideices
*/
const int width_window = 640;
const int height_window = 480;

class Vector3
{
private:
	/* data */
public:
	// 데이터가 일렬로 4바이트 씩 x, y, z 가 나열되어 있다면
	// 배열이나 struct 나 똑같은 것으로 컴퓨터는 생각할 것이기 때문에
	// union 을 사용해서 둘중 하나의 자료형으로도 표현할 수 있다.
	union
	{
		struct
		{
			float x_, y_, z_;
		};
		float v_[3];
	};

	// constructor
	Vector3(const float &_x, const float &_y, const float &_z)
		: x_(_x), y_(_y), z_(_z)
	{
	}
};

int main(void)
{
	std::cout << "size of vec3 " << sizeof(Vector3) << std::endl;
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// print graphic card version
	printf("%s\n", glGetString(GL_VERSION));

	glClearColor(1, 1, 1, 1); // while background

	/*
		[ 직교 투영에서 3 차원 처럼 보이게 만들기 ]
		eyeX, eyeY, eyeZ 			: 눈 (카메라) 의 위치
		centerX, centerY, centerZ	: 카메라가 바라보고 있는 점의 위치
		upX, upY, upZ				: 카메라의 회전 방향?
	*/
	// gluLookAt(1, 1, 1, 0.5, 0.5, 0.5, 0, 1, 0);
	// glm::lookAt()
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	Vector3 colors[4] = {
		Vector3(1.0, 0.0, 0.0),
		Vector3(0.0, 1.0, 0.0),
		Vector3(0.0, 0.0, 1.0),
		Vector3(0.0, 0.0, 1.0)
		};
	float vertex[4][3] = {
		{0.0, 0.0, 0.0},    // v1
		{0.5, 0.0, 0.0},    // v0
		{0.25, 0.5, 0.0},   // v2
		{0.5, 0.5, -0.5}
		};
	int num_vertices = 6;

    GLubyte indices[] = { 0, 1, 2, 1, 2, 3}; // 시계 방향으로 2 개 의 삼각형
	GLuint vbo[3];	// cpu 에서 포인터 처럼 작동한다.
					// float *my_array[3]; 처럼 작동
	glGenBuffers(3, vbo); // vbo : gpu 메모리에서 포인터
							// vbo 를 통해 array 를 gpu 에 보낼 수 있다.
							// glGenBuffer 는 메모리를 할당해줌
							// 3 : 3 개짜리 배열을 생성한다는 뜻
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * sizeof(Vector3), colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// 이렇게 만들어 두면 반복문 안에서 계속 전달해줄 필요 없어진다.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 3, vertex, GL_STATIC_DRAW);

    // 점들의 연결성을 알려야함
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte) * 6, indices, GL_STATIC_DRAW);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
				//TODO: draw here
		// gpu 에게 해당 pointer 를 사용함을 알림
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableClientState(GL_COLOR_ARRAY);
		/*
			이미 반복문 밖에서 데이터들을 gpu 에 보내놨기 때문에
			최적화 2 처럼 glColorPointer(3, GL_FLOAT, 0, colors); 배열을 보내줄 필요 없다.
			따라서 0, 0 을 넣어줌
		*/
		glColorPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		// count : vertices number
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
		
		// glDrawArrays(GL_TRIANGLES, 0, 6 * 3);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}
