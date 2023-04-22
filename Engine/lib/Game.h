#pragma once
#include <SDL.h>
#include <vector>
#include <SDL_image.h>
#include <ostream>
#include <unordered_map>
#include "CustomMath.h"

namespace Engine {

	class Game {
	public:
		Game();
		bool Start();
		void RunLoop();
		void End();

		enum Turn
		{
			NONE,
			PLAYER,
			ENEMY,
			SHOOT,
			END
		};

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* actor);

		void AddSprite(class SpriteComp* sprite);
		void RemoveSprite(class SpriteComp* sprite);

		void AddText(class TextComponent* sprite);
		void RemoveText(class TextComponent* sprite);

		SDL_Texture* GetTexture(const std::string& fileName);

		class Grid* GetGrid() { return m_Grid; }
		class UI* GetUI() { return m_UI; }
		class Player* GetAI() { return m_AI; }
		class Player* GetPlayer() { return m_Human; }

		std::vector<class Unit*>& GetUnits() { return m_Units; }
		std::vector<class Bullet*>& GetBullets() { return m_Bullets; }
		bool once, once2;

		float balance = 9;
		
	private:
		void GetInputs();
		void UpdateGame();
		void GetOutput();

		void LoadData();
		void UnloadData();

		void Finish();

		std::unordered_map<std::string, SDL_Texture*> m_Textures;

		SDL_Window* m_Window;
		SDL_Renderer* m_Render;
		bool m_Running;

		std::vector<class Actor*> m_Actors;
		std::vector<class Actor*> m_PendingActors;
		bool m_UpdatingActors;
		bool WaitForNext;
		float cooldown;

		std::vector<class SpriteComp*> m_Sprites;
		std::vector<class TextComponent*> m_Texts;

		Uint32 m_TicksCount;

		std::vector<class Unit*> m_Units;
		std::vector<class Bullet*> m_Bullets;

		class Grid* m_Grid;
		class UI* m_UI;
		class Selector* m_Select;
		class Dot* m_Dot;
		class TextPlate* m_HumanSpirit;
		class TextPlate* m_AISpirit;
		class TextPlate* m_Prices;
		class Player* m_Human;
		class Player* m_AI;
		
		Turn m_Turn;
	};
}