#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Sound.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>

// Provides a way to access raw file data and stores global shaders or textures.
class ResourceEngine {
public:
	void init();
	void stop() {};
	std::string getFile(const std::string& filePath);

	void addShader(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath, const std::string& shaderName);
	Shader* getShader(const std::string& shaderName);

	void addTexture(const std::string& filePath, const std::string& textureName);
	Texture* getTexture(const std::string& textureName);

	void addSound(const std::string& filePath, const std::string& soundName);
	Sound* getSound(const std::string& soundName);
private:
	std::unordered_map<std::string, Shader*> shaderMap_;
	std::unordered_map<std::string, Texture*> textureMap_;
	std::unordered_map<std::string, Sound*> soundMap_;
};
