#include "Game.h"
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
	p1->applyComponent(new Quad(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100)));
	p1->applyComponent(new gTransform(Eigen::Vector2f(100,400)));
	p1->applyComponent(new Player("P1_UP", "P1_DOWN", .5f));
	p1->applyComponent(new BoxCollider(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100)));
	pong.addEntity(p1);

	Entity* p2= new Entity();
	p2->applyComponent(new Quad(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100)));
	p2->applyComponent(new gTransform(Eigen::Vector2f(500, 400)));
	p2->applyComponent(new Player("P2_UP", "P2_DOWN", .5f));
	p2->applyComponent(new BoxCollider(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100)));
	pong.addEntity(p2);

	Entity* ball = new Entity();
	ball->applyComponent(new Sprite(Locator::getResourceEngine()->getTexture("face")));
	ball->applyComponent(new gTransform(Eigen::Vector2f(400, 300)));
	ball->applyComponent(new CircleCollider(Eigen::Vector2f(0, 0), 50));
	ball->applyComponent(new Velocity(Eigen::Vector2f(100, 0)));
	pong.addEntity(ball);

	pong.addSystem(new MovementSystem());
	pong.addSystem(new SpriteRenderSystem());
	pong.addSystem(new TimeIntegrationSystem());
	pong.addSystem(new QuadRenderSystem());

	// Run the game!
	pong.start();
}
