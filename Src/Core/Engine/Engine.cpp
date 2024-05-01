
#include "Engine.h"
#include <iostream>

#include "Time/TimeManager.h"
#include "Texture/Texture.h"
#include "ObjectRenderer.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Core/Scene/Scene.h"

Engine::Engine(GLFWwindow* glWin)
	:window(glWin), camera(std::make_shared<Camera>()), scene(std::make_shared<Scene>()), objectRenderer(std::make_shared<ObjectRenderer>(glWin, camera, scene)),
	inputHandler(std::make_shared<InputHandler>(glWin, objectRenderer, camera, scene))
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void Engine::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (objectRenderer) {
			objectRenderer->Draw();
		}
		TimeManager::UpdateDeltatime();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
