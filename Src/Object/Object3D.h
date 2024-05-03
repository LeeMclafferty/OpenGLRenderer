#pragma once

#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <vector>
#include <string>

#include "Object/Components/BufferManager.h"
#include "PremadeShapes/ShapeData.h"
#include "Texture/Texture.h"
#include "Shader/ShaderManager.h"
#include "Material/Material.h"

struct Vertex;

class Object3D
{
public:
	Object3D();
	Object3D(const char* tPath);



	// Getters
	glm::mat4 GetTransformationMatrix() const;
	glm::vec3 GetScale() const { return scale; }
	glm::quat GetRotation() const { return rotation; }
	glm::vec3 GetPosition() const { return position; }
	ShapeData GetShapeData() const { return shapeData; }

	GLuint GetVAO() { return bufferManager.GetVAO(); }
	GLuint GetVBO() { return bufferManager.GetVBO(); }
	GLuint GetEBO() { return bufferManager.GetEBO(); }
	GLuint GetShaderProgram() { return bufferManager.GetShaderProgram(); }

	Texture GetTexture() { return texture; }

	ShaderManager GetShaderManager() const { return shaderManager; }

	Material GetMaterial() const { return material; }

	// Setters
	void SetScale(const glm::vec3& inScale) { scale = inScale; }
	void SetRotation(const glm::quat& inRotation) { rotation = inRotation; }
	void SetPosition(const glm::vec3& translation) { position = translation; }
	void SetShapeData(std::vector<Vertex> verticies, std::vector<GLuint> indicies, size_t vertexCount, size_t indexCount);
	void SetShaderProgram(GLuint program) { bufferManager.SetShaderProgram(program); }
	
	void SetTexture(Texture tex) { texture = tex; }

	// Additive to current transforms
	void AddScale(glm::vec3 inScale) { scale += inScale; }
	void MovePosition(glm::vec3 translation) { position += translation; }
	void Rotate(glm::vec2 deltas);

	void TransformObject();
	virtual void CreateShapeOnGPU();

	void UpdateLocalVectors();

protected:
	GLuint CreateShaderProgram(const std::string path);

private:
	
	ShapeData shapeData;
	BufferManager bufferManager;
	ShaderManager shaderManager;
	Texture texture;
	Material material;

	// World Space
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 position; 
	glm::vec3 worldUp;
	glm::vec3 worldForward;
	glm::vec3 worldRight;

	// Local Space
	glm::vec3 objectUpVector;
	glm::vec3 objectForwardVector;
	glm::vec3 objectRightVector;

	void Setup();
};

