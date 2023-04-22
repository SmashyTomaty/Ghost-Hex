#include "NCrow.h"
#include "MoveComponent.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Bullet.h"

namespace Engine {

	NCrow::NCrow(Game* game) : Unit(game)
	{

		std::vector<SDL_Texture*> anims = {
			game->GetTexture("src/Assets/Necrow.png"),
			game->GetTexture("src/Assets/Necrow1.png"),
			game->GetTexture("src/Assets/Necrow.png"),
			game->GetTexture("src/Assets/Necrow2.png")
		};

		GetSprite()->SetAnimTextures(anims);

		setStats(0, 1, 50, 50);
	}

	NCrow::~NCrow()
	{

	}

	void NCrow::UpdateActor(float deltaTime)
	{
		Unit::UpdateActor(deltaTime);
	}
}