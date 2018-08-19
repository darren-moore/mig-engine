#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

// The IO Engine's job is to handle HID input and display pixels from the Render Engine.
// We use GLFW.
class IOEngine {
public:
	void init();
	void stop();
	bool shouldClose();
	float getCurrentWindowTime();
	//bool addInput(std::string str, int button);
	//void isDown(std::string str);
	void swapBuffers();
	void processInput();
	int createWindow(int width, int height);

private:
	GLFWwindow* window_;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static bool keys[1024];	// A GLFW key table.
};
