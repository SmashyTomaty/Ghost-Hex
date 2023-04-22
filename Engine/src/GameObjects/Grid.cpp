#include "Grid.h"
#include "Tile.h"
#include "NCrow.h"
#include "Crow.h"
#include "Ghost.h"
#include "Tomb.h"
#include "Fire.h"
#include "Player.h"
#include <algorithm>

namespace Engine {
	Grid::Grid(Game* game) : Actor(game), m_SelectedTile(nullptr)
	{
		m_Tiles.resize(nRow);
		for (size_t e = 0; e < m_Tiles.size(); ++e) 
		{
			m_Tiles[e].resize(nCols);
		}

		for (size_t e = 0; e < nRow; ++e) {

			for (size_t j = 0; j < nCols; ++j) {
				m_Tiles[e][j] = new Tile(GetGame());
				m_Tiles[e][j]->SetPos(Vector2(tileSize / 2.0f + j * tileSize, 
								StartY + e * tileSize));
			}
		}

		for (size_t e = 0; e < nRow; ++e) {

			for (size_t j = 0; j < nCols; ++j) {
				if (e > 0) {
					m_Tiles[e][j]->m_Adjacent.push_back(m_Tiles[e - 1][j]);
				}
				if (e < nRow - 1) {
					m_Tiles[e][j]->m_Adjacent.push_back(m_Tiles[e + 1][j]);
				}
				if (j > 0) {
					m_Tiles[e][j]->m_Adjacent.push_back(m_Tiles[e][j - 1]);
				}
				if (j < nCols - 1) {
					m_Tiles[e][j]->m_Adjacent.push_back(m_Tiles[e][j + 1]);
				}
			}
		}

		SetPath();

		m_NextEnemy = enemTime;
	}

	Grid::~Grid()
	{

	}

	void Grid::CheckClick(int x, int y)
	{
		y -= static_cast<int>(StartY - tileSize / 2);
		if (y >= 0) {
			x /= static_cast<int>(tileSize);
			y /= static_cast<int>(tileSize);
			if (x >= 0 && x < static_cast<int>(nCols) &&
				y >= 0 && y < static_cast<int>(nRow)) {
				SelectTile(y, x);
			}
		}
	}

	void Grid::SetPath()
	{
		for (size_t e = 0; e < nRow; ++e)
		{
			for (size_t j = 0; j < nCols; ++j)
			{
				if (j == 4) {
					m_Tiles[e][j]->SetTileState(Tile::EPath);
					m_Tiles[e][j]->m_Blocked = true;
				}
				else if (j > 4) {
					m_Tiles[e][j]->m_Blocked = true;
				}

				if (j == 1 || j == 3 || j == 5 || j == 7) {
					m_Tiles[e][j]->SetTileState(Tile::EDefault2);
				}

			}
		}
	}

	void Grid::BuildUnit()
	{
		if (m_SelectedTile && !m_SelectedTile->m_Blocked && m_buildType != NULL)
		{
			m_SelectedTile->m_Blocked = true;
		    switch (m_buildType)
			{
			 case ENeCrow: {
				NCrow* u = new NCrow(GetGame());
				u->SetPos(m_SelectedTile->GetPos());
				u->SetTile(m_SelectedTile);
				m_Player->AddSpirit(u->getPrice() * -1);
				break;
			 }
			 case ECrow: {
				Crow* u = new Crow(GetGame());
				u->SetPos(m_SelectedTile->GetPos());
				u->SetTile(m_SelectedTile);
				m_Player->AddSpirit(u->getPrice() * -1);
				break;
			 }
		 	 case EGhost: {
				Ghost* u = new Ghost(GetGame());
				u->SetPos(m_SelectedTile->GetPos());
				u->SetTile(m_SelectedTile);
				m_Player->AddSpirit(u->getPrice() * -1);
				break;
			 }
			 case ETomb: {
				Tomb* u = new Tomb(GetGame());
				u->SetPos(m_SelectedTile->GetPos());
				u->SetTile(m_SelectedTile);
				m_Player->AddSpirit(u->getPrice() * -1);
				break;
			 }
			 case EFire: {
				Fire* u = new Fire(GetGame());
				u->SetPos(m_SelectedTile->GetPos());
				u->SetTile(m_SelectedTile);
				m_Player->AddSpirit(u->getPrice() * -1);
				break;
			 }
			}
		}
	}

