#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <gtc/quaternion.hpp>
#include "Object/TexturedObject/TexturedObject.h"
#include "Object/LightSource/LightSource.h"
#include "Utilities/Utilities.h"

class Camera;

class ObjectRenderer
{

public:
	ObjectRenderer(GLFWwindow* win, Camera* cam);
	void Draw();

	TexturedObject GetObject() const { return cubeObject; }
	TexturedObject& GetObjectRef() { return cubeObject; }
private:

	GLFWwindow* window;
	Camera* camera;
	TexturedObject cubeObject;
	LightSource lightSource;
	Utilities utilties;

	
	void SendProjectionData(GLuint shaderProgram, float fov, float aspectRatio, float nearPlane, float farPlane);
	void SetupCube();
	void SetupLightSource();

	void DrawObject(Object3D& object);

	void UpdateNormalUniform(GLuint shaderProgram, Object3D& obj);
	void SetUniforms(GLuint shaderProgram);
};

