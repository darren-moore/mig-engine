#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IOEngine.h"
#include "RenderEngine.h"
#include "ResourceEngine.h"

#include "Locator.h"
#include "GameObject.h"
#include <vector>

class Game {

public:
	Game(GLuint windowWidth = 800, GLuint windowHeight = 600);
	~Game() {}
	void stop();
	void start();
	void update(float const dt);
	void render();
	void addGameObject(GameObject *gameObject);
	float getDt() { return dt_; }

private:
	std::vector<GameObject*> gameObjects_;
	RenderEngine renderEngine_;
	IOEngine ioEngine_;
	ResourceEngine resourceEngine_;
	float dt_ = 0;
};
