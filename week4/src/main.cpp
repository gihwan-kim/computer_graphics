#include <GL/glew.h>
#include <Opengl/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
#include <vector>
#include "../include/Matrix4.h"

const int width_window = 640;
const int height_window = 640;

class Vector3
{
public:
	union {
		struct { float x_, y_, z_; };
		float v_[3];
	};

	Vector3(const float& _x, const float& _y, const float& _z)
		: x_(_x), y_(_y), z_(_z)
	{}
};

//Vec3 colors[3] = { Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 1.0) };
//Vec3 pos[3] = { Vec3(0.0, 0.0, 0.0), Vec3(1.0f, 0.0, 0.0), Vec3(0.0f, 1.0f, 0.0) };
//GLubyte indices[] = { 0, 1, 2 };

const int num_vertices = 24;
const int num_quads = 6;

const Vector3 colors[num_vertices] =
{
	Vector3(0, 0, 0.8),
	Vector3(0, 0, 0.8),
	Vector3(0, 0, 0.8),
	Vector3(0, 0, 0.8),

	Vector3(1, 0, 0),
	Vector3(1, 0, 0),
	Vector3(1, 0, 0),
	Vector3(1, 0, 0),

	Vector3(0, 1, 0),
	Vector3(0, 1, 0),
	Vector3(0, 1, 0),
	Vector3(0, 1, 0),

	Vector3(1, 1, 0),
	Vector3(1, 1, 0),
	Vector3(1, 1, 0),
	Vector3(1, 1, 0),

	Vector3(0.2, 0.2, 1),
	Vector3(0.2, 0.2, 1),
	Vector3(0.2, 0.2, 1),
	Vector3(0.2, 0.2, 1),

	Vector3(1, 0, 1),
	Vector3(1, 0, 1),
	Vector3(1, 0, 1),
	Vector3(1, 0, 1)
};

Vector4<float> positions[num_vertices] = 
{
	Vector4<float>(0.0, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.0, 0.0, 1.0),
	Vector4<float>(0.0, 0.0, 0.0, 1.0),

	Vector4<float>(0.0, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.5, 0.5, 1.0),
	Vector4<float>(0.0, 0.5, 0.5, 1.0),

	Vector4<float>(0.5, 0.0, 0.5, 1.0),
	Vector4<float>(0.5, 0.0, 0.0, 1.0),
	Vector4<float>(0.5, 0.5, 0.0, 1.0),
	Vector4<float>(0.5, 0.5, 0.5, 1.0),

	Vector4<float>(0.0, 0.0, 0.5, 1.0),
	Vector4<float>(0.0, 0.0, 0.0, 1.0),
	Vector4<float>(0.0, 0.5, 0.0, 1.0),
	Vector4<float>(0.0, 0.5, 0.5, 1.0),

	Vector4<float>(0.0, 0.0, 0.0, 1.0),
	Vector4<float>(0.5, 0.0, 0.0, 1.0),
	Vector4<float>(0.5, 0.5, 0.0, 1.0),
	Vector4<float>(0.0, 0.5, 0.0, 1.0),

	Vector4<float>(0.0, 0.5, 0.5, 1.0),
	Vector4<float>(0.5, 0.5, 0.5, 1.0),
	Vector4<float>(0.5, 0.5, 0.0, 1.0),
	Vector4<float>(0.0, 0.5, 0.0, 1.0)
};

const GLbyte indices[num_quads * 4] = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	8, 9, 10, 11,
	12, 13, 14, 15,
	16, 17, 18, 19,
	20, 21, 22, 23
};

int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glClearColor(1, 1, 1, 1); // while background

	printf("%s\n", glGetString(GL_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(-0.2, 1.2, -0.2, 1.2, -10.0, 10.0);
	glOrtho(-1.2, 1.2, -1.2, 1.2, -10.0, 10.0);
	//TODO: consider anisotropic view
	gluLookAt(1.2, 0.8, 1.2, 0.5, 0.5, 0.5, 0, 1, 0);
	//glLoadIdentity();
	//gluLookAt(1, 1, 1, 0.5, 0.5, 0.5, 0, 1, 0);
	//gluLookAt(0, 0, 0, 0.25, 0.25, 0.25, 0, 1, 0);
	//glEnableVertexAttribArray(0);
	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	GLuint vbo[3];
	glGenBuffers(3, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//NOTE: don't forget glDeleteBuffersARB(1, &vbo);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // <- depth test

		//TODO: draw here
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(4, GL_FLOAT, 0, 0);		// Vector4

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_QUADS, num_quads * 4, GL_UNSIGNED_BYTE, 0);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glDeleteBuffersARB(3, vbo);

	glfwTerminate();

	return 0;
}

