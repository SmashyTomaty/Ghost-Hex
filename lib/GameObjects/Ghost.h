#pragma once
#include "Unit.h"

namespace Engine {
	class Ghost : public Unit {
	public:
		Ghost(class Game* game);
		~Ghost();
		void UpdateActor(float deltaTime) override;
	};
}