#include "Game.h"

// BaseIOEngine is the only one that touches GLFW stuff. It could be swapped with SDL for instance.
// WindowEngine gets 
// PhysicsEngine includes rigid body, soft body, and fluid computations.
// ParticleEngine
// TextEngine
// AudioEngine
// GUI Engine

Game::Game(GLuint windowWidth, GLuint windowHeight) {
	ioEngine.init();
	Locator::provide(ioEngine);

	renderEngine.init();
	Locator::provide(renderEngine);
}

// Shutdown sub-engines in inverse start-order.
void Game::stop() {
	renderEngine.stop();
	ioEngine.stop();
}

void Game::start() {
	float lastFrameTime = 0;

	while (true) {
		if (ioEngine.shouldClose()) {
			stop();
			break;
		}

		float currentFrameTime = ioEngine.getCurrentWindowTime();
		dt = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		ioEngine.processInput();
		this->update(dt);
		this->render();
		ioEngine.swapBuffers();
	}

}


void Game::addGameObject(GameObject *gameObject) {
	gameObjects.push_back(gameObject);
}

void Game::update(float const dt) {
	for (auto &go : gameObjects) {
		if (go->active) {
			go->update(dt);
		}
	}

	// Update other engines here.
}

void Game::render() {
	for (auto &go : gameObjects) {
		if (go->spriteRenderer != NULL) {
			go->spriteRenderer->draw(glm::vec2(100,100), glm::vec2(100,100), 0);
		}
	}
}