	void Grid::UpdateActor(float deltaTime)
	{
		Actor::UpdateActor(deltaTime);

		//Enemy Updater
	}

	void Grid::addEnemyToList(Player* p)
	{
		p->addEnemPos(m_LastSelectPosition, m_buildType);
	}

	void Grid::removeEnemyList(Player* p, class Unit* u)
	{
		Vector2 temp = u->GetPos();
		temp.y -= static_cast<int>(StartY - tileSize / 2);
		if (temp.y >= 0) {
			temp.x /= static_cast<int>(tileSize);
			temp.y /= static_cast<int>(tileSize);
			if (temp.x >= 0 && temp.x < static_cast<int>(nCols) &&
				temp.y >= 0 && temp.y < static_cast<int>(nRow)) {
				p->removeEnemPos(Vector2(temp.x - 0.5f, temp.y -0.5f));
			}
		}
	}

	void Grid::removeOwnList(Player* p, class Unit* u)
	{
		Vector2 temp = u->GetPos();
		temp.y -= static_cast<int>(StartY - tileSize / 2);
		if (temp.y >= 0) {
			temp.x /= static_cast<int>(tileSize);
			temp.y /= static_cast<int>(tileSize);
			if (temp.x >= 0 && temp.x < static_cast<int>(nCols) &&
				temp.y >= 0 && temp.y < static_cast<int>(nRow)) {
				p->removeOwnPos(Vector2(temp.x - 0.5f, temp.y -0.5f));
				if (u->getNCrow()) {
					p->RemoveNCrowFromBCount();
				}
			}
		}

	}

	void Grid::SelectTile(size_t row, size_t col)
	{
		Tile::TileState tState = m_Tiles[row][col]->GetTileState();
		if (tState != Tile::EPath && col < 4) {
			if (m_SelectedTile) {
				m_SelectedTile->setSelected();
			}
			m_SelectedTile = m_Tiles[row][col];
			m_LastSelectPosition.x = row;
			m_LastSelectPosition.y = col;
			m_SelectedTile->setSelected();

			allow = true;
		}
	}

