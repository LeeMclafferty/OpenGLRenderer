#pragma 
#include <glm.hpp>

class Camera
{
public:
	Camera();

	glm::vec3 GetGlobalPosition() { return globalPosition; }
	glm::vec3 GetCameraForward() const;
	glm::vec3 GetCameraRight() const;
	glm::vec3 GetCameraUp() const;

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }

	float GetFov() const { return fov; }
	float GetAspectRatio() const { return aspectRatio; }
	float GetNearPlane() const { return nearPlane; }
	float GetFarPlane() const { return farPlane; }

	void SetGlobalPosition(glm::vec3 pos) { globalPosition = pos; }
	void SetFov(float inFov) { fov = inFov; }
	void SetAspectRatio(float ratio);
	void SetNearPlane(float nearP) { nearPlane = nearP; }
	void SetFarPlane(float farP) { farPlane = farP; }

	void UpdateProjectionMatrix();

	void Rotate(glm::vec2 mouseDeltas);

	void Move(int key);

private:

	glm::vec3 globalPosition;
	glm::mat4 projectionMatrix;

	float lookSensitivity;
	float moveSensitivity;
	float cameraSpeed;

	float fov;
	float aspectRatio;
	float nearPlane;
	float farPlane;

	glm::vec3 forwardVector;
	glm::vec3 upVector;
	void UpdateLocalVectors(glm::mat4 rotation);
};

