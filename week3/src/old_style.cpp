#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"

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
        struct   {float x_, y_, z_;};
        float   v_[3];
    };
    

    // constructor
    Vector3(const float & _x,const float & _y, const float & _z)
        :   x_(_x), y_(_y), z_(_z)
    {}
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

    // print graphic carg version
    printf("%s\n", glGetString(GL_VERSION));

	glClearColor(1, 1, 1, 1); // while background
    
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

    
    Vector3 colors[3] = { 
                            Vector3(1.0, 0.0, 0.0),
                            Vector3(0.0, 1.0, 0.0), 
                            Vector3(0.0, 0.0, 1.0) 
                            };
    float pos[3][3] = { 
                        {0.0, 0.0, 0.0}, 
                        {0.5, 0.0, 0.0}, 
                        {0.25, 0.5, 0.0} 
                        };

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here

        // glColor3f(1.0, 0.0, 0.0);
        /*
            glVertex3f(0.0, 0.0, 0.0); 의 형태로 파라미터를 3개나 전달하는 것 보다
            배열의 형태로 파라미터 한개만 전달하는 것이 스택을 적게 사용하기 때문에 효율적이다.
        */
    	glBegin(GL_TRIANGLES);
		{
            for (int i = 0; i < 3; i++)
            {
                glColor3fv(colors[i].v_);
                glVertex3fv(colors[i].v_);
            }		
        }
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}

