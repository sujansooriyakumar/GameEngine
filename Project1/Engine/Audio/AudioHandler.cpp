#include "AudioHandler.h"

std::unique_ptr<AudioHandler> AudioHandler::audioHandlerInstance = nullptr;
std::map<std::string, FMOD::Sound*> AudioHandler::soundMap = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*> AudioHandler::channelMap = std::map<int, FMOD::Channel*>();


AudioHandler::AudioHandler() : channelCount(0), system(nullptr), position(glm::vec3(0)),velocity(glm::vec3(0)), forwardDirection(glm::vec3(0,0,-1)), upDirection(glm::vec3(0,1,0)) 
{

}

AudioHandler::~AudioHandler()
{
}

FMOD_VECTOR AudioHandler::glmToFMOD(glm::vec3 vector_)
{
	// create FMOD_VECTOR variable
	FMOD_VECTOR result;
	// set the x,y,z to the x,y,z of glm::vec3
	result.x = vector_.x;
	result.y = vector_.y;
	result.z = vector_.z;
	//return FMOD variable
	return result;
}

void AudioHandler::LoadSound(std::string name_, bool loop, bool is3D, bool playbackMethod)
{
	if (GetSound(name_) != nullptr) {
		return;
	}
	FMOD_MODE mode = FMOD_MODE(FMOD_DEFAULT);
	mode |= loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	mode |= is3D ? FMOD_3D : FMOD_2D;
	mode |= playbackMethod ? FMOD_CREATESAMPLE : FMOD_CREATESAMPLE;


	FMOD::Sound* sound = nullptr;
	std::string path = "./Resources/Audio/" + name_ + ".wav";
	const char* a = path.c_str();
	if (system->createSound(a, mode, nullptr, &sound) == FMOD_OK) {
		soundMap[name_] = sound;
	}


}

int AudioHandler::PlaySound(std::string name_, glm::vec3 pos_, glm::vec3 vel_, float volume_)
{
	std::cout << "playing" << std::endl;
	int channelID = -1;
	if (GetSound(name_) == nullptr) {
		LoadSound(name_, true, true, true);
	}

	FMOD::Channel* channel = nullptr;
	system->playSound(soundMap[name_], nullptr, true, &channel);
	
	 channel->set3DAttributes(&glmToFMOD(pos_), &glmToFMOD(vel_));
	channel->setVolume(volume_);
	
	 channel->setPaused(false);
	channelID = channelCount;
	channelCount++;
	channelMap[channelID] = channel;
	return channelID;
	// find the sound in the map with the correct name
	

}

FMOD::Sound* AudioHandler::GetSound(std::string soundName_)
{
	std::map<std::string, FMOD::Sound*>::iterator soundIt = soundMap.begin();

	while (soundIt != soundMap.end()) {
		if (soundIt->first == soundName_) {
			return soundIt->second;
		}

		soundIt++;
	}
	
	return nullptr;

}

void AudioHandler::UpdateChannelPositionVelocity(int channelID_, glm::vec3 newPos_, glm::vec3 newVel_)
{
	std::map<int, FMOD::Channel*>::iterator channelIt = channelMap.begin();
	while (channelIt != channelMap.end()) {
		if (channelIt->first == channelID_) {
			channelIt->second->set3DAttributes(&glmToFMOD(newPos_), &glmToFMOD(newVel_));

		}
		channelIt++;

	}
	

}

bool AudioHandler::isPlaying(int channelID_)
{
	std::map<int, FMOD::Channel*>::iterator channelIt = channelMap.begin();

	while (channelIt != channelMap.end()) {
		if (channelIt->first == channelID_) {
			bool result;
			channelIt->second->isPlaying(&result);
			return result;
		}
		channelIt++;

	}
	
	return false;
}

bool AudioHandler::Initialize(glm::vec3 position_, glm::vec3 velocity_, glm::vec3 forwardDirection_, glm::vec3 upDirection_)
{
	
	position = position_;
	velocity = velocity_;
	forwardDirection = forwardDirection_;
	upDirection = upDirection_;
	FMOD::System_Create(&system);
	// if the number of drivers in the system is 0, stop the function here
	int result;
	system->getNumDrivers(&result);
	if (result == 0) {
		return false; 
	}
	system->init(5, FMOD_INIT_NORMAL, nullptr);
	if (system->set3DListenerAttributes(0, &glmToFMOD(position), &glmToFMOD(velocity),
		&glmToFMOD(forwardDirection), &glmToFMOD(upDirection)) == FMOD_OK) {
		return true;
	}
	


	
}

void AudioHandler::OnDestroy()
{
	std::map<std::string, FMOD::Sound*>::iterator soundIt = soundMap.begin();
	std::map<int, FMOD::Channel*>::iterator channelIt = channelMap.begin();

	while (soundIt != soundMap.end()) {
		soundIt->second->release();
		soundIt->second = nullptr;

		soundIt++;
	}

	while (channelIt != channelMap.end()) {
		channelIt->second->stop();
		channelIt->second = nullptr;

		channelIt++;
	}
	system->release();
	system = nullptr;
}

void AudioHandler::Update(float deltaTime_)
{
	system->update();
}

AudioHandler* AudioHandler::GetInstance()
{
	if (audioHandlerInstance.get() == nullptr)
	{
		audioHandlerInstance.reset(new AudioHandler);
	}
	return audioHandlerInstance.get();
}
