#include "Crow.h"
#include "MoveComponent.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Bullet.h"

namespace Engine {

	Crow::Crow(Game* game) : Unit(game)
	{

		std::vector<SDL_Texture*> anims = {
			game->GetTexture("src/Assets/Crow.png"),
			game->GetTexture("src/Assets/Crow1.png"),
			game->GetTexture("src/Assets/Crow.png"),
			game->GetTexture("src/Assets/Crow2.png")
		};

		GetSprite()->SetAnimTextures(anims);

		setCrow();

		setStats(1, 1, 300, 0);
	}

	Crow::~Crow()
	{

	}

	void Crow::UpdateActor(float deltaTime)
	{
		Unit::UpdateActor(deltaTime);
	}
}