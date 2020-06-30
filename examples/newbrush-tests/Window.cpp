#include "Window.h"
#include "Application.h"

using namespace nb;

Window::Window(int width, int height, const std::string &title)
{
	init();
	m_implWindow = glfwCreateWindow(width, height, title.data(), 0, 0);
	glfwMakeContextCurrent(m_implWindow);

	glfwSetWindowSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });

	sizeCallback(width, height);
	Application::current()->windows().push_back(this);
}

Window::~Window()
{
	auto &windows = Application::current()->windows();
	auto iter = std::find(windows.begin(), windows.end(), this);
	if (iter != windows.end())
	{
		Application::current()->windows().erase(iter);
	}
}

void Window::render()
{
	glfwSwapBuffers(m_implWindow);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::init()
{
	static bool bInit = false;
	if (bInit)	return;

	glfwSetErrorCallback([](int error, const char*str) { printf("error:%s\n", str); });
	glfwInit();
	//������������Щ�����ϵ���glfwDestroyWindow���������ڿ��ⲻ�������Ŀǰ��δ�ҵ�ԭ��
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_SAMPLES, 32);
	bInit = true;
}

void Window::sizeCallback(int width, int height)
{
	auto app = Application::current();
	if (app)
	{
		app->drawContext.projection.ortho(0.0f, (float)width, (float)height, 0.0f, -1000.0f, 1000.0f);
		app->drawContext.viewport(0, 0, width, height);
	}
}
