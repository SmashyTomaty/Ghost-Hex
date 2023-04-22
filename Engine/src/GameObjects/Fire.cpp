#include "Fire.h"
#include "MoveComponent.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Bullet.h"

namespace Engine {

	Fire::Fire(Game* game) : Unit(game)
	{

		std::vector<SDL_Texture*> anims = {
			game->GetTexture("src/Assets/Fire.png"),
			game->GetTexture("src/Assets/Fire2.png"),
			game->GetTexture("src/Assets/Fire1.png"),
			game->GetTexture("src/Assets/Fire3.png"),
			game->GetTexture("src/Assets/Fire2.png"),
			game->GetTexture("src/Assets/Fire.png"),
			game->GetTexture("src/Assets/Fire1.png")
		};

		GetSprite()->SetAnimTextures(anims);
		GetSprite()->SetAnimFPS(12);

		setFire();

		setStats(0, 1, 400, 10);
	}

	Fire::~Fire()
	{

	}

	void Fire::UpdateActor(float deltaTime)
	{
		Unit::UpdateActor(deltaTime);
	}
}