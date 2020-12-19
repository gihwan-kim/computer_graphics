#include <OpenGL/glad
// GLFW 앞에 GLAD 를 포함해야함 GLAD include 파일에는
// 필요한 OpenGL 헤더들을 가지고 있어서 먼제 선언해줘야함
#include <GLFW/glfw3.h>
// void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	glfwInit();
	// glfwWindowHint : GLFW 의 구성값을 설정

	// OpenGL 3.3 버전을 사용함을 알림
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Mac OS X 에서 사용하려는 경우
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// window 객체 만들기
	// 모든 window 관련 데이터를 가지고 있음, GLFW 의 대부분의 함수에서 사용됨
	// glfwCreatwWindow(window_width, window_height, window_name, 나머지 무시)
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD : 	OpenGL 에 대한 함수 포인터를 관리한다.
	// 			OpenGL 함수를 호출하기 전에 초기화해줘야한다.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 렌더링 하기전에 OpenGL 에게 렌더링 window 크기를 알려줘서
	// 좌표와 데이터들을 창에 표시하는 법을 정하도록
	// glViewPort(window 의 왼쪽상단 결졍, window 의 왼쪽 상단결정, 픽셀에서 렌더링될 width, 픽셀에서 렌더링될 height);
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 즉시 종료하지 않도록
	// glfwWindowShouldClose(window_object)
	// : 	반복이 시작될때 닫으라고 지시 받았는지 확인, 
	// :	닫으라고 했을 경우 true 리턴해서 렌더링 반복이 실행을 멈추고 application 을 닫을 수 있음
	// glfwPollEvents()
	// :	이벤트 (키보드입력, 마우스이동) 가 발생했는지 확인하고 window 상태를 업데이트
	// :	해당 콜백함수 호출
	while(!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  