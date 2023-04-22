#include "Ghost.h"
#include "MoveComponent.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Bullet.h"

namespace Engine {

	Ghost::Ghost(Game* game) : Unit(game)
	{

		std::vector<SDL_Texture*> anims = {
			game->GetTexture("src/Assets/Ghost.png"),
			game->GetTexture("src/Assets/Ghost1.png"),
			game->GetTexture("src/Assets/Ghost.png"),
			game->GetTexture("src/Assets/Ghost2.png")
		};

		GetSprite()->SetAnimTextures(anims);

		setStats(1, 2, 100, 0);
	}

	Ghost::~Ghost()
	{

	}

	void Ghost::UpdateActor(float deltaTime)
	{
		Unit::UpdateActor(deltaTime);
	}
}