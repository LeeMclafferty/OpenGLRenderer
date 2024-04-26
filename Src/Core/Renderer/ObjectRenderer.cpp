
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

}

void ObjectRenderer::Draw() 
{
	lightSource.Orbit(cubeObject.GetPosition(), 1.f, TimeManager::GetDeltaTime(), 2.f);
	DrawObject(cubeObject);
	DrawObject(lightSource);
}

void ObjectRenderer::DrawObject(Object3D& object)
{
	glUseProgram(object.GetShaderProgram());
	glBindVertexArray(object.GetVAO());
	
	UpdateShaderUniforms(object.GetShaderProgram(), object);

	object.TransformObject();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void ObjectRenderer::UpdateShaderUniforms(GLuint shaderProgram, Object3D& object)
{
	if (!camera || !window)
		return;

	if (camera)
	{
		int w = 0, h = 0;
		camera->SetAspectRatio(utilities.GetAspectRatio(window, w, h));
	}

	camera->UpdateProjectionMatrix();
	ShaderHelpers::SetUniformMatrix4(shaderProgram, "projectionMatrix", camera->GetProjectionMatrix());
	ShaderHelpers::SetUniformMatrix4(shaderProgram, "viewMatrix", camera->GetViewMatrix());
	ShaderHelpers::SetUniformVec4(cubeObject.GetShaderProgram(), "lightingColor", lightSource.GetColor());
	ShaderHelpers::SetUniformSampler2D(shaderProgram, "textureImg");
	ShaderHelpers::SetUniformVec3(shaderProgram, "lightPos", lightSource.GetPosition());
	ShaderHelpers::SetUniformVec3(shaderProgram, "cameraPos", camera->GetGlobalPosition());

	glm::mat4 modelMatrix = object.GetTransformationMatrix();
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
	ShaderHelpers::SetUniformMatrix3(shaderProgram, "normalMatrix", normalMatrix);
}

