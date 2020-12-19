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

        // color array 를 사용할 수 있도록 한다.
		glEnableClientState(GL_COLOR_ARRAY);
        // vertex array 를 사용할 수 있도록 한다.
		glEnableClientState(GL_VERTEX_ARRAY);
		
        // color array 와 vertex array 들을 한번에 보낼 수 있다.
		glColorPointer(3, GL_FLOAT, 0, colors);
		glVertexPointer(3, GL_FLOAT, 0, pos);
        // glDrawArrays(mode, array_frist_idx, number_of_element);
		glDrawArrays(GL_TRIANGLES, 0, 9);

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

