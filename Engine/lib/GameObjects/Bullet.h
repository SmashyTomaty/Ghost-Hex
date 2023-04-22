#pragma once
#include "Actor.h"

namespace Engine {
	class Bullet : public Actor {
	public:
		Bullet(class Game* game, float DMG, bool e);
		~Bullet();
		void UpdateActor(float deltaTime) override;
		class CircleColider* GetCircle() { return m_Circle; }
		void setFire();

	private:
		class CircleColider* m_Circle;
		class SpriteComp* m_sc;
		bool isEnemy;
		float m_DMG;
	};
}
