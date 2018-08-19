#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IOEngine.h"
#include "RenderEngine.h"
#include "Locator.h"
#include "GameObject.h"
#include <vector>

class Game {

public:
	Game(GLuint windowWidth, GLuint windowHeight);
	~Game() {}
	void stop();
	void start();
	void update(float const dt);
	void render();
	void addGameObject(GameObject *gameObject);
	float getDt() { return dt; }

private:
	std::vector<GameObject*> gameObjects;
	RenderEngine renderEngine;
	IOEngine ioEngine;
	float dt = 0;
};