	void Grid::BuildAI(buildType bType, std::vector<Vector2> Opos, std::vector<Vector2> Epos, Player* p, bool recursive)
	{

		if (bType == Grid::EDef || Opos.size() >= 20) {
			return;
		}

		Tile* WhereBuild = nullptr;
		Vector2 Selection;
		/*while (WhereBuild == nullptr) {
			size_t v2 = rand() % 4 + 5;
			size_t v1 = rand() % 5;
			WhereBuild = m_Tiles[v1][v2];
			Selection = Vector2(v1, v2);

			for (int e = 0; e < Opos.size(); ++e) {
				if (Opos[e].x == v1 && Opos[e].y == v2) {
					WhereBuild = nullptr;
				}
			}
		}*/

		int maxAttempts = 0;
		int maxChecks;
		std::vector<Vector2> tested;

		switch (bType)
		{
		case ENeCrow: {
			NCrow* u = new NCrow(GetGame());

			while (WhereBuild == nullptr) {
				size_t v2;
				size_t v1;
				if (maxAttempts <= 4) {
					v2 = 8;
					v1 = rand() % 5;
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else if (maxAttempts <= 8) {
						v2 = 7;
						v1 = rand() % 5;
						WhereBuild = m_Tiles[v1][v2];
						Selection = Vector2(v1, v2);
				} 
				else {
					if (p->GetSpirit() >= 300) {
						int v3 = rand() % 8;
						if (v3 <= 3) {
							BuildAI(Grid::ETomb, Opos, Epos, p, false);
							return;
						}
						else if(v3 <= 6) {
							BuildAI(Grid::ECrow, Opos, Epos, p, false);
							return;
						}
						else {
							BuildAI(Grid::EGhost, Opos, Epos, p, true);
							return;
						}
					}
					else if (p->GetSpirit() >= 100) {
						BuildAI(Grid::EGhost, Opos, Epos, p, true);
						return;
					}
					else {
						BuildAI(Grid::EDef, Opos, Epos, p, false);
					}
				}

				for (int e = 0; e < Opos.size(); ++e) {
					if (Opos[e].x == v1 && Opos[e].y == v2) {
						WhereBuild = nullptr;
						for (int j = 0; j < tested.size(); ++e) {
							if (tested[e].x != v1 && tested[e].y != v2) {
								tested.push_back(Vector2(v1, v2));
								++maxAttempts;
							}
						}
					}
				}
			}

			u->SetPos(WhereBuild->GetPos());
			u->SetTile(WhereBuild);
			p->addOwnPos(Selection, bType);
			p->AddSpirit(u->getPrice() * -1);

			if (p->getNCrows() < 4) {
				int rep = p->GetSpirit() / 50;
				for (int e = 0; e < rep; ++e) {
					BuildAI(Grid::ENeCrow, Opos, Epos, p, true);
				}
			}

			break;
		}
		case ECrow: {

			while (WhereBuild == nullptr) {
				size_t v2;
				size_t v1;
				if (maxAttempts <= 10) {
					v2 = rand() % 1 + 6;
					v1 = rand() % 5;
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else {
					if (p->GetSpirit() >= 400) {
						BuildAI(Grid::EFire, Opos, Epos, p, false);
						return;
					}
					else {
						v1 = rand() % 2 + 1;
						if (v1 == 3) {
							BuildAI(Grid::ETomb, Opos, Epos, p, true);
							return;
						}
					}
				}

				for (int e = 0; e < Opos.size(); ++e) {
					if (Opos[e].x == v1 && Opos[e].y == v2) {
						WhereBuild = nullptr;
						for (int j = 0; j < tested.size(); ++e) {
							if (tested[e].x != v1 && tested[e].y != v2) {
								tested.push_back(Vector2(v1, v2));
								++maxAttempts;
							}
						}
					}
				}
			}

			Crow* u = new Crow(GetGame());
			u->SetPos(WhereBuild->GetPos());
			u->SetTile(WhereBuild);
			p->addOwnPos(Selection, bType);
			p->AddSpirit(u->getPrice() * -1);
			break;
		}
		case EGhost: {

			while (WhereBuild == nullptr) {
				size_t v2;
				size_t v1;

				int Col[5] = { 0,0,0,0,0 };

				int highestCol = 0;
				int bestCol = 0;

				if (maxAttempts < 1) {
					for (int e = 0; e < 5; ++e) {
						for (int j = 0; j < Epos.size(); ++j) {
							if (Epos[j].x == e) {
								++Col[e];
							}
						}
					} 
					for (int j = 0; j < 5; ++j) {
						if (highestCol < Col[j]) {
							highestCol = Col[j];
							bestCol = j + 1;
						}
					}

					if (highestCol == 0 || highestCol == 1 || highestCol == 2) {
						v1 = rand() % 5;
					}
					else {
						v1 = bestCol;
					}
					v2 = 7;
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else if (maxAttempts < 2) {
					for (int e = 0; e < 5; ++e) {
						for (int j = 0; j < Epos.size(); ++j) {
							if (Epos[j].x == e) {
								++Col[e];
							}
						}
					}
					for (int j = 0; j < 5; ++j) {
						if (highestCol < Col[j]) {
							highestCol = Col[j];
							bestCol = j + 1;
						}
					}

					if (highestCol == 0 || highestCol == 1 || highestCol == 2) {
						v1 = rand() % 5;
					}
					else {
						v1 = bestCol;
					}
					v2 = 6;
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else if (maxAttempts < 3) {
					for (int e = 0; e < 5; ++e) {
						for (int j = 0; j < Epos.size(); ++j) {
							if (Epos[j].x == e) {
								++Col[e];
							}
						}
					}
					for (int j = 0; j < 5; ++j) {
						if (highestCol < Col[j]) {
							highestCol = Col[j];
							bestCol = j + 1;
						}
					}

					Col[bestCol] = 0;

					for (int j = 0; j < 5; ++j) {
						if (highestCol < Col[j]) {
							highestCol = Col[j];
							bestCol = j + 1;
						}
					}

					if (highestCol == 0 || highestCol == 1 || highestCol == 2) {
						v1 = rand() % 5;
					}
					else {
						v1 = bestCol;
					}
					v2 = 7;
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else if (maxAttempts < 4) {
					for (int e = 0; e < 5; ++e) {
						for (int j = 0; j < Epos.size(); ++j) {
							if (Epos[j].x == e) {
								++Col[e];
							}
						}
					}
					for (int j = 0; j < 5; ++j) {
						if (highestCol < Col[j]) {
							highestCol = Col[j];
							bestCol = j + 1;
						}
					}

					Col[bestCol] = 0;

					for (int j = 0; j < 5; ++j) {
						if (highestCol < Col[j]) {
							highestCol = Col[j];
							bestCol = j + 1;
						}
					}

					if (highestCol == 0 || highestCol == 1 || highestCol == 2) {
						v1 = rand() % 5;
					}
					else {
						v1 = bestCol;
					}
					v2 = 6;
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else if (maxAttempts <= 15) {
					size_t v2 = rand() % 1 + 6;
					size_t v1 = rand() % 5;
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else {
					if (p->GetSpirit() >= 400) {
						BuildAI(Grid::EFire, Opos, Epos, p, false);
						return;
					}
				}

				for (int e = 0; e < Opos.size(); ++e) {
					if (Opos[e].x == v1 && Opos[e].y == v2) {
						WhereBuild = nullptr;
						for (int j = 0; j < tested.size(); ++e) {
							if (tested[e].x != v1 && tested[e].y != v2) {
								tested.push_back(Vector2(v1, v2));
								++maxAttempts;
							}
						}
					}
				}
			}

			Ghost* u = new Ghost(GetGame());
			u->SetPos(WhereBuild->GetPos());
			u->SetTile(WhereBuild);
			p->addOwnPos(Selection, bType);
			p->AddSpirit(u->getPrice() * -1);

			if (p->GetSpirit() >= 200) {
				int rep = p->GetSpirit() / 100;
				for (int e = 0; e < rep; ++e) {
					BuildAI(Grid::EGhost, Opos, Epos, p, true);
				}
			}
			break;
		}
		case ETomb: {

			while (WhereBuild == nullptr) {
				size_t v2;
				size_t v1;
				if (maxAttempts <= 10) {
					v2 = 1 + 5;
					v1 = rand() % 5;
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else {
					if (p->GetSpirit() >= 400) {
						BuildAI(Grid::EFire, Opos, Epos, p, false);
						return;
					}
					else {
						int v3 = rand() % 6;
						if (v3 <= 3) {
							BuildAI(Grid::ECrow, Opos, Epos, p, true);
							return;
						}
						else {
							BuildAI(Grid::EGhost, Opos, Epos, p, true);
							return;
						}
					}
				}

				for (int e = 0; e < Opos.size(); ++e) {
					if (Opos[e].x == v1 && Opos[e].y == v2) {
						WhereBuild = nullptr;
						for (int j = 0; j < tested.size(); ++e) {
							if (tested[e].x != v1 && tested[e].y != v2) {
								tested.push_back(Vector2(v1, v2));
								++maxAttempts;
							}
						}
					}
				}
			}

			Tomb* u = new Tomb(GetGame());
			u->SetPos(WhereBuild->GetPos());
			u->SetTile(WhereBuild);
			p->addOwnPos(Selection, bType);
			p->AddSpirit(u->getPrice() * -1);
			break;
		}
		case EFire: {


			while (WhereBuild == nullptr) {
				size_t v2;
				size_t v1;

				int Col[5] = { 0,0,0,0,0 };

				int lowestCol = 50000;
				int bestCol = 0;

				if (maxAttempts <= 5) {
					for (int e = 0; e < Epos.size(); ++e) {
						for (int j = 0; j < 5; ++j) {
							if (Epos[e].y = j) {
								++Col[j];
							}
						}
					}
					for (int j = 0; j < 5; ++j) {
						if (lowestCol > Col[j]) {
							lowestCol = Col[j];
							bestCol = j + 1;
						}
					}

					v1 = bestCol;
					v2 = 5;
					for (int e = 0; e < Opos.size(); ++e) {
						if (Opos[e].x == v1 && Opos[e].y == v2) {
							tested.push_back(Vector2(v1, v2));
							Col[bestCol] = 0;
							for (int j = 0; j < 5; ++j) {
								if (lowestCol > Col[j]) {
									lowestCol = Col[j];
									bestCol = j + 1;
								}
							}
							v1 = bestCol;
							for (int j = 0; j < Opos.size(); ++j) {
								if (Opos[j].x == v1 && Opos[j].y == v2) {
									v1 = rand() % 5;
									break;
								}
							}
						}

					}
					WhereBuild = m_Tiles[v1][v2];
					Selection = Vector2(v1, v2);
				}
				else {
					int v3 = rand() % 10;
					if (v3 < 2) {
						BuildAI(Grid::ECrow, Opos, Epos, p, true);
						return;
					}
					else if (v3 < 4) {
						BuildAI(Grid::ETomb, Opos, Epos, p, true);
						return;
					}
					else if (v3 < 8) {
						BuildAI(Grid::EGhost, Opos, Epos, p, true);
						return;
					}
					else if (v3 < 10) {
						BuildAI(Grid::ENeCrow, Opos, Epos, p, true);
						return;
					}
				}

				for (int e = 0; e < Opos.size(); ++e) {
					if (Opos[e].x == v1 && Opos[e].y == v2) {
						WhereBuild = nullptr;
						for (int j = 0; j < tested.size(); ++e) {
							if (tested[e].x != v1 && tested[e].y != v2) {
								tested.push_back(Vector2(v1, v2));
								++maxAttempts;
							}
						}
					}
				}
			}

			Fire* u = new Fire(GetGame());
			u->SetPos(WhereBuild->GetPos());
			u->SetTile(WhereBuild);
			p->addOwnPos(Selection, bType);
			p->AddSpirit(u->getPrice() * -1);
			break;
		}
		}

		if (recursive) {
			int v1 = rand() % 20 + 1;

			if (p->GetSpirit() >= 150) {
				if (v1 < 10) {
					Opos.push_back(Vector2(Selection.y, Selection.x));
					BuildAI(Grid::EGhost, Opos, Epos, p, true);
				}
				else {
					Opos.push_back(Vector2(Selection.y, Selection.x));
					BuildAI(Grid::ENeCrow, Opos, Epos, p, true);
				}
			}
			else if (p->GetSpirit() >= 50) {
				v1 += p->getNCrows();
				if (v1 < 16) {
					Opos.push_back(Vector2(Selection.y, Selection.x));
					BuildAI(Grid::ENeCrow, Opos, Epos, p, true);
				}
			}

			if (p->GetSpirit() >= 400) {
				if (v1 > 5 && v1 < 10) {
					Opos.push_back(Vector2(Selection.y, Selection.x));
					BuildAI(Grid::ETomb, Opos, Epos, p, true);
				}
				else if (v1 > 10 && v1 < 15) {
					Opos.push_back(Vector2(Selection.y, Selection.x));
					BuildAI(Grid::ECrow, Opos, Epos, p, true);
				}
			}

			if (p->GetSpirit() >= 500) {
				if (v1 > 15) {
					Opos.push_back(Vector2(Selection.y, Selection.x));
					BuildAI(Grid::EFire, Opos, Epos, p, false);
				}
			}
		}
	}
}