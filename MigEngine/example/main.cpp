#include "Game.h"
#include "Tank.h"
#include "Systems.h"
#include "Entity.h"

int main() {
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	Game myGame(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	Locator::getResourceEngine()->addTexture("src/face.png", "face");
	Locator::getIOEngine()->bindInput("UP", GLFW_KEY_W);
	Locator::getIOEngine()->bindInput("DOWN", GLFW_KEY_S);
	Locator::getIOEngine()->bindInput("LEFT", GLFW_KEY_A);
	Locator::getIOEngine()->bindInput("RIGHT", GLFW_KEY_D);

	Entity* e = new Entity();
	e->addComponent(new Sprite(Locator::getResourceEngine()->getTexture("face")));
	e->addComponent(new gTransform(Eigen::Vector2f(100,100)));
	e->addComponent(new Player("UP", "DOWN", "LEFT", "RIGHT", .1f));
	myGame.addEntity(e);

	myGame.addSystem(new MovementSystem());
	myGame.addSystem(new DrawSystem());

	// Run the game!
	myGame.start();
}
