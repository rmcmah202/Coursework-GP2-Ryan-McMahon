#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "camera.h"

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->position = pos;
		this->rotation = rot;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 positionOfMaterial = glm::translate(position);
		glm::mat4 scaleOfMaterial = glm::scale(scale);
		glm::mat4 rotationX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotationY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotationZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotationOfMaterial = rotationX * rotationY * rotationZ;

		return positionOfMaterial * rotationOfMaterial * scaleOfMaterial;
	}

	inline glm::vec3* GetPos() { return &position; } //getters
	inline glm::vec3* GetRot() { return &rotation; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPos(glm::vec3& pos) { this->position = pos; } // setters
	inline void SetRot(glm::vec3& rot) { this->rotation = rot; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }
protected:
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};


