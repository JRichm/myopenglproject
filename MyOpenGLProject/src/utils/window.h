#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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

		unsigned int programID;

		std::string readFile(const char* filePath);
		bool createShaderInstance(const char* vertexPath, const char* fragmentPath);
		unsigned int compileShader(const char* source, unsigned int type, const char* typeName);
		unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};