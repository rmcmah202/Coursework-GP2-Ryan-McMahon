#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "GameDisplay.h" 
#include "MyShader.h"
#include "Meshes.h"
#include "Texture.h"
#include "transform.h"
#include "Sound.h"

enum class GameState{PLAY, EXIT};

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void InitialiseSystems();
	void inputProcessing();
	void mainGameLoop();
	void drawTheGame();
	bool collisionDetection(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playSound(unsigned int Source, glm::vec3 pos);

	GameDisplay mainGameDisplay;
	GameState currentGameState;
	Mesh enemyMesh1;
	Mesh enemyMesh2;
	Mesh projectileMesh;
	Mesh playerMesh;
	MainCamera gameCamera;
	Sound soundDevice;

	float counter;
	bool goingLeft;
	bool projectileActive;
	float playerPosition;
	unsigned int whistle;
	unsigned int gameMusic;
};

