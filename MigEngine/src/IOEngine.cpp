#include "IOEngine.h"

bool IOEngine::keys[1024];

void IOEngine::init() {
	createWindow(800, 600);
}

void IOEngine::processInput() {
	glfwPollEvents();
}

int IOEngine::createWindow(int width, int height) {
	// Init and setup GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GFLW window
	window_ = glfwCreateWindow(width, height, "Mig2D", NULL, NULL);
	if (window_ == NULL) {
		std::cout << "Error: Window creation failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window_);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error: GLAD initialization failed" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
	glfwSetKeyCallback(window_, key_callback);

	return 0;
}

void IOEngine::stop() {
	glfwTerminate();
}

bool IOEngine::shouldClose() {
	return glfwWindowShouldClose(window_);
}

float IOEngine::getCurrentWindowTime() {
	return glfwGetTime();
}

void IOEngine::swapBuffers() {
	glfwSwapBuffers(window_); // double buffer!
}


void IOEngine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void IOEngine::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			IOEngine::keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			IOEngine::keys[key] = GL_FALSE;
	}
}
