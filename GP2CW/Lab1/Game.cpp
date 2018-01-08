#include "Game.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;
Transform playerTransform;
Transform bulletTransform;


Game::Game()
{
	currentGameState = GameState::PLAY;
	GameDisplay* mainGameDisplay = new GameDisplay(); //new display
    Mesh* enemyMesh1();
	Mesh* enemyMesh2();
	Mesh* projectileMesh();
	Mesh* playerMesh();
	Sound* soundDevice();
}

Game::~Game()
{
}

void Game::run()
{
	InitialiseSystems(); 
	mainGameLoop();
}

void Game::InitialiseSystems()
{
	mainGameDisplay.inititaliseDisplay(); // tells mainGameDisplay to draw the window
	whistle = soundDevice.loadSound("..\\res\\bang.wav");
	gameMusic = soundDevice.loadSound("..\\res\\background.wav");
	
	enemyMesh1.loadGameModel("..\\res\\monkey3.obj"); //both enemies will be set to the monkey mode
	enemyMesh2.loadGameModel("..\\res\\monkey3.obj"); 
	playerMesh.loadGameModel("..\\res\\f.obj"); //player is set to a fighter jet model
	projectileMesh.loadGameModel("..\\res\\spraycan.obj");

	goingLeft = true; //starts the enemies going left at the beginning of the game
	playerPosition = 0; //starts the tracker of the player's X position at the origin
	projectileActive = false; //starts program off with no bullets fired whihc means no bullets drawn
	
	gameCamera.cameraSetUp(glm::vec3(0, 0, -5), 70.0f, (float)mainGameDisplay.findWidth()/mainGameDisplay.findHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void Game::mainGameLoop()
{
	while (currentGameState != GameState::EXIT)
	{
		inputProcessing();
		drawTheGame();
		collisionDetection(projectileMesh.FindSpherePosition(), projectileMesh.FindRadiusOfSphere(), enemyMesh1.FindSpherePosition(), enemyMesh1.FindRadiusOfSphere());
		collisionDetection(projectileMesh.FindSpherePosition(), projectileMesh.FindRadiusOfSphere(), enemyMesh2.FindSpherePosition(), enemyMesh2.FindRadiusOfSphere()); //this line is carried out twice with only the enemymesh number changing to test if the bullet hit either opponent
		playSound(gameMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void Game::inputProcessing()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{
			case SDLK_a:
				if (playerPosition < 2) { //prevents player moving out of screen
					playerPosition += 0.1;
				}
				break;
			case SDLK_d:
				if (playerPosition > -2) {
					playerPosition -= 0.1;
				}
				break;
			case SDLK_SPACE:
				bulletTransform.SetPos(glm::vec3(playerTransform.GetPos()->x, playerTransform.GetPos()->y, 0)); //bullet initial position always equal to players since it shoots from player
				projectileActive = true;
				playSound(whistle, glm::vec3(0.0f, 0.0f, 0.0f));
				break;
			}
				break;
			case SDL_QUIT:
				currentGameState = GameState::EXIT;
				break;
		}
	}
	
}


bool Game::collisionDetection(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z)); //works out the distance between the objects

	if (distance < (m1Rad + m2Rad)) //checks to see if the distance is short enough to mean that overlapping colliders are guarenteed
	{
		soundDevice.posOfListener(gameCamera.findCameraPos(), m1Pos); //add bool to mesh
		playSound(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

void Game::playSound(unsigned int Source, glm::vec3 pos)
{
	
	ALint state; 
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		soundDevice.playSound2(Source, pos);
	}
}

void Game::drawTheGame()
{
	mainGameDisplay.displayClearing(0.0f, 0.0f, 0.0f, 1.0f); //clears screen to be drawn on again
	
	GameShaders shader("..\\res\\shader"); //new shader
	Texture texture("..\\res\\bricks.jpg"); //load texture
	Texture texture1("..\\res\\mat.png"); //load texture
	Texture texture2("..\\res\\bullet.jpg"); //load texture
	

	transform.SetPos(glm::vec3(counter, 1, 0.0)); //sets the position for the first enemy
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5)); //causes enemy to rotate depending on which way it is traveling
	transform.SetScale(glm::vec3(0.3, 0.3, 0.3)); //stops enemy being too large

	shader.Bind();
	shader.Update(transform, gameCamera);
	texture.Bind(0);
	enemyMesh1.draw();
	enemyMesh1.updateDataOfSphere(*transform.GetPos(), 0.10f);
	

	transform.SetPos(glm::vec3(counter + 1.5, 1, 0)); //does same as above for 2nd enemy, spacing exactly 1.5 away
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.3, 0.3, 0.3));

	shader.Bind();
	shader.Update(transform, gameCamera);
	texture.Bind(0);
	enemyMesh2.draw();
	enemyMesh2.updateDataOfSphere(*transform.GetPos(), 0.10f);
	if (counter > 2) {
		goingLeft = false;
	}
	if (counter < -2) {
		goingLeft = true;
	}
	counter += goingLeft ? 0.05f : -0.05;

	

	playerTransform.SetPos(glm::vec3(playerPosition, -1, 0)); //does same as above but for player
	playerTransform.SetRot(glm::vec3(-0.3, 0.0, 0));
	playerTransform.SetScale(glm::vec3(0.15, 0.15, 0.15));

	shader.Bind();
	shader.Update(playerTransform, gameCamera);
	texture1.Bind(0);
	playerMesh.draw();
	playerMesh.updateDataOfSphere(*playerTransform.GetPos(), 0.62f);

	if (projectileActive) {
		bulletTransform.SetPos(glm::vec3(bulletTransform.GetPos()->x, bulletTransform.GetPos()->y + 0.25, 0));
		bulletTransform.SetRot(glm::vec3(0.0, 0.0, 0.0));
		bulletTransform.SetScale(glm::vec3(0.01, 0.01, 0.01));

		shader.Bind();
		shader.Update(bulletTransform, gameCamera);
		texture2.Bind(0);
		projectileMesh.draw();
		projectileMesh.updateDataOfSphere(*transform.GetPos(), 0.10f);
	}

				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	mainGameDisplay.bufferSwapping();
} 