#pragma once
#include "Unit.h"

namespace Engine {
	class Crow : public Unit {
	public:
		Crow(class Game* game);
		~Crow();
		void UpdateActor(float deltaTime) override;
	};
}