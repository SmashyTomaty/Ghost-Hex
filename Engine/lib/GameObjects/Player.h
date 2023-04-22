#pragma once
#include "Actor.h"
#include "Grid.h"

namespace Engine {
	class Player : public Actor {
	public:
		Player(class Game* game);
		~Player();
		void UpdateActor(float deltaTime) override;

		bool isTurn() { return m_isTurn; }
		int GetSpirit() { return m_SpiritCount; }
		void AddSpirit(float add) { m_SpiritCount += add; }
		void addEnemPos(Vector2 v, Grid::buildType b);
		void removeEnemPos(Vector2 v);
		void addOwnPos(Vector2 v, Grid::buildType b);
		void removeOwnPos(Vector2 v);
		void RemoveNCrowFromBCount();
		Grid::buildType whatBuild();
		//Vector2 whereBuild(Grid::buildType b);

		std::vector<Vector2> getEPos() { return EnemPos; }
		std::vector<Vector2> getOPos() { return OwnPos; }

		int getNCrows() { return m_Necrows; }
	private:
		bool m_isTurn;
		int m_SpiritCount;
		int m_Necrows;
		std::vector<Vector2> EnemPos;
		std::vector<Vector2> OwnPos;
		std::vector<Grid::buildType> build;
	};
}