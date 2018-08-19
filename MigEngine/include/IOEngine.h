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
	void init(int windowWidth, int windowHeight);
	void stop();
	bool shouldClose();
	float getCurrentWindowTime();
	void bindInput(const std::string& inputName, int button);
	void unbindInput(const std::string& inputName);
	bool isDown(const std::string& inputName);
	void swapBuffers();
	void processInput();
	int createWindow(int width, int height);

	int getWindowWidth();
	int getWindowHeight();


private:
	GLFWwindow* window_;
	std::map<std::string, int> inputMap_;

	static int windowWidth_;
	static int windowHeight_;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static bool keys[1024];	// A GLFW key table.
};
