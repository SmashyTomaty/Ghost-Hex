#pragma once
#include "Actor.h"
#include <string>

namespace Engine {
	class UI : public Actor {
	public:
		UI(class Game* game);
		~UI();
		void UpdateActor(float deltaTime) override;
	};

	class Selector : public Actor {
	public:
		Selector(class Game* game);
		~Selector();
		void UpdateActor(float deltaTime) override;
	};

	class Dot : public Actor {
	public:
		Dot(class Game* game);
		~Dot();
		void UpdateActor(float deltaTime) override;
	};

	class TextPlate : public Actor {
	public:
		TextPlate(class Game* game);
		~TextPlate();
		void UpdateActor(float deltaTime) override;
		void UpdateText(std::string s);

		void IncreaseWidth(int e);

	private:
		class TextComponent* tc;
	};
}