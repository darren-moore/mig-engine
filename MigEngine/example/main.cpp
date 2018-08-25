#include "Game.h"
#include "Tank.h"
#include "Ball.h"

int main() {
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	Game myGame(WINDOW_WIDTH, WINDOW_HEIGHT);

	Tank* go = new Tank();
	myGame.addGameObject(go);

	Ball* ball = new Ball();
	ball->setVelocity(Eigen::Vector2f(10,20));
	myGame.addGameObject(ball);

	// Run the game!
	myGame.start();
}
