#include "StdAfx.h"
#include "SoundManager.h"
#include <SDL_mixer.h>


SoundManager::SoundManager(void)
{
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16; 
	int audio_channels = 2;
	int audio_buffers = 1024;

	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
	{
		Logger::ErrorOut() << "Unable to open audio!\n";
		status_ = SoundStatus::ErrorInitialising;
	} else
	{
		Mix_AllocateChannels(32);
		Logger::ErrorOut() << "Sound initialised\n";
		status_ = SoundStatus::OK;
	}

}

SoundManager::~SoundManager(void)
{
}

SoundManager& SoundManager::Instance()
{
	static SoundManager* instance = NULL;
	if(!instance)
		instance = new SoundManager();
	return *instance;
}

void SoundManager::PlaySample(std::string _filename)
{
	PlayEnqueuedSample(_filename, 0);
}

Mix_Chunk* SoundManager::GetChunk(std::string _filename)
{
	Mix_Chunk* sample = NULL;
	if(samples_.find(_filename) != samples_.end())
	{
		sample = samples_[_filename];
	} else
	{
		sample = Mix_LoadWAV((std::string("Sounds/") + _filename).c_str());
		
		if(sample != NULL)
			samples_[_filename] = sample;
		else
			Logger::ErrorOut() << "Unable to load sound:" << _filename << "\n";
	}
	return sample;
}

int SoundManager::PlayLoopingSample(std::string _filename)
{
	//Look the sound up, it's probably already loaded. If not then load it.
	if(status_ != SoundStatus::OK)
		return -1;

	Mix_Chunk* sample = GetChunk(_filename);
	if(sample)
	{
		//Play the sound
		return Mix_PlayChannel(-1, sample, -1);
	}
	return -1;
}

int SoundManager::PlayEnqueuedSample(std::string _filename, unsigned char _distance)
{
	//Look the sound up, it's probably already loaded. If not then load it.
	if(status_ != SoundStatus::OK)
		return -1;

	Mix_Chunk* sample = GetChunk(_filename);
	if(sample)
	{
		//Play the sound
		int channel = Mix_PlayChannel(-1, sample, 0);
		
		if(channel >= 0) Mix_SetDistance(channel, _distance);
		return channel;
	}
	return -1;
}

void SoundManager::StopChannel(int _channel)
{
	if(status_ != SoundStatus::OK)
		return;
	Mix_HaltChannel(_channel);
}

void SoundManager::SetVolume(int _channel, float _volume)
{
	if(status_ != SoundStatus::OK)
		return;
	unsigned char distance = (1.0f - _volume) * 255;
	Mix_SetDistance(_channel, distance);
}

