#pragma once

#include <glad/glad.h>
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string> 

class Shader {
public:
	unsigned int ID;

	Shader(std::string const& vertexPath, std::string const& fragmentPath);

	void use();

	void setBool(std::string const& name, bool value) const;
	void setInt(std::string const& name, int value) const;
	void setFloat(std::string const& name, float value) const;
	//void setVec3(std::string const& name, Eigen::Vector3f value) const;
	//void setMat4(std::string const& name, Eigen::Matrix4f value) const;
	void setVec3(std::string const& name, glm::vec3 value) const;
	void setMat4(std::string const& name, glm::mat4 value) const;

};
