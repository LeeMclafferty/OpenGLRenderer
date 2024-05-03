#pragma once
#include "Object/Object3D.h"

class LightSource : public Object3D
{
public:
	LightSource();
	//virtual void CreateShapeOnGPU() override;
	
	glm::vec4 GetColor() { return color; }

	void SetColor(glm::vec4 inColor) { color = inColor; }
	void Orbit(const glm::vec3& centerVec, float orbitRadius, float deltaTime, float speed);
private:
	void Setup();
	glm::vec4 color;
};

