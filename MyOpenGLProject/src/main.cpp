#include <iostream>
#include "utils/window.h"
#include "utils/shader.h"
#include "utils/input.h"
#include "utils/view.h"

int main() {

	// initialize glfw
	if (!glfwInit()) {
		// Handle the error or throw an exception
		throw std::runtime_error("Failed to initialize GLFW");
	}

	// window instance
	Window window("Hello World", 680, 480);

	// shader instance
	const char* vertexPath = "shaders/vertex.glsl";
	const char* fragmentPath = "shaders/fragment.glsl";
	Shader shader(vertexPath, fragmentPath);

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