#pragma once
#include "Actor.h"
#include <string>

namespace Engine {
	class Unit : public Actor {
	public:
		Unit(class Game* game);
		~Unit();
		void UpdateActor(float deltaTime) override;

		class CircleColider* GetCircle() { return m_Circle; }
		class AnimSpriteComponent* GetSprite() { return m_Asc; }

		class Tile* getTile() { return m_Tile; }
		void SetTile(class Tile* t) { m_Tile = t; }
		void setStats(float DMG, float HP, float Price, float Profit);
		float getPrice() { return unitPrice; }
		bool getEnemy() { return isEnemy; }
		void setEnemy();
		bool getFire() { return isFire; }
		bool getNCrow() { return isNCrow; }
		void setFire() { isFire = true; }
		void setCrow() { isCrow = true; }
		void setNCrow() { isNCrow = true; }
		float getDamage() { return AttackDMG; }

		void TakeDamage(float DMG);
		float DoTurn(bool enemy);

	private:
		class MoveComponent* m_Move;
		class AnimSpriteComponent* m_Asc;
		class Tile* m_Tile;
		float AttackDMG;
		float unitHP;
		float unitPrice;
		float unitProfits;
		bool isEnemy;
		bool isFire;
		bool isCrow;
		bool isNCrow;
		class CircleColider* m_Circle;
	};
}