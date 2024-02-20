#include "window.h"

// initialize window
Window::Window(const char* title, int width, int height) : glfwWindow(nullptr) {

	// give window opengl version data
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create glfw window
	glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

	// make sure window is created
	if (!glfwWindow) {
		throw std::runtime_error("Failed to create GLFW window");
		glfwTerminate();
	}

	// add window to current context
	glfwMakeContextCurrent(glfwWindow);
	glfwSetWindowUserPointer(glfwWindow, this);
}

Window::~Window() {
	std::cout << "kill window" << std::endl;
	if (glfwWindow) {
		glfwDestroyWindow(glfwWindow);
	}
}

GLFWwindow* Window::getGLFWWindow() const {
	return glfwWindow;
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(glfwWindow);
}

void Window::clear() {
	glClearColor(0.0f, 0.04f, 0.08f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers() {
	glfwSwapBuffers(glfwWindow);
}

void Window::pollEvents() {
	glfwPollEvents();
}