#include <iostream>
#include "utils/window.h"
#include "utils/input.h"

int main() {

	// window instance
	Window window("Hello World", 680, 480);

	if (window.getGLFWWindow() == nullptr) {
		// Handle the error or throw an exception
		std::cout << "failed to initialize window" << std::endl;
	}


	// create input instance
	Input input(window);


	// main loop
	while (!window.shouldClose()) {
		window.clear();

		window.swapBuffers();
		window.pollEvents();

		input.writeDebug(window.getGLFWWindow());
	}

	return 0;
}