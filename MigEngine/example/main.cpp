#include "Game.h"
#include "Systems.h"
#include "Entity.h"

int main() {
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	Game danmaku(WINDOW_WIDTH, WINDOW_HEIGHT);

	CollisionEngine& ce = Locator::getCollisionEngine();
	Locator::getResourceEngine().addTexture("example/face.png", "face");	// I drew this at some point.
	Locator::getResourceEngine().addSound("example/koto.mp3", "koto");		// I was learning to play koto.
	Locator::getIOEngine().bindInput("UP", GLFW_KEY_UP);
	Locator::getIOEngine().bindInput("DOWN", GLFW_KEY_DOWN);
	Locator::getIOEngine().bindInput("LEFT", GLFW_KEY_LEFT);
	Locator::getIOEngine().bindInput("RIGHT", GLFW_KEY_RIGHT);
	Locator::getIOEngine().bindInput("SHOOT", GLFW_KEY_X);

	{
		Entity* player = new Entity();
		player->applyComponent(new Quad(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 30)));
		player->applyComponent(new Sprite(Locator::getResourceEngine().getTexture("face"), Eigen::Vector2f(0, 0)));
		player->applyComponent(new gTransform(Eigen::Vector2f(50, 400)));
		player->applyComponent(new Player("UP", "DOWN", "LEFT", "RIGHT", "SHOOT", .5f));
		player->applyComponent(new CollisionShape(new Box(Eigen::Vector2f(0, 0), Eigen::Vector2f(30, 100))));
		ce.addCollisionEntity(player);
		danmaku.addEntity(player);
	}

	{
		Entity* ball = new Entity();
		ball->applyComponent(new Circ(Eigen::Vector2f(0, 0), 20));
		ball->applyComponent(new gTransform(Eigen::Vector2f(400, 300)));
		ball->applyComponent(new CollisionShape(new Circle(Eigen::Vector2f(0, 0), 20)));
		ball->applyComponent(new Velocity(Eigen::Vector2f(200, 0)));
		ce.addCollisionEntity(ball);
		danmaku.addEntity(ball);
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
		ce.addCollisionEntity(wall1);
		ce.addCollisionEntity(wall2);
		ce.addCollisionEntity(wall3);
		ce.addCollisionEntity(wall4);
		danmaku.addEntity(wall1);
		danmaku.addEntity(wall2);
		danmaku.addEntity(wall3);
		danmaku.addEntity(wall4);
	}

	danmaku.addSystem(new MovementSystem());
	danmaku.addSystem(new SpriteRenderSystem());
	danmaku.addSystem(new TimeIntegrationSystem());
	danmaku.addSystem(new QuadRenderSystem());
	danmaku.addSystem(new CircleRenderSystem());
	danmaku.addSystem(new BallCollisionResolutionSystem());

	Locator::getAudioEngine().playSound(Locator::getResourceEngine().getSound("koto"), true);

	// Run the game!
	danmaku.start();
}
