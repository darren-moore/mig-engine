#include "Game.h"
#include "Tank.h"

int main() {
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	Game myGame(WINDOW_WIDTH, WINDOW_HEIGHT);

	GameObject* go = new Tank();
	myGame.addGameObject(go);

	// Run the game!
	myGame.start();
}
