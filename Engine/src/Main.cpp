#include <iostream>
#include <Game.h>

int main(int argc, char** argv)
{
	Engine::Game game;
	bool success = game.Start();

	if (success) {
		game.RunLoop();
	}

	return 0;
}