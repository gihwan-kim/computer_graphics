#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h> // srand, rand
#include <thread>	// std::this_thread::sleep_for
#include <chrono>	// std::chrono::seconds
#include <iostream>
#include "math.h"

/*
    [ 파일 특징]
    삼각 형 두개를 생성하는데
    삼각형 하나와 붙어있는 나머지 삼각형은 반시계 반향으로 돌려서 생성해준다.
    삼각형 두개는 서로 2점을 공유하는데
    반시계 방향으로 할 경우 두 점은 공유되지 않고 개별적인 점으로
    판단하여 vertex 배열은 총 점 6 개에 대한 데이터를 가져야 한다.
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

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	Vector3 colors[6] = {
		Vector3(1.0, 0.0, 0.0),
		Vector3(0.0, 1.0, 0.0),
		Vector3(0.0, 0.0, 1.0),
		Vector3(1.0, 0.0, 0.0),
		Vector3(0.0, 1.0, 0.0),
		Vector3(0.0, 0.0, 1.0)
		};
	float vertex[6][3] = {
		{0.0, 0.0, 0.0},
		{0.5, 0.0, 0.0},
		{0.25, 0.5, 0.0},
		{0.25, 0.5, 0.0},
		{0.5, 0.0, 0.0},
		{0.5, 0.5, 0.0}
		};
	int num_vertices = 6;

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
	// glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte) * 3, indices, GL_STATIC_DRAW);

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

		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6 * 3);
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
