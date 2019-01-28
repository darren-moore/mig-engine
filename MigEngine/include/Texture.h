#pragma once
#include <glad/glad.h>

class Texture {
public:
	Texture(unsigned char* textureData, int width, int height, int nrChannels);
	~Texture();
	void bind();
	unsigned int ID;
	GLuint Internal_Format; // Format of texture object
	GLuint Image_Format; // Format of loaded image
	// Texture configuration
	GLuint Wrap_S; // Wrapping mode on S axis
	GLuint Wrap_T; // Wrapping mode on T axis
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
	GLuint width;
	GLuint height;
	
};