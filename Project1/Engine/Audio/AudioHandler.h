#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <string>
#include <map>
#include <memory>
#include<fmod.hpp>
#include<glm/glm.hpp>
#include "..//Core/Debug.h"
#include "AudioSource.h"

class AudioHandler {
public:
	AudioHandler(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator = (const AudioHandler&) = delete;
	AudioHandler& operator = (AudioHandler&&) = delete;

	bool Initialize(glm::vec3 position_ , glm::vec3 velocity_, glm::vec3 forwardDirection_, glm::vec3 upDirection_);
	void OnDestroy();
	void Update(float deltaTime_);
	static AudioHandler* GetInstance();

private:
	AudioHandler();
	~AudioHandler();

	FMOD_VECTOR glmToFMOD(glm::vec3 vector_);
	void LoadSound(std::string name_, bool loop, bool is3D, bool playbackMethod);
	int PlaySound(std::string name_, glm::vec3 pos_, glm::vec3 vel_, float volume_);
	FMOD::Sound* GetSound(std::string soundName_);
	void UpdateChannelPositionVelocity(int channelID_, glm::vec3 newPos_, glm::vec3 newVel_);
	bool isPlaying(int channelID_);
	glm::vec3 position, velocity, forwardDirection, upDirection;
	FMOD::System* system;
	int channelCount;
	friend class AudioSource;
	static std::map<std::string, FMOD::Sound*> soundMap;
	static std::map<int, FMOD::Channel*> channelMap;
	static std::unique_ptr<AudioHandler> audioHandlerInstance;
	friend std::default_delete<AudioHandler>;
};
#endif // !AUDIOHANDLER_H
