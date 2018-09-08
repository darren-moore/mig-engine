#include "ResourceEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void ResourceEngine::init() {
	addShader("src/DefaultShaders/defaultVertShader.vert", "src/DefaultShaders/defaultFragShader.frag", "defaultSpriteShader");
	addShader("src/DefaultShaders/defaultPrimitiveVertShader.vert", "src/DefaultShaders/defaultPrimitiveFragShader.frag", "defaultPrimitiveShader");
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
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	Texture* texture = new Texture(data, width, height, nrChannels);
	textureMap_[textureName] = texture;
	stbi_image_free(data);
}

Texture* ResourceEngine::getTexture(const std::string& textureName) {
	return textureMap_[textureName];
}

void ResourceEngine::addSound(const std::string& soundFilename, const std::string& soundName) {
	Sound* sound = new Sound(soundFilename);
	soundMap_[soundName] = sound;
}

Sound* ResourceEngine::getSound(const std::string& soundName) {
	return soundMap_[soundName];
};