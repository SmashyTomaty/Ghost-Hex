#pragma once
#include "Actor.h"

namespace Engine {

	class Grid : public Actor 
	{
	public:
		Grid(class Game* game);
		~Grid();

		void CheckClick(int x, int y);

		enum buildType
		{
			EDef,
			ENeCrow,
			ECrow,
			EGhost,
			ETomb,
			EFire
		};

		void SetPath();
		void BuildUnit();
		void BuildAI(buildType bType, std::vector<Vector2> Opos, std::vector<Vector2> Epos, 
			class Player* p, bool recursive);
		void UpdateActor(float deltaTime) override;

		void addEnemyToList(class Player* p);
		void removeEnemyList(class Player* p, class Unit* u);
		void removeOwnList(class Player* p, class Unit* u);
		void SetPlayer(Player* p) { m_Player = p; }

		void SetBType(buildType bType) { m_buildType = bType; }
		buildType getBType() { return m_buildType; }
		float getGridPrice() { return m_PayPrice; }
		void setGridPrice(float a) { m_PayPrice = a; }

		bool allow = true;

	private:
		void SelectTile(size_t row, size_t col);
		class Tile* m_SelectedTile;
		class Player* m_Player;

		std::vector<std::vector<class Tile*>> m_Tiles;
		Vector2 m_LastSelectPosition;

		float m_NextEnemy;
		float m_PayPrice;
		const size_t nRow = 5;
		const size_t nCols = 9;
		const float StartY = 100;
		const float tileSize = 128;
		const float enemTime = 1.5f;
		buildType m_buildType;
	};
}