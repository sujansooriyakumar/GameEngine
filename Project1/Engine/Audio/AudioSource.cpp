#include "AudioHandler.h"

#include "AudioSource.h"





AudioSource::AudioSource(std::string name_, bool loop, bool is3D, bool playbackMethod)
{
	channelID = -1;
	name = name_;
	AudioHandler::GetInstance()->LoadSound(name_, loop, is3D, playbackMethod);
}

AudioSource::~AudioSource()
{
}

bool AudioSource::OnCreate(GameObject* parent_)
{
	parent = parent_;
	
	
	return true;
}

void AudioSource::Update(float deltaTime_)
{
	//AudioHandler::GetInstance()->UpdateChannelPositionVelocity(channelID, parent->GetPosition(), glm::vec3(0));
}

bool AudioSource::isPlaying()
{
	return AudioHandler::GetInstance()->isPlaying(channelID);
}

void AudioSource::PlaySound()
{
	channelID = AudioHandler::GetInstance()->PlaySound(name, parent->GetPosition(), glm::vec3(0), 1.0f);
	
}
