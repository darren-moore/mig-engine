#include "Game.h"
#include "System.h"

// PhysicsEngine includes rigid body, soft body, and fluid computations.
// ParticleEngine
// TextEngine
// AudioEngine
// GUI Engine

Game::Game(GLuint windowWidth, GLuint windowHeight) {
	ioEngine_.init(windowWidth, windowHeight);
	Locator::provide(&ioEngine_);

	resourceEngine_.init();
	Locator::provide(&resourceEngine_);

	renderEngine_.init();
	Locator::provide(&renderEngine_);
}

// Shutdown sub-engines in inverse start-order.
void Game::stop() {
	renderEngine_.stop();
	resourceEngine_.stop();
	ioEngine_.stop();
}

void Game::start() {
	for (auto& system : systems_) {
		system->init();
	}

	float lastFrameTime = 0;
	renderEngine_.setClearColor(0, 0, 0, 1);
	while (true) {
		if (ioEngine_.shouldClose()) {
			stop();
			break;
		}

		float currentFrameTime = ioEngine_.getCurrentWindowTime();
		dt_ = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		ioEngine_.processInput();
		renderEngine_.clear();
		this->update(dt_);
		ioEngine_.swapBuffers();
	}

}


void Game::addEntity(Entity *entity) {
	entities_.push_back(entity);
}
void Game::addSystem(System* system) {
	systems_.push_back(system);
}


void Game::update(const float dt) {
	for (auto& system : systems_) {
		for (auto& e : entities_) {
			system->validateAndExecute(*e, dt);
		}
	}

	// System order defined by order added to game.

	// Update engines here.
}
