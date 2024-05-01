#pragma once
#include <GL/glew.h>
#include <string>
#include <GLFW/glfw3.h>
#include <memory>

class Engine
{

public:
	Engine(struct GLFWwindow* glWin);
	void MainLoop();

private:
	struct GLFWwindow* window;
	std::shared_ptr<class Camera> camera;
	std::shared_ptr<class Scene> scene;
	std::shared_ptr<class ObjectRenderer> objectRenderer;
	std::shared_ptr<class InputHandler> inputHandler;
};

