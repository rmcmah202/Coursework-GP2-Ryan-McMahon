#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->position = pos;
		this->textureCoordinates = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTextureCoordinates() { return &textureCoordinates; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 position;
	glm::vec2 textureCoordinates;
	glm::vec3 normal;
};

struct Sphere
{
public:

	Sphere() {}

	Sphere(glm::vec3& pos, float radius)
	{
		this->position = pos;
	}

	glm::vec3 FindPosition() { return position; }
	float FindRadius() { return radius; }

	void SetPos(glm::vec3 pos)
	{
		this->position = pos;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 position;
	float radius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();


	void draw();
	void initialise(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadGameModel(const std::string& filename);
	void initialiseModel(const IndexedModel& model);
	void updateDataOfSphere(glm::vec3 pos, float radius);
	glm::vec3 FindSpherePosition() { return sphereMesh.FindPosition(); }
	float FindRadiusOfSphere() { return sphereMesh.FindRadius(); }

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	Sphere sphereMesh;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};