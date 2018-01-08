#include "GameDisplay.h"


GameDisplay::GameDisplay()
{
	mainWindow = nullptr; //initialise to generate null access violation for debugging. 
	widthOfScreen = 1024.0f;
	heightOfScreen = 768.0f; 
}

GameDisplay::~GameDisplay()
{
	SDL_GL_DeleteContext(glContext); // delete context
	SDL_DestroyWindow(mainWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in initDisplay())
	SDL_Quit();
}

float GameDisplay::findWidth() { return widthOfScreen; } //getters
float GameDisplay::findHeight() { return heightOfScreen; }

void GameDisplay::returnError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void GameDisplay::bufferSwapping()
{
	SDL_GL_SwapWindow(mainWindow); //swap buffers
}

void GameDisplay::displayClearing(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void GameDisplay::inititaliseDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	mainWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)widthOfScreen, (int)heightOfScreen, SDL_WINDOW_OPENGL); // create window

	if (mainWindow == nullptr)
	{
		returnError("window failed to create");
	}

	glContext = SDL_GL_CreateContext(mainWindow);

	if (glContext == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}