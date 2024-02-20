#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

class Window {
	public:
		Window(const char* title, int width, int height);
		~Window();

		GLFWwindow* getGLFWWindow() const;

		bool shouldClose();
		void clear();
		void swapBuffers();
		void pollEvents();

	private:
		GLFWwindow* glfwWindow;
};