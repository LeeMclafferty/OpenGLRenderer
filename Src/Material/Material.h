#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Material
{
public:
	Material();

	glm::vec4 GetAmbientColor() const { return ambient; }
	glm::vec4 GetDiffuseColor() const { return diffuse; }
	glm::vec4 GetSpecularColor() const { return specular; }
	float GetShininess() const { return shininess; }

	void SetAmbientColor(glm::vec4 ambientColor) { ambient = ambientColor; }
	void SetDiffuseColor(glm::vec4 diffuseColor) { diffuse = diffuseColor; }
	void SetSpecularColor(glm::vec4 specularColor) { specular = specularColor; }
	void SetShininess(float shine) { shininess = shine; }

private:
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;
	
};

