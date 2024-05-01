#include "LightSource.h"
#include "PremadeShapes/PremadeShapes.h"

LightSource::LightSource()
	:color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	size_t vertexCount = PremadeShapes::lightSource.size();
	size_t indexCount = PremadeShapes::cubeIndices.size();
	SetShapeData(
		PremadeShapes::lightSource, PremadeShapes::cubeIndices,
		vertexCount, indexCount
	);
	SetShaderProgram(CreateShaderProgram("Resources/Shaders/LightSource.shader"));
	SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	CreateShapeOnGPU();
}

void LightSource::Orbit(const glm::vec3& centerVec, float orbitRadius, float deltaTime, float speed)
{

	static float angle = 0.0f;
	glm::vec3 orbitingVec(0.f, 0.f, 0.f);
	angle += speed * deltaTime;

	// Ensure the angle stays within the range of 0 to 2*pi
	if (angle > glm::two_pi<float>())
	{
		angle -= glm::two_pi<float>();
	}

	// Calculate the new position for the orbiting vector
	orbitingVec.x = centerVec.x + orbitRadius * cos(angle);
	//orbitingVec.y = centerVec.y + orbitRadius * sin(angle);
	orbitingVec.z = centerVec.z + orbitRadius * sin(angle);

	SetPosition(orbitingVec);
}
