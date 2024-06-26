#include "ShaderManager.h"

#include "Object/Object3D.h"
#include "Object/LightSource/LightSource.h"

#include "Camera.h"
#include "Utilities/Utilities.h"


ShaderManager::ShaderSource ShaderManager::ParseShader(const std::string& filePath)
{

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::fstream stream(filePath);

	std::string line;
	std::stringstream ss[2];
	ShaderType shaderType = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				shaderType = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				shaderType = ShaderType::FRAGMENT;
			}
		}
		else
		{
			// Use the enum value as the array index
			ss[(int)shaderType] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

bool ShaderManager::LinkedSuccessfully(int& result, const GLuint& id)
{
	if (result == GL_FALSE)
	{
		int len;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
		char* message = new GLchar[len];
		glGetProgramInfoLog(id, len, &len, message);

		std::cout << message << std::endl;

		glDeleteShader(id);
		delete[] message;
		return false;
	}
	return true;
}

bool ShaderManager::CompiledSuccessfully(int& result, const GLuint& id, const GLuint& glType)
{
	if (result == GL_FALSE)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char* message = new GLchar[len];
		glGetShaderInfoLog(id, len, &len, message);

		std::cout << "Failed to compile " << (glType == GL_VERTEX_SHADER ? "vertex" : "fragment");
		std::cout << message << std::endl;

		glDeleteShader(id);
		delete[] message;
		return false;
	}
	return true;
}

void ShaderManager::SetUniformMatrix4(GLuint shader, std::string uniformName, glm::mat4 matrix)
{
	GLint matrixUniform = glGetUniformLocation(shader, uniformName.c_str());
	glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderManager::SetUniformMatrix3(GLuint shader, std::string uniformName, glm::mat3 matrix)
{
	GLint matrixUniform = glGetUniformLocation(shader, uniformName.c_str());
	glUniformMatrix3fv(matrixUniform, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderManager::SetUniformVec3(GLuint shader, std::string uniformName, glm::vec3 vector3)
{
	GLint vecUniform = glGetUniformLocation(shader, uniformName.c_str());
	glUniform3f(vecUniform, vector3.x, vector3.y, vector3.z);
}

void ShaderManager::SetUniformVec4(GLuint shader, std::string uniformName, glm::vec4 vector4)
{
	GLint vecUniform = glGetUniformLocation(shader, uniformName.c_str());
	glUniform4f(vecUniform, vector4.x, vector4.y, vector4.z, vector4.w);
}

void ShaderManager::SetUniformSampler2D(GLuint shader, std::string uniformName)
{
	GLint textureUniformLoc = glGetUniformLocation(shader, uniformName.c_str());
	glUseProgram(shader);
	glUniform1i(textureUniformLoc, 0); // Always using index 0 for now
}

void ShaderManager::SetUniformFloat(GLuint shader, std::string uniformname, float value)
{
	GLint floatUniformLoc = glGetUniformLocation(shader, uniformname.c_str());
	glUniform1f(floatUniformLoc, value);
}

unsigned int ShaderManager::CompileShader(unsigned int glType, const std::string& source)
{
	GLuint id = glCreateShader(glType);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!CompiledSuccessfully(result, id, glType))
	{
		return 0;
	}

	return id;
}

GLuint ShaderManager::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	// Read in Shaders .. Link them .. Compile into single shader program
	GLuint shaderProgram = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	int result;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!LinkedSuccessfully(result, shaderProgram))
	{
		return 0;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return shaderProgram;
}

void ShaderManager::UpdateShaderUniforms(GLuint shaderProgram, Object3D& object, GLFWwindow* win, LightSource& lightSource, Camera* camera)
{
	if (!camera || !win)
		return;

	Utilities utilities;

	if (camera)
	{
		int w = 0, h = 0;
		camera->SetAspectRatio(utilities.GetAspectRatio(win, w, h));
	}

	camera->UpdateProjectionMatrix();
	SetUniformMatrix4(shaderProgram, "projectionMatrix", camera->GetProjectionMatrix());
	SetUniformMatrix4(shaderProgram, "viewMatrix", camera->GetViewMatrix());
	SetUniformVec4(object.GetShaderProgram(), "lightingColor", lightSource.GetColor());
	SetUniformSampler2D(shaderProgram, "textureImg");
	SetUniformVec3(shaderProgram, "lightPos", lightSource.GetPosition());
	SetUniformVec3(shaderProgram, "cameraPos", camera->GetGlobalPosition());

	SetUniformVec4(shaderProgram, "material.ambient", object.GetMaterial().GetAmbientColor());
	SetUniformVec4(shaderProgram, "material.diffuse", object.GetMaterial().GetDiffuseColor());
	SetUniformVec4(shaderProgram, "material.specular", object.GetMaterial().GetSpecularColor());
	SetUniformFloat(shaderProgram,"material.shininess", object.GetMaterial().GetShininess());

	SetUniformVec4(shaderProgram, "light.ambient", lightSource.GetMaterial().GetAmbientColor());
	SetUniformVec4(shaderProgram, "light.diffuse", lightSource.GetMaterial().GetDiffuseColor());
	SetUniformVec4(shaderProgram, "light.specular", lightSource.GetMaterial().GetSpecularColor());

	glm::mat4 modelMatrix = object.GetTransformationMatrix();
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
	SetUniformMatrix3(shaderProgram, "normalMatrix", normalMatrix);
}


