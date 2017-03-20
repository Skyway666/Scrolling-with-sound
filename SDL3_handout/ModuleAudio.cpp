#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio(): Module()
{

}

ModuleAudio::~ModuleAudio()
{

}

bool ModuleAudio::Init()
{
	if (Mix_Init(MIX_INIT_OGG) == 0)
	{
		LOG("An error has ocurred while initializing the audio: %s", SDL_GetError())
			return false;
	}

	return true;
}

Mix_Music* const ModuleAudio::Load(const char* path)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	music = Mix_LoadMUS(path);
	Mix_PlayMusic(music, -1);
}
bool ModuleAudio::CleanUp()
{

}
