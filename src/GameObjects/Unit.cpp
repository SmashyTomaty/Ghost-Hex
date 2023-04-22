#include "Game.h"
#include "Unit.h"
#include "Tile.h"
#include "MoveComponent.h"
#include "AnimSpriteComponent.h"
#include "CircleColider.h"
#include "Bullet.h"
#include "Player.h"

namespace Engine {

	Unit::Unit(Game* game) : Actor(game)
	{
		game->GetUnits().emplace_back(this);

		m_Asc = new AnimSpriteComponent(this);
		m_Asc->SetAnimFPS(6);

		m_Move = new MoveComponent(this);

		m_Circle = new CircleColider(this);
	}

	Unit::~Unit()
	{
		auto iter = std::find(GetGame()->GetUnits().begin(),
			GetGame()->GetUnits().end(), this);
		GetGame()->GetUnits().erase(iter);
	}

	void Unit::UpdateActor(float deltaTime)
	{
		Actor::UpdateActor(deltaTime);

		if (GetPos().x != 0) {
			if (GetPos().x > 557) {
				m_Asc->flip();
				isEnemy = true;
			}
			else {
				isEnemy = false;
			}
		}
	}

	void Unit::setStats(float DMG, float HP, float Price, float Profit) {
		AttackDMG = DMG;
		unitHP = HP;
		unitPrice = Price;
		unitProfits = Profit;
	}

	void Unit::setEnemy() {
		isEnemy = true;
	}

	void Unit::TakeDamage(float DMG) {
		unitHP -= DMG;

		if (unitHP <= 0) {
			getTile()->setBlock(false);
			GetGame()->GetGrid()->removeOwnList(GetGame()->GetAI(), this);
			GetGame()->GetGrid()->removeEnemyList(GetGame()->GetAI(), this);
			SetState(EDead);
		}

	}

	float Unit::DoTurn(bool enemy)
	{
		if (AttackDMG > 0 && !enemy) {
			Bullet* b = new Bullet(GetGame(), AttackDMG, isEnemy);
			GetGame()->GetBullets().emplace_back(b);
			b->SetPos(GetPos());

			if (isCrow) {

				//Find nerest Non-Enemy
				std::vector<class Unit*> m_Units;

				m_Units = GetGame()->GetUnits();
				Unit* temp = nullptr;
				if (m_Units.size() > 0) {

					float bestDist = 10000000;
					for (size_t e = 0; e < m_Units.size(); ++e)
					{
						if (m_Units[e] != this) {
							float newDist = (GetPos() - m_Units[e]->GetPos()).LengthSq();
							if (newDist < bestDist && m_Units[e]->getEnemy() != isEnemy && !isFire)
							{
								bestDist = newDist;
								temp = m_Units[e];
							}
						}
					}

				}

				if (temp != nullptr)
				{
					Vector2 dir = temp->GetPos() - GetPos();
					b->SetRota(CustomMath::Atan2(-dir.y, dir.x));
				} else {
					b->SetRota(-3.1416);
				}

				return 0;
			} 
			
			if (isEnemy) {
				b->SetRota(-3.1416);
			}
		}

		if (unitProfits != 0 && !enemy) {
			if (isEnemy) {
				return 0;
			}
			else {
				return unitProfits;
			}
		}
		else if (unitProfits != 0 && enemy) {
			if (!isEnemy) {
				return 0;
			}
			else {
				return unitProfits;
			}
		}
		else {
			return 0;
		}
	}
}