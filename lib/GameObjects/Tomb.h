#pragma once
#include "Unit.h"

namespace Engine {
	class Tomb : public Unit {
	public:
		Tomb(class Game* game);
		~Tomb();
		void UpdateActor(float deltaTime) override;
	};
}