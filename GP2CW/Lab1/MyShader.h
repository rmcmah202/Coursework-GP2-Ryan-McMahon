#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"

class GameShaders
{
public:
	GameShaders(const std::string& filename);

	void Bind(); //Set gpu to use our shaders
	void Update(const Transform& transform, const MainCamera& camera);

	std::string GameShaders::LoadShader(const std::string& fileName);
	void GameShaders::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint GameShaders::CreateShader(const std::string& text, unsigned int type);

    ~GameShaders();


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
