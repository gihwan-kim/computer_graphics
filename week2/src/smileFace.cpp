#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h> // srand, rand
#include <thread>	// std::this_thread::sleep_for
#include <chrono>	// std::chrono::seconds
#include <iostream>
#include "math.h"

const int	 width_window = 640;
const int	height_window = 480;

float		circle_center_x = 0.0;
float		circle_center_y = 0.0;

float		left_eye_x = -0.2;
float		left_eye_y = 0.2;
float		right_eye_x = 0.2;
float		right_eye_y = 0.2;
void	eye_maker(GLfloat eye_x, GLfloat eye_y)
{
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	{
		// center of polygonized circle
		glVertex2f(eye_x, eye_y);
		const int num_triangles = 10000;
		const float dtheta = 2.0 * 3.141592 / (float)num_triangles;
		const float radius = 0.1;

		float theta = 0.0;
		for (float theta = 0.0; theta < 2.0 * 3.141592; theta += dtheta)
		{
			const float x = radius * cos(theta) + eye_x;
			const float y = radius * sin(theta) + eye_y;
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void	mouth_maker(const float radius, GLfloat mouth_x, GLfloat mouth_y)
{
	glColor3f(0, 0, 0);
	glBegin(GL_POINTS);
	{
		// center of polygonized circle
		glVertex2f(mouth_x, mouth_y);
		const int num_triangles = 10000;
		const float dtheta = 2.0 * 3.141592 / (float)num_triangles;

		float theta = 0.0;
		for (float theta = 3.141592; theta < 2.0 * 3.141592; theta += dtheta)
		{
			const float x = radius * cos(theta) + mouth_x;
			const float y = radius * sin(theta) + mouth_y;
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
		circle_center_x -= 0.1;
		left_eye_x -= 0.1;
		right_eye_x -= 0.1;
		std::cout << "LEFT KEY PRESSED" << std::endl;
	}
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
		circle_center_x += 0.1;
		left_eye_x += 0.1;
		right_eye_x += 0.1;
		std::cout << "RIGHT KEY PRESSED" << std::endl;
	}
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
		circle_center_y += 0.1;
		left_eye_y += 0.1;
		right_eye_y += 0.1;
		std::cout << "UP KEY PRESSED" << std::endl;
	}
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
		circle_center_y -= 0.1;
		left_eye_y -= 0.1;
		right_eye_y -= 0.1;
		std::cout << "DOWN KEY PRESSED" << std::endl;
	}
}

int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(width_window, height_window, "Lecture example", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here
	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);

	/*
        버퍼의 기본 색깔을 결정
    */
	glClearColor(0, 0, 0, 1); // while background

	int width, height;
	/*
		frame buffer 로 부터 window 의 사이즈를 얻어온다.
	*/
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	/*
		[프레임 버퍼]
		픽셀은 프레임 버퍼 라고 부르는 메모리에 저장된다.
		해상도(Resolution) : 프레임 버퍼의 픽셀 수
		보통 2 차원 배열  : x, y 
		3차원 배열인 경우 : x, y, depth(viewpoint 에서 object 와의 거리) 
	*/
	const float aspect_ratio = (float)width / (float)height; // 종횡비(화면비) : 1.66, 1.9 TV 종횡비랑 비슷함

	// glOrtho : 투영 방식을 orthographic (직교) 투영으로 정해준다.
	glOrtho(-1, 1, -1 / aspect_ratio, 1 / aspect_ratio, -1.0, 1.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1, 1, 0);
		glBegin(GL_TRIANGLE_FAN);
		{
			// center of polygonized circle
			glVertex2f(circle_center_x, circle_center_y);

			const int num_triangles = 10000;
			const float dtheta = 2.0 * 3.141592 / (float)num_triangles;
			const float radius = 0.5;

			float theta = 0.0;
			for (float theta = 0.0; theta < 2.0 * 3.141592; theta += dtheta)
			{
				const float x = radius * cos(theta) + circle_center_x;
				const float y = radius * sin(theta) + circle_center_y;
				glVertex2f(x, y);
			}
		}
		glEnd();

		eye_maker(left_eye_x, left_eye_y);
		eye_maker(right_eye_x, right_eye_y);
		float radius = 0.3;
		while (radius <= 0.33)
		{
			mouth_maker(radius, circle_center_x, circle_center_y);
			radius += 0.001;
		}

		/* Swap front and back buffers of the specified window */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}
