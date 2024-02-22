#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	std::cout << "\nCreating shader instance..." << std::endl;

	std::cout << "\treading files..." << std::endl;
	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	unsigned int vertexShader = compileShader(vertexCode.c_str(), 1, "vertex");
	unsigned int fragmentShader = compileShader(fragmentCode.c_str(), 2, "fragment");

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
		std::cerr << "\tCould not read file " << filePath << "File does not exist." << std::endl;
		return "";
	}
	else {
		std::cout << "\t\tfile: " << filePath << std::endl;
	}

	std::stringstream stringStream;
	stringStream << fileStream.rdbuf();
	content = stringStream.str();

	fileStream.close();
	return content;
}

unsigned int Shader::compileShader(const char* source, int type, const char* typeName) {

	std::cout << "\n\tCompiling shader..." << std::endl;
	std::cout << "\t\ttype: " << typeName << std::endl;
	std::cout << "\t\ttype int: " << type << std::endl;

	std::cout << source << std::endl;

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "OpenGL error after glCreateShader: " << error << std::endl;
	}

	std::cout << glCreateShader(type) << std::endl;

	unsigned int shaderID;

	if (type == 1) {
		shaderID = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == 2) {
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else {
		std::cerr << "incorrect shader type" << std::endl;
		return (int)nullptr;
	}

	std::cout << "created shader" << std::endl;

	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);
	
	std::cout << "checking success" << std::endl;
		
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed: " << infoLog << std::endl;
	}
	else {
		std::cout << "Shader compilation success" << std::endl;
	}
	
	return shaderID;
}


unsigned int Shader::linkProgram(unsigned int vertexShader, unsigned int fragmentShader) {

	std::cout << "\tLinking Shader..." << std::endl;

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