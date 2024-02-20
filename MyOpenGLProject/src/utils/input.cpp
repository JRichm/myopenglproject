#include "input.h"
#include <GLFW/glfw3.h>

Input* Input::inputInstance = nullptr;

// initialize input and set up callbacks
Input::Input(const Window& window) : mousePressed(false) {

	if (window.getGLFWWindow() == nullptr) {
		// Handle the error or throw an exception
		throw std::runtime_error("Invalid GLFW window pointer");
	}

	inputInstance = this;

	lastX = 0.0;
	lastY = 0.0;
	initialX = 0.0;
	initialY = 0.0;
	deltaX = 0.0;
	deltaY = 0.0;
	mousePressed = false;

	GLFWwindow* glfwWindow = window.getGLFWWindow();

	glfwSetMouseButtonCallback(glfwWindow, Input::mouseButtonCallback);
	glfwSetCursorPosCallback(glfwWindow, Input::cursorPositionCallback);
}

void Input::processInput() {
	// process input and handle keybaord input
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (inputInstance) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS) {
				inputInstance->mousePressed = true;
				glfwGetCursorPos(window, &inputInstance->initialX, &inputInstance->initialY);
			}
			else if (action == GLFW_RELEASE) {
				inputInstance->mousePressed = false;
			}
		}
	}
	else {
		std::cerr << "InputInstance is null in mouseButtonCallback!" << std::endl;
	}
}

void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	if (inputInstance) {
		if (inputInstance->mousePressed) {
			std::cout << "(" << xpos << "," << ypos << ")" << std::endl;
		}
	}
}

void Input::writeDebug(GLFWwindow* window) {

	if (inputInstance) {

		bool pressedValue = inputInstance->mousePressed;
		if (pressedValue) {
			std::cout << "Mouse Pressed: " << pressedValue << std::endl;
		}
	}
}