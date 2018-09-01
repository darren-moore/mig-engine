#include "Game.h"
#include "Tank.h"
#include "Systems.h"
#include "Entity.h"

int main() {
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	Game pong(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	Locator::getResourceEngine()->addTexture("src/face.png", "face");
	Locator::getIOEngine()->bindInput("P1_UP", GLFW_KEY_W);
	Locator::getIOEngine()->bindInput("P1_DOWN", GLFW_KEY_S);
	Locator::getIOEngine()->bindInput("P2_UP", GLFW_KEY_UP);
	Locator::getIOEngine()->bindInput("P2_DOWN", GLFW_KEY_DOWN);

	Entity* p1 = new Entity();
	p1->applyComponent(new Sprite(Locator::getResourceEngine()->getTexture("face")));
	p1->applyComponent(new gTransform(Eigen::Vector2f(100,100)));
	p1->applyComponent(new Player("P1_UP", "P1_DOWN", .1f));
	pong.addEntity(p1);

	Entity* p2= new Entity();
	p2->applyComponent(new Sprite(Locator::getResourceEngine()->getTexture("face")));
	p2->applyComponent(new gTransform(Eigen::Vector2f(500, 100)));
	p2->applyComponent(new Player("P2_UP", "P2_DOWN", .1f));
	pong.addEntity(p2);

	pong.addSystem(new MovementSystem());
	pong.addSystem(new DrawSystem());

	// Run the game!
	pong.start();
}
