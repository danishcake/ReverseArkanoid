#pragma once
#include <string>
#include <map>

struct Mix_Chunk;

namespace SoundStatus
{
	enum Enum
	{
		ErrorInitialising, OK
	};
}

class SoundManager
{
private:
	SoundManager(void);
	~SoundManager(void);
	SoundStatus::Enum status_;

	std::map<std::string, Mix_Chunk*> samples_;

	Mix_Chunk* GetChunk(std::string _filename);
	int PlayEnqueuedSample(std::string _filename, unsigned char _distance);
	
	
public:
	static SoundManager& Instance();
	void PlaySample(std::string _filename);
	int PlayLoopingSample(std::string _filename);
	void StopChannel(int _channel);
	void SetVolume(int _channel, float _volume);
};
