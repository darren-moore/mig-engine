#include "Game.h"
#include "System.h"

Game::Game(GLuint windowWidth, GLuint windowHeight) {
	ioEngine_.init(windowWidth, windowHeight);
	Locator::provide(&ioEngine_);

	resourceEngine_.init();
	Locator::provide(&resourceEngine_);

	renderEngine_.init();
	Locator::provide(&renderEngine_);

	collisionEngine_.init();
	Locator::provide(&collisionEngine_);

	audioEngine_.init();
	Locator::provide(&audioEngine_);
}

// Shutdown sub-engines in inverse start-order.
void Game::stop() {
	collisionEngine_.stop();
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
		collisionEngine_.processCollisions();
		this->update(dt_);
		ioEngine_.swapBuffers();
	}

}


void Game::addEntity(std::shared_ptr<Entity> entity) {
	entities_.push_back(entity);
}
void Game::addSystem(System* system) {
	systems_.push_back(system);
}


void Game::update(const float dt) {
	for (auto& system : systems_) {
		for (auto& e : entities_) {
			system->validateAndExecute(e, dt);
		}
	}

	// System order defined by order added to game.

	// Update engines here.
}
