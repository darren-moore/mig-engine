#pragma once

#include <glad/glad.h>
#include <Eigen/Core>

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
	void setVec3(std::string const& name, const Eigen::Vector3f& value) const;
	void setMat4(std::string const& name, const Eigen::Matrix4f& value) const;
};
