#include "ResourceEngine.h"

void ResourceEngine::init() {
	addShader("src/defaultVertShader.vert", "src/defaultFragShader.frag", "defaultShader");
}

std::string ResourceEngine::getFile(const std::string& filePath) {
	std::string fileContents;

	try {
		std::fstream file(filePath);
		std::stringstream buffer;
		buffer << file.rdbuf();
		fileContents = buffer.str();
		file.close();
		return fileContents;
	}
	catch (std::fstream::failure e) {
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ::" << filePath << std::endl;
		return "";
	}
}

void ResourceEngine::addShader(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath, const std::string& shaderName) {
	Shader* shader = new Shader(getFile(vertShaderFilePath), getFile(fragShaderFilePath));
	shaderMap_[shaderName] = shader;
}

Shader* ResourceEngine::getShader(const std::string& shaderName) {
	return shaderMap_[shaderName];
};

void ResourceEngine::addTexture(const std::string& filePath, const std::string& textureName) {

}

Texture* ResourceEngine::getTexture(const std::string& textureName) {
	return textureMap_[textureName];
}
