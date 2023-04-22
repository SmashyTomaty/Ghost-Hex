#pragma once
#include "Unit.h"

namespace Engine {
	class NCrow : public Unit {
	public:
		NCrow(class Game* game);
		~NCrow();
		void UpdateActor(float deltaTime) override;
	};
}