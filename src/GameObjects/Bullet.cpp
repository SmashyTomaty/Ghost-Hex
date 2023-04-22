#include "Bullet.h"
#include "SpriteComp.h"
#include "MoveComponent.h"
#include "CircleColider.h"
#include "Game.h"
#include "Unit.h"

namespace Engine
{
	Bullet::Bullet(Game* game, float DMG, bool e) :
		Actor(game), m_DMG(DMG), isEnemy(e)
	{
		m_sc = new SpriteComp(this);
		m_sc->SetTexture(game->GetTexture("src/Assets/Projectile.png"));

		MoveComponent* mc = new MoveComponent(this);
		mc->setForwardSpeed(400.0f);

		m_Circle = new CircleColider(this);
		m_Circle->SetRadius(5);
	}

	Bullet::~Bullet()
	{
		auto iter = std::find(GetGame()->GetBullets().begin(),
			GetGame()->GetBullets().end(), this);
		GetGame()->GetBullets().erase(iter);
	}

	void Bullet::UpdateActor(float deltaTime)
	{
		Actor::UpdateActor(deltaTime);

		for (Unit* u : GetGame()->GetUnits())
		{
			if (CircleColider::Intersect(*m_Circle, *(u->GetCircle())))
			{
				if (!u->getFire() && u->getEnemy() != isEnemy){
					u->TakeDamage(m_DMG);
					SetState(EDead);
				}
				else if (u->getFire() && u->getEnemy() == isEnemy) {
					setFire();
				}
				break;
			}
		}

		if (GetPos().x > 1200) {
			++GetGame()->balance;
			SetState(EDead);
		} else if (GetPos().x < -100) {
			--GetGame()->balance;
			SetState(EDead);
		}
	}

	void Bullet::setFire()
	{
		m_sc->SetTexture(GetGame()->GetTexture("src/Assets/ProjectileStrong.png"));
		m_DMG *= 2;
	}
}