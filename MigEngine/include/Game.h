#pragma once

#include "IOEngine.h"
#include "RenderEngine.h"
#include "ResourceEngine.h"
#include "CollisionEngine.h"

#include "Locator.h"
#include "Entity.h"
#include "Component.h"
#include "System.h"

#include "irrKlang.h"
#include <vector>

class Game {

public:
	Game(GLuint windowWidth = 800, GLuint windowHeight = 600);
	~Game() {}
	void stop();
	void start();
	void update(float const dt);
	void addEntity(std::shared_ptr<Entity> entity);
	void addSystem(System* system);
	float getDt() { return dt_; }

private:
	std::vector<std::shared_ptr<Entity>> entities_;
	std::vector<System*> systems_;

	ResourceEngine resourceEngine_;
	RenderEngine renderEngine_;
	IOEngine ioEngine_;
	CollisionEngine collisionEngine_;
	AudioEngine audioEngine_;

	float dt_ = 0;
};
