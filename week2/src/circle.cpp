#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"

// 표준 라이브러리이기 떄문에 윈도우에만 특화된 라이브러리를 사용하는 것보다는 표준 라이브러리를 사용하면 좋음

const int width_window = 640;
const int height_window = 480;

float circle_center_x = 0.0;
float circle_center_y = 0.0;

/*
	key_callbakc()
		parameter 인 window 에 대하여 콜백 함수가 설정되는것 같다.

*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
		circle_center_x += 0.1;
		std::cout << "LEFT KEY PRESSED" << std::endl;
	}
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
		circle_center_x -= 0.1;
		std::cout << "RIGHT KEY PRESSED" << std::endl;
	}
}

int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
    /*
	Create a windowed mode window and its OpenGL context 
    	glfwCreateWindow(width_window, height_window, window_title, monitor, share);
			monitor  : 여러 디스플레이를 사용할 경우 어떤것을 보여줄지 결정할 수 있다.
			shar     : 여러 어플리케이션간의 공유 기능을 제공

			window 를 생성하는데 실패한다면 당연히 바로 종료해줘야한다.
    */
	window = glfwCreateWindow(width_window, height_window, "Lecture example", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here
	glfwSetKeyCallback(window, key_callback);

	/* 
        glfwMakeContextCurrent(window);
        Make the window's context current
        argument 에 그릴 것이라고 명시해줌
        
    */
	glfwMakeContextCurrent(window);
	
    /*
        버퍼의 기본 색깔을 결정
        RGB 색깔을 통해 결정
		[clamp]
			glclampf 의 clamp 는 값의 범위가 0.0 ~ 1.0 사이로 제한된다는 뜻
			색상의 강도, 텍스처의 좌표처럼 범위가 명확한 값을 지정할 때 이 타입을 사용
			Ex. glclampf, glclampd

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
	const float aspect_ratio = (float)width/(float)height; // 종횡비(화면비) : 1.66, 1.9 TV 종횡비랑 비슷함

	// glOrtho : 투영 방식을 orthographic (직교) 투영으로 정해준다.
	glOrtho(-1, 1, -1 / aspect_ratio,  1 / aspect_ratio, -1.0, 1.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here 
			glcear()
			현대 그래픽시스템에서는 여러 메모리 버퍼를 사용하는데 여러 캠버스를 사용할 수 있음을 의미한다.
			
			이런 버퍼들을 바꾸면서 사용하여 aliasing 을 막을 수 있다고 한다.

			싱글 버퍼링으로 그래픽을 그릴 경우 데이터를 저장하는 동안 다음 그림의 데이터를 전송할 수 없어
			필연적으로 지우고 그리고를 반복하다 깜빡임, 찢어짐 등의 현상이 발생한다고 한다.
			-> 예비버퍼, 여러 버퍼를 가지고 잇다면 해결 가능
		*/
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here
		/*
			glBegin(GLenum mode);
			어떤 방식으로 정점들을 그리는데 사용할지정한다.

			[ vertex ]
			- 오른손 법칙
				x : 엄지
				y : 집게
				z : 가운데손가락

			[glVertex~()]
				: 어떤 유형의 정점들을 사용할지 결정한다.
				ex.
					glVertex2d(x, y) : 2 차원, double 을 사용하는 정점
				- 보통 float 을 사용하는데 좀더 복잡하고 실시간적인 효과가 필요할 경우 double 을 사용한다
		*/
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

