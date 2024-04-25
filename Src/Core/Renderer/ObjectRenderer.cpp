
#include "ObjectRenderer.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Shader/ShaderHelpers.h"
#include "PremadeShapes/PremadeShapes.h"
#include "Camera.h"
#include "Time/TimeManager.h"

ObjectRenderer::ObjectRenderer(GLFWwindow* win, Camera* cam)
	: window(win), camera(cam), 
	cubeObject("D:\\Dev\\LocalRepos\\OpenGLRenderer\\Resources\\Textures\\T_WorldGrid.png")
{
	SetupCube();
	SetupLightSource();
}

void ObjectRenderer::Draw() 
{
	lightSource.Orbit(cubeObject.GetPosition(), 1.f, TimeManager::GetDeltaTime(), 2.f);
	DrawObject(lightSource);
	DrawObject(cubeObject);
}

/* Setup Projection Matrix and send data to shader's uniform variable */
void ObjectRenderer::SendProjectionData(GLuint shaderProgram, float fov, float aspectRatio, float nearPlane, float farPlane)
{
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	ShaderHelpers::SetUniformMatrix4(shaderProgram, "projectionMatrix", projectionMatrix);
}

void ObjectRenderer::SetupCube()
{
	size_t vertexCount = PremadeShapes::cubeVertices.size();
	size_t indexCount = PremadeShapes::cubeIndices.size();
	cubeObject.SetShapeData(
		PremadeShapes::cubeVertices, PremadeShapes::cubeIndices,
		vertexCount, indexCount
	);
	cubeObject.CreateShapeOnGPU();

	ShaderHelpers::ShaderSource source = ShaderHelpers::ParseShader("Resources/Shaders/Basic.shader");
	cubeObject.SetShaderProgram(
		ShaderHelpers::CreateShader(
			source.vertexSource,
			source.fragmentSource
		)
	);
}

void ObjectRenderer::SetupLightSource()
{
	size_t vertexCount = PremadeShapes::LightSource.size();
	size_t indexCount = PremadeShapes::cubeIndices.size();
	lightSource.SetShapeData(
		PremadeShapes::LightSource, PremadeShapes::cubeIndices,
		vertexCount, indexCount
	);
	lightSource.CreateShapeOnGPU();

	ShaderHelpers::ShaderSource source = ShaderHelpers::ParseShader("Resources/Shaders/LightSource.shader");
	lightSource.SetShaderProgram(
		ShaderHelpers::CreateShader(
			source.vertexSource,
			source.fragmentSource
		)
	);

	//lightSource.SetPosition(glm::vec3(0.0f, 1.0f, -3.0f));
	lightSource.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
}

void ObjectRenderer::DrawObject(Object3D& object)
{
	glUseProgram(object.GetShaderProgram());

	int w = 0, h = 0;
	float AspectRatio = utilties.GetAspectRatio(window, w, h);

	SendProjectionData(object.GetShaderProgram(), 60.f, AspectRatio, .01f, 1000.f);
	SetUniforms(object.GetShaderProgram());
	ShaderHelpers::SetUniformMatrix4(object.GetShaderProgram(), "viewMatrix", camera->GetViewMatrix());
	UpdateNormalUniform(object.GetShaderProgram(), object);

	glBindVertexArray(object.GetVAO());
	object.TransformObject();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

// Update normal as view changes.
void ObjectRenderer::UpdateNormalUniform(GLuint shaderProgram, Object3D& obj)
{
	glm::mat4 modelMatrix = obj.GetTransformationMatrix();
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
	ShaderHelpers::SetUniformMatrix3(shaderProgram, "normalMatrix", normalMatrix);
}

void ObjectRenderer::SetUniforms(GLuint shaderProgram)
{
	ShaderHelpers::SetUniformMatrix4(shaderProgram, "viewMatrix", camera->GetViewMatrix());
	ShaderHelpers::SetUniformVec4(shaderProgram, "lightingColor", lightSource.GetColor());
	ShaderHelpers::SetUniformSampler2D(shaderProgram, "textureImg");
	ShaderHelpers::SetUniformVec3(shaderProgram, "lightPos", lightSource.GetPosition());
	ShaderHelpers::SetUniformVec3(shaderProgram, "cameraPos", camera->GetGlobalPosition());
}
