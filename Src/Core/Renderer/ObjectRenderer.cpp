
#include "ObjectRenderer.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

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
	
	shaderManager.UpdateShaderUniforms(object.GetShaderProgram(), object, window, lightSource, camera);

	object.TransformObject();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


