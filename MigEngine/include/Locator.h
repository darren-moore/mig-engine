#pragma once

#include "RenderEngine.h"
#include "IOEngine.h"
#include "ResourceEngine.h"
#include "CollisionEngine.h"
#include "AudioEngine.h"

// An implementation of the Service Locator pattern.
class Locator {
public:

	static IOEngine* getIOEngine() { return ioEngine_; }
	static void provide(IOEngine* ioEngine) { ioEngine_ = ioEngine; }

	static RenderEngine* getRenderEngine() { return renderEngine_; }
	static void provide(RenderEngine* renderEngine) { renderEngine_ = renderEngine; }

	static ResourceEngine* getResourceEngine() { return resourceEngine_; }
	static void provide(ResourceEngine* resourceEngine) { resourceEngine_ = resourceEngine; }

	static CollisionEngine* getCollisionEngine() { return collisionEngine_; }
	static void provide(CollisionEngine* collisionEngine) { collisionEngine_ = collisionEngine; }

	static AudioEngine* getAudioEngine() { return audioEngine_; }
	static void provide(AudioEngine* audioEngine) { audioEngine_ = audioEngine; }

private:
	static IOEngine* ioEngine_;
	static RenderEngine* renderEngine_;
	static ResourceEngine* resourceEngine_;
	static CollisionEngine* collisionEngine_;
	static AudioEngine* audioEngine_;
};
