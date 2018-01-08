#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class GameDisplay
{
public:
	GameDisplay();
	~GameDisplay();
	void inititaliseDisplay();
	void bufferSwapping();
	void displayClearing(float r, float g, float b, float a);

	float findWidth();
	float findHeight();

private:

	void returnError(std::string errorString);
	
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* mainWindow; //holds pointer to out window
	float widthOfScreen;
	float heightOfScreen;
};

