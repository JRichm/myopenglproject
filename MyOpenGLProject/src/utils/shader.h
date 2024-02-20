#pragma once

#include <string>

class Shader {
	public:
		Shader();
		~Shader();

		void use();

	private:
		std::string readFile(const char* filePath);
		unsigned int compileShader(const char* source, unsigned int type);
		unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};