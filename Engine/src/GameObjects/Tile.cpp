#include "Tile.h"
#include "SpriteComp.h"
#include <string>
#include "Game.h"

Engine::Tile::Tile(Game* game) :
	Actor(game), m_Sprite(nullptr), m_TileState(EDefault)
{
	m_Sprite = new SpriteComp(this);
	UpdateTexture();
}

void Engine::Tile::SetTileState(TileState state)
{
	m_TileState = state;
	UpdateTexture();
}

void Engine::Tile::setSelected()
{
	m_Selected = !m_Selected;
	UpdateTexture();
}

void Engine::Tile::UpdateTexture()
{
	std::string path;
	switch (m_TileState) {
	case EStart:
		path = "src/Assets/TileGrey.png";
		break;
	case EBase:
		path = "src/Assets/TileGrey.png";
		break;
	case EPath:
		if (m_Selected)
			path = "src/Assets/TileGreySelected.png";
		else
			path = "src/Assets/TileGrey.png";
		break;
	case EDefault2:
		if (m_Selected)
			path = "src/Assets/TileBrownSelected.png";
		else
			path = "src/Assets/TileBrown.png";
		break;
	case EDefault:
	default:
		if (m_Selected)
			path = "src/Assets/TileGreenSelected.png";
		else
			path = "src/Assets/TileGreen.png";
		break;
	}

	m_Sprite->SetTexture(GetGame()->GetTexture(path));
}
