#include "Game.h"
#include "Systems.h"
#include "Entity.h"

int main() {
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	Game pong(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	CollisionEngine* ce = Locator::getCollisionEngine();
	Locator::getResourceEngine()->addTexture("example/face.png", "face");
	Locator::getResourceEngine()->addSound("example/koto.mp3", "koto");
	Locator::getIOEngine()->bindInput("P1_UP", GLFW_KEY_W);
	Locator::getIOEngine()->bindInput("P1_DOWN", GLFW_KEY_S);
	Locator::getIOEngine()->bindInput("P2_UP", GLFW_KEY_UP);
	Locator::getIOEngine()->bindInput("P2_DOWN", GLFW_KEY_DOWN);

	{
		Entity* p1 = new Entity();
		p1->applyComponent(new Quad(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100)));
		p1->applyComponent(new gTransform(Eigen::Vector2f(50, 400)));
		p1->applyComponent(new Player("P1_UP", "P1_DOWN", .5f));
		p1->applyComponent(new CollisionShape(new Box(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100))));
		ce->addCollisionEntity(p1);
		pong.addEntity(p1);

		Entity* p2 = new Entity();
		p2->applyComponent(new Quad(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100)));
		p2->applyComponent(new gTransform(Eigen::Vector2f(750, 400)));
		p2->applyComponent(new Player("P2_UP", "P2_DOWN", .5f));
		p2->applyComponent(new CollisionShape(new Box(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100))));
		ce->addCollisionEntity(p2);
		pong.addEntity(p2);
	}

	{
		Entity* ball = new Entity();
		ball->applyComponent(new Circ(Eigen::Vector2f(0, 0), 20));
		ball->applyComponent(new gTransform(Eigen::Vector2f(400, 300)));
		ball->applyComponent(new CollisionShape(new Circle(Eigen::Vector2f(0, 0), 20)));
		ball->applyComponent(new Velocity(Eigen::Vector2f(200, 0)));
		ce->addCollisionEntity(ball);
		pong.addEntity(ball);
	}

	{
		Entity* wall1 = new Entity();
		Entity* wall2 = new Entity();
		Entity* wall3 = new Entity();
		Entity* wall4 = new Entity();
		wall1->applyComponent(new gTransform(Eigen::Vector2f(0, 0)));
		wall2->applyComponent(new gTransform(Eigen::Vector2f(0, 0)));
		wall3->applyComponent(new gTransform(Eigen::Vector2f(0, 0)));
		wall4->applyComponent(new gTransform(Eigen::Vector2f(0, 0)));
		wall1->applyComponent(new CollisionShape(new Line(Eigen::Vector2f(0, 0), Eigen::Vector2f(WINDOW_WIDTH, 0))));
		wall2->applyComponent(new CollisionShape(new Line(Eigen::Vector2f(0, 0), Eigen::Vector2f(0, WINDOW_HEIGHT))));
		wall3->applyComponent(new CollisionShape(new Line(Eigen::Vector2f(0, WINDOW_HEIGHT), Eigen::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))));
		wall4->applyComponent(new CollisionShape(new Line(Eigen::Vector2f(WINDOW_WIDTH, 0), Eigen::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))));
		ce->addCollisionEntity(wall1);
		ce->addCollisionEntity(wall2);
		ce->addCollisionEntity(wall3);
		ce->addCollisionEntity(wall4);
		pong.addEntity(wall1);
		pong.addEntity(wall2);
		pong.addEntity(wall3);
		pong.addEntity(wall4);
	}

	pong.addSystem(new MovementSystem());
	pong.addSystem(new SpriteRenderSystem());
	pong.addSystem(new TimeIntegrationSystem());
	pong.addSystem(new QuadRenderSystem());
	pong.addSystem(new CircleRenderSystem());
	pong.addSystem(new BallCollisionResolutionSystem());

	Locator::getAudioEngine()->playSound(Locator::getResourceEngine()->getSound("koto"), true);

	// Run the game!
	pong.start();
}
