#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class LightSource;
class Object3D;
class Camera;

class ShaderManager
{

public:
	struct ShaderSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	ShaderSource ParseShader(const std::string& filePath);
	bool LinkedSuccessfully(int& result, const GLuint& id);
	static bool CompiledSuccessfully(int& result, const GLuint& id, const GLuint& glType);
	void SetUniformMatrix4(GLuint shader, std::string uniformName, glm::mat4 matrix);
	void SetUniformMatrix3(GLuint shader, std::string uniformName, glm::mat3 matrix);
	void SetUniformVec3(GLuint shader, std::string uniformName, glm::vec3 vector3);
	void SetUniformVec4(GLuint shader, std::string uniformName, glm::vec4 vector4);
	void SetUniformSampler2D(GLuint shader, std::string uniformName);
	void SetUniformFloat(GLuint shader, std::string uniformname, float value);
	unsigned int CompileShader(unsigned int glType, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void UpdateShaderUniforms(GLuint shaderProgram, Object3D& object, GLFWwindow* win, LightSource& lightSource, Camera* camera);

};

