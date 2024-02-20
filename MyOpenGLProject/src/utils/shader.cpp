#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	std::cout << "Creating shader instance" << std::endl;

	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	unsigned int vertexShader = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER, "Vertex Shader", vertexPath);
	unsigned int fragmentShader = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER, "Fragment Shader", fragmentPath);

	programID = linkProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(programID);
}

void Shader::use() const {
	glUseProgram(programID);
}

std::string Shader::readFile(const char* filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << "File does not exist." << std::endl;
		return "";
	}
	else {
		std::cout << "reading file " << filePath << std::endl;
	}

	std::stringstream stringStream;
	stringStream << fileStream.rdbuf();
	content = stringStream.str();

	fileStream.close();
	return content;
}

unsigned int Shader::compileShader(const char* source, unsigned int type, const char* typeName, const char* filePath) {
	unsigned int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed (" << typeName << "): " << infoLog << " (File: " << filePath << ")" << std::endl;
	}
	else {
		std::cout << "Shader compilation success (" << typeName << "): " << filePath << std::endl;
	}
	
	return shaderID;
}
unsigned int Shader::linkProgram(unsigned int vertexShader, unsigned int fragmentShader) {
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	int success;
	char infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		std::cerr << "Shader program linking failed: " << infoLog << std::endl;
	}
	else {
		std::cout << "Shader program linking success." << std::endl;
	}

	return programID;
}