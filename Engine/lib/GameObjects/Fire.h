#pragma once
#include "Unit.h"

namespace Engine {
	class Fire : public Unit {
	public:
		Fire(class Game* game);
		~Fire();
		void UpdateActor(float deltaTime) override;
	};
}