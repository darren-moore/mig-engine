#include "Game.h"
#include "Tank.h"
#include "Ball.h"
#include "Paddle.h"
#include "Systems.h"

int main() {
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	Game myGame(WINDOW_WIDTH, WINDOW_HEIGHT);

	Entity* go = new Entity();
	Locator::getResourceEngine()->addTexture("src/face.png", "face");
	Locator::getIOEngine()->bindInput("UP", GLFW_KEY_W);
	Locator::getIOEngine()->bindInput("DOWN", GLFW_KEY_S);
	Locator::getIOEngine()->bindInput("LEFT", GLFW_KEY_A);
	Locator::getIOEngine()->bindInput("RIGHT", GLFW_KEY_D);

	go->sprite = new Sprite(Locator::getResourceEngine()->getTexture("face"));
	go->transform = new gTransform(Eigen::Vector2f(100,100));
	go->player = new Player("UP", "DOWN", "LEFT", "RIGHT", .1);
	myGame.addEntity(go);

	myGame.addSystem(new MovementSystem());
	myGame.addSystem(new DrawSystem());

	//Tank* go = new Tank();
	//myGame.addGameObject(go);

	//Paddle* p1 = new Paddle(30, 90);
	//p1->transform.position = Eigen::Vector2f(50, 2 * WINDOW_HEIGHT / 3.0);
	//Locator::getIOEngine()->bindInput("Player 1 Up", GLFW_KEY_W);
	//Locator::getIOEngine()->bindInput("Player 1 Down", GLFW_KEY_S);
	//p1->paddleUp = "Player 1 Up";
	//p1->paddleDown = "Player 1 Down";
	//myGame.addGameObject(p1);

	//Paddle* p2 = new Paddle(30, 90);
	//p2->transform.position = Eigen::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT / 3.0);
	//Locator::getIOEngine()->bindInput("Player 2 Up", GLFW_KEY_UP);
	//Locator::getIOEngine()->bindInput("Player 2 Down", GLFW_KEY_DOWN);
	//p2->paddleUp = "Player 2 Up";
	//p2->paddleDown = "Player 2 Down";
	//myGame.addGameObject(p2);

	//Ball* ball = new Ball();
	//ball->transform.position = Eigen::Vector2f(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
	//ball->setVelocity(Eigen::Vector2f(125, 0));
	//myGame.addGameObject(ball);
	//ball->p1 = p1;
	//ball->p2 = p2;



	// Run the game!
	myGame.start();
}
