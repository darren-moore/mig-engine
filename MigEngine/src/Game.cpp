#include "Game.h"

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
		this->update(dt_);
		renderEngine_.clear();
		this->render();
		ioEngine_.swapBuffers();
	}

}


void Game::addGameObject(GameObject *gameObject) {
	gameObjects_.push_back(gameObject);
}

void Game::update(float const dt) {
	for (auto &go : gameObjects_) {
		if (go->active) {
			go->update(dt);
		}
	}

	// Update other engines here.
}

void Game::render() {
	for (auto &go : gameObjects_) {
		if (go->texture != NULL) {
			renderEngine_.drawTexture(go->texture, go->transform.position, Eigen::Vector2f(100, 100), 3.14 / 4);
		}
	}
}
