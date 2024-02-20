#include "input.h"
#include <GLFW/glfw3.h>

// initialize input and set up callbacks
Input::Input(const Window& window) {

	if (window.getGLFWWindow() == nullptr) {
		// Handle the error or throw an exception
		throw std::runtime_error("Invalid GLFW window pointer");
	}

	lastX = 0.0;
	lastY = 0.0;
	initialX = 0.0;
	initialY = 0.0;
	deltaX = 0.0;
	deltaY = 0.0;
	mousePressed = false;

	GLFWwindow* glfwWindow = window.getGLFWWindow();

	glfwSetMouseButtonCallback(glfwWindow, mouseButtonCallback);
	glfwSetCursorPosCallback(glfwWindow, cursorPositionCallback);
}

void Input::processInput() {
	// process input and handle keybaord input
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	auto* inputInstance = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (inputInstance) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS) {
				inputInstance->mousePressed = true;
				glfwGetCursorPos(window, &inputInstance->initialX, &inputInstance->initialY);
				std::cout << "Mouse click" << std::endl;
			}
			else if (action == GLFW_RELEASE) {
				std::cout << "Mouse release" << std::endl;
				inputInstance->mousePressed = false;
			}
		}
	}
}

void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	auto* inputInstance = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (inputInstance) {
		if (inputInstance->mousePressed) {

		}
	}
}

void Input::writeDebug(GLFWwindow* window) {
	auto* inputInstance = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (inputInstance) {
		std::cout << "Mouse Pressed: " << inputInstance->mousePressed << std::endl;
	}
}