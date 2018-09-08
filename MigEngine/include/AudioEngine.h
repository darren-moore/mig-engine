#pragma once
#include "irrKlang.h"
#include "Sound.h"

class AudioEngine {

public:
	void init();
	void stop();

	void playSound(Sound* sound, bool loop);

private:
	irrklang::ISoundEngine* iksound;


};