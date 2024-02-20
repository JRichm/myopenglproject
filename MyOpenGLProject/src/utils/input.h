#pragma once
#include "window.h"
#include <GLFW/glfw3.h>

class Input {
	public:
		Input(const Window& window);

		void processInput();
		void writeDebug(GLFWwindow* window);

		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

		bool mousePressed;


	private:
		double lastX;
		double lastY;
		double initialX;
		double initialY;
		double deltaX;
		double deltaY;
};
