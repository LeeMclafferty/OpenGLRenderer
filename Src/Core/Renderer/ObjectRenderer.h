#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <gtc/quaternion.hpp>
#include <memory>

#include "Utilities/Utilities.h"

class ObjectRenderer
{

public:
	ObjectRenderer(GLFWwindow* win, std::shared_ptr<class Camera> cam, std::shared_ptr<class Scene> inScene);
	void Draw();

private:

	GLFWwindow* window;
	std::shared_ptr<class Camera> camera;
	std::shared_ptr<class Scene> scene;
	Utilities utilities;
	std::shared_ptr<class LightSource> lightSource;
	std::shared_ptr<class Object3D> cubeObject;
	std::shared_ptr<class InputHandler> inputHandler;

	void DrawObject(Object3D& object);
};

