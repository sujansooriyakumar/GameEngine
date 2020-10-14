#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include "..//Core/Component.h"
#include "..//Rendering/3D/GameObject.h"

class AudioSource : public Component {
public:
	AudioSource(std::string name_, bool loop, bool is3D, bool playbackMethod);
	virtual ~AudioSource();
	bool OnCreate(GameObject* parent_) override;
	void Update(float deltaTime_) override;
	bool isPlaying();
	void PlaySound();
	friend class AudioHandler;


private:
	std::string name;
	int channelID;


};

#endif // !AUDIOSOURCE_H
