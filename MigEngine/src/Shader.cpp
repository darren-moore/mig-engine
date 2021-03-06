
#include "Shader.h"

using namespace std;

Shader::Shader(std::string const &vertString, std::string const &fragString) {
	int  shaderSuccess;
	char shaderInfoLog[512];

	const char* vertexShaderSource = vertString.c_str();
	const char* fragmentShaderSource = fragString.c_str();

	// Vertex shader compilation
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check for shader compilation errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderSuccess);
	if (!shaderSuccess) {
		glGetShaderInfoLog(vertexShader, 512, NULL, shaderInfoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << shaderInfoLog << endl;
	}


	// Fragment shader compilation
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for shader compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderSuccess);
	if (!shaderSuccess) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, shaderInfoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << shaderInfoLog << endl;
	}

	// Attach shaders to shader program
	Shader::ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// Check for shader linking errors
	glGetShaderiv(ID, GL_LINK_STATUS, &shaderSuccess);
	if (!shaderSuccess) {
		glGetProgramInfoLog(ID, 512, NULL, shaderInfoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << shaderInfoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(std::string const &name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(std::string const &name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(std::string const &name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(std::string const &name, const Eigen::Vector3f& value) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value(0), value(1), value(2));
}


void Shader::setMat4(std::string const &name, const Eigen::Matrix4f& value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value.data());	// Eigen defaults to column-major matrix storage
}
