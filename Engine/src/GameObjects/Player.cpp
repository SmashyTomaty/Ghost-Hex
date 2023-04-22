#include "Player.h"
#include "Game.h"

namespace Engine {

	Player::Player(Game* game) : Actor(game)
	{
	}

	Player::~Player()
	{
	}

	void Player::UpdateActor(float deltaTime)
	{
		Actor::UpdateActor(deltaTime);
	}

	void Player::addEnemPos(Vector2 v, Grid::buildType b)
	{
		for (int e = 0; e < EnemPos.size(); ++e) {
			if (v.x == EnemPos[e].x && v.y == EnemPos[e].y) {
				return;
			}
		}
		EnemPos.emplace_back(v);
		build.emplace_back(b);
	}

	void Player::removeEnemPos(Vector2 v)
	{
		auto iter = EnemPos.begin();

		for (; iter < EnemPos.end(); ++iter) {
			if (iter->x == v.x && iter->y == v.y) {
				EnemPos.erase(iter);
				return;
			}
		}
	}


	void Player::addOwnPos(Vector2 v, Grid::buildType b)
	{
		Vector2 newV = Vector2(v.y, v.x);
		OwnPos.emplace_back(newV);
		if (b == Grid::ENeCrow) {
			++m_Necrows;
		}
	}

	void Player::RemoveNCrowFromBCount() {
		--m_Necrows;
	}

	void Player::removeOwnPos(Vector2 v)
	{
		auto iter = OwnPos.begin();

		for (; iter < OwnPos.end(); ++iter) {
			if (iter->x == v.x && iter->y == v.y) {
				OwnPos.erase(iter);
				return;
			}
		}
	}

	// This is my attempt at building the AI, feel free to try improving it!
	Grid::buildType Player::whatBuild()
	{
		int builds[5] = { 0,0,0,0,0 };
		Grid::buildType b = Grid::ENeCrow;

		int higest;

		for (int e = 0; e < build.size(); ++e) {
			switch (build[e])
			{
			 case Grid::ENeCrow: {
				 ++builds[0];
				break;
		  	 }
			 case Grid::ECrow: {
				++builds[1];
				break;
			 }
			 case Grid::EGhost: {
				++builds[2];
				break;
			 }
			 case Grid::ETomb: {
				++builds[3];
				break;
			 }
			 case Grid::EFire: {
				++builds[4];
				break;
			 }
			}
		}

		//if (build.size() < 2 && builds[2] > 0) {
		//	return b;
		//}

		//if (build.size() > 2 && builds[2] + builds[1] > 0) { //This is here so the AI is agressive, even if the player spams Ncrows
		//	higest = builds[1];
		//	if (m_SpiritCount > 100) {
		//		int v1 = rand() % 3 + 1;
		//		if (v1 == 1) {
		//			b = Grid::EGhost;
		//		}
		//	}
		//}
		//else {
		//	higest = builds[0];
		//}

		higest = 0;

		for (int e = 0; e < 5; ++e) {
			if (higest < builds[e]) {
				higest = builds[e];
				if (e == 0) {
					if (m_SpiritCount >= 100) {
						int v1 = rand() % 2 + 1;
						if (v1 == 1) {
							b = Grid::ENeCrow;
						}
						else {
							b = Grid::EGhost;
						}
					}
				}
				else if (e == 2) {
					if (m_SpiritCount > 420) {
						b = Grid::EFire;
					}
					else if (m_SpiritCount >= 300) {
						int v1 = rand() % 4 + 1;
						if (v1 <= 1) {
							b = Grid::ETomb;
						}
						else if (v1 < 3) {
							b = Grid::EGhost;
						}
						else {
							b = Grid::ECrow;
						}
					}
					else if(m_SpiritCount >= 100) {
						b = Grid::EGhost;
					}
					else if (m_Necrows >= 6) {
						b = Grid::EDef;
					}
				}
				else if (e == 1) {
					if (m_SpiritCount > 300) {
						b = Grid::ETomb;
					} //If Agressive, it should place the Necrow as close to the front.
				}
				else if (e == 3) {
					if (m_SpiritCount >= 300) {
						b = Grid::ECrow;
					}
					else if (m_SpiritCount >= 100) {
						b = Grid::EGhost;
					}
					else if (m_Necrows >= 6) {
						b = Grid::EDef;
					}
				}
				else if (e == 4) {
					int sum = builds[2];
					if (sum == 0) {
						if (m_SpiritCount >= 300) {
							b = Grid::ECrow;
						}
						else if (m_SpiritCount >= 100) {
							b = Grid::EGhost;
						}
						else if (m_Necrows >= 4) {
							b = Grid::EDef;
						}
					}
					else {
						if (build[2] == 0 && builds[1] == 0) {
							if (m_SpiritCount >= 400) {
								b = Grid::EFire;
							}
							else if (m_SpiritCount >= 300) {
								b = Grid::ECrow;
							}
							else if (m_SpiritCount >= 100) {
								b = Grid::EGhost;
							}
							else if (m_Necrows >= 4) {
								b = Grid::EDef;
							}
						}
						else {
							if (builds[2] > builds[1]) {
								if (m_SpiritCount >= 300) {
									b = Grid::ETomb;
								}
								else if (m_SpiritCount >= 100) {
									b = Grid::EGhost;
								}
								else if (m_Necrows >= 4) {
									b = Grid::EDef;
								}
							}
							else {
								if (m_SpiritCount >= 300) {
									b = Grid::ECrow;
								}
								else if (m_SpiritCount >= 100) {
									b = Grid::EGhost;
								}
								else if (m_Necrows >= 4) {
									b = Grid::EDef;
								}
							}
						}
					}
				}
			}
		}

		if (OwnPos.size() > 7 && b == Grid::EGhost && m_SpiritCount >= 300) {
			b = Grid::ECrow;
		}

		if ((higest == builds[0] && builds[0] > 7) || (higest == builds[0] && m_Necrows > 7)) {
			if (m_SpiritCount > 100) {
				b = Grid::EGhost;
			}
		}

		if (builds[1] + builds[2] == 0) {
			b = Grid::ENeCrow;
		}

		return b;
	}
}