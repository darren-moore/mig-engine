#include "AudioEngine.h"

using namespace irrklang;

void AudioEngine::init() { 
	iksound = createIrrKlangDevice(); 
}
void AudioEngine::stop() { 
	iksound->drop();
}

void AudioEngine::playSound(Sound* sound, bool loop) {
	iksound->play2D(sound->getFilename().c_str(), loop);
}