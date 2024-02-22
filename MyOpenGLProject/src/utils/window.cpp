#include "window.h"

// initialize window
Window::Window(const char* title, int width, int height) : glfwWindow(nullptr) {

	// create glfw window
	glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

	// make sure window is created
	if (!glfwWindow) {
		throw std::runtime_error("Failed to create GLFW window");
		glfwTerminate();
	}

	const char* vertexPath = "shaders/vertex.glsl";
	const char* fragmentPath = "shaders/fragment.glsl";
	//Shader shader(vertexPath, fragmentPath);

	bool shader = createShaderInstance(vertexPath, fragmentPath);
}

Window::~Window() {
	std::cout << "kill window" << std::endl;
	if (glfwWindow) {
		glfwDestroyWindow(glfwWindow);
	}
}

GLFWwindow* Window::getGLFWWindow() const {
	return glfwWindow;
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(glfwWindow);
}

void Window::clear() {
	glClearColor(0.0f, 0.04f, 0.08f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers() {
	glfwSwapBuffers(glfwWindow);
}

void Window::pollEvents() {
	glfwPollEvents();
}

bool Window::createShaderInstance(const char* vertexPath, const char* fragmentPath) {

	std::cout << "creating shader instance.." << std::endl;

	std::cout << "\treading files..." << std::endl;
	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	unsigned int vertexShader = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER, "vertex");
	unsigned int fragmentShader = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER, "fragment");

	programID = linkProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}

std::string Window::readFile(const char* filePath) {
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

unsigned int Window::compileShader(const char* source, unsigned int type, const char* typeName) {

	std::cout << "\n\tCompiling shader..." << std::endl;
	std::cout << "\t\ttype: " << typeName << std::endl;
	std::cout << "\t\ttype int: " << type << std::endl;

	std::cout << source << std::endl;

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "OpenGL error after glCreateShader: " << error << std::endl;
	}

	std::cout << glCreateShader(type) << std::endl;

	unsigned int shaderID = glCreateShader(type);
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


unsigned int Window::linkProgram(unsigned int vertexShader, unsigned int fragmentShader) {

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