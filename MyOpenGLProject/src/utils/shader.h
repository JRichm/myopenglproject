#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void use() const;

	private:
		unsigned int programID;

		std::string readFile(const char* filePath);
		unsigned int compileShader(const char* source, unsigned int type, const char* typeName, const char* filePath);
		unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};