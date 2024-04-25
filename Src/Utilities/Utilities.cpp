#include "Utilities.h"
#include <GLFW/glfw3.h>

float Utilities::GetAspectRatio(GLFWwindow* window, int w, int h)
{
	if (!window) return -1.f;

	glfwGetFramebufferSize(window, &w, &h);
	return (float)w / (float)h;
}
