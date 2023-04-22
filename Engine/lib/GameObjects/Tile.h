#pragma once
#include "Actor.h"

namespace Engine {
	class Tile : public Actor {
	public:
		friend class Grid;
		enum TileState {
			EDefault,
			EDefault2,
			EPath,
			EStart,
			EBase
		};

		Tile(class Game* game);

		void SetTileState(TileState state);
		TileState GetTileState() const { return m_TileState; }
		void setSelected();
		const Tile* GetParent() const { return m_Parent; }
		void setBlock(bool b) { m_Blocked = b; }

	private:
		std::vector<Tile*> m_Adjacent;
		Tile* m_Parent;
		float f; // G + H
		float g; //Dist to start Node
		float h; //Dist to final node
		bool m_InOpenSet;
		bool m_InClosedSet;
		bool m_Blocked;
		bool m_EnemBlocked;

		void UpdateTexture();
		class SpriteComp* m_Sprite;
		TileState m_TileState;
		bool m_Selected;
	};
}