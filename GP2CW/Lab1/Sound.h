#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Sound
{
	struct Datasound {
		int sourceID, bufferID;
		char* buffer;
		std::string name;
		Datasound(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	struct Vector3
	{
		float x, y, z;
	};
	std::vector<Datasound> soundDatas;
	ALCcontext* context;
	ALCdevice *device;
	bool bigEndian();
	int intConversion(char* buffer, int length);
	char* loadWAVfile(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	Sound();
	~Sound();
	unsigned int loadSound(const char* filename);
	void deleteSound(unsigned int id);
	void playSound(unsigned int id);
	void playSound2(unsigned int id, glm::vec3& pos);
	void stopSound(unsigned int id);
	void posOfListener(glm::vec3& pos, glm::vec3& camLookAt);

private:
	
};

