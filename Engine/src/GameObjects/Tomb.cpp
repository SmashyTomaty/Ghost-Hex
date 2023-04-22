#include "Tomb.h"
#include "MoveComponent.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Bullet.h"

namespace Engine {

	Tomb::Tomb(Game* game) : Unit(game)
	{
		std::vector<SDL_Texture*> anims = {
			game->GetTexture("src/Assets/Tomb.png")
		};

		GetSprite()->SetAnimTextures(anims);

		setStats(0, 5, 300, 0);
	}

	Tomb::~Tomb()
	{

	}

	void Tomb::UpdateActor(float deltaTime)
	{
		Unit::UpdateActor(deltaTime);
	}
}