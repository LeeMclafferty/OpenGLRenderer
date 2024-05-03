
#include "ObjectRenderer.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Time/TimeManager.h"
#include "Core/Scene/Scene.h"
#include "Object/Object3D.h"
#include "Object/LightSource/LightSource.h"
#include "Core/Input/InputHandler.h"

ObjectRenderer::ObjectRenderer(GLFWwindow* win, std::shared_ptr<Camera> cam, std::shared_ptr<class Scene> inScene)
	: window(win), camera(cam), scene(inScene)
{
	scene->addObject("Default Cube", std::make_shared<Object3D>());
	scene->addObject("World Light", std::make_shared<LightSource>());

	lightSource = std::dynamic_pointer_cast<LightSource>(scene->GetObject("World Light"));
	cubeObject = std::dynamic_pointer_cast<Object3D>(scene->GetObject("Default Cube"));
}

void ObjectRenderer::Draw()
{
	if (lightSource && cubeObject) {
		lightSource->Orbit(cubeObject->GetPosition(), 1.f, TimeManager::GetDeltaTime(), 2.f);
		DrawObject(*cubeObject);
		DrawObject(*lightSource);
	}
}

void ObjectRenderer::DrawObject(Object3D& object)
{
	if (!lightSource || !cubeObject) return;

	glUseProgram(object.GetShaderProgram());
	glBindVertexArray(object.GetVAO());
	
	object.GetShaderManager().UpdateShaderUniforms(object.GetShaderProgram(), object, window, *lightSource, camera.get());

	object.TransformObject();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


