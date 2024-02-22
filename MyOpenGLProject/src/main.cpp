#include <iostream>
#include "utils/window.h"
#include "utils/shader.h"
#include "utils/input.h"
#include "utils/view.h"

int main() {

	// give window opengl version data
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// initialize glfw
	if (!glfwInit()) {
		// Handle the error or throw an exception
		throw std::runtime_error("Failed to initialize GLFW");
	}

	// window instance
	Window window("Hello World", 680, 480);

	// add window to current context
	glfwMakeContextCurrent(window.getGLFWWindow());
	//glfwSetWindowUserPointer(window.getGLFWWindow());

	// input instance
	Input input(window);

	// view instance
	View view;

	// main loop
	while (!window.shouldClose()) {
		window.clear();

		window.swapBuffers();
		window.pollEvents();

		//input.writeDebug(window.getGLFWWindow());
		view.DebugLog();
	}

	glfwTerminate();

	return 0;
}