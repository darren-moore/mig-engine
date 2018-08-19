#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>

// The IO Engine's job is to handle HID input and display pixels from the Render Engine.
// We use GLFW.
class IOEngine {
public:
	void init();
	void stop();
	bool shouldClose();
	float getCurrentWindowTime();
	void bindInput(const char* inputName, int button);
	void unbindInput(const char* inputName);
	bool isDown(const char* inputName);
	void swapBuffers();
	void processInput();
	int createWindow(int width, int height);
private:
	GLFWwindow* window_;
	std::map<std::string, int> inputMap_;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static bool keys[1024];	// A GLFW key table.
};
