#include "UI.h"
#include "SpriteComp.h"
#include "TextComponent.h"
#include "Game.h"

/// -----------------------
/// This scripts holds all the code pertinent to UI elements
/// -----------------------

namespace Engine
{
	UI::UI(Game* game) :
		Actor(game)
	{
		SpriteComp* sc = new SpriteComp(this);
		sc->SetTexture(game->GetTexture("src/Assets/UI.png"));

		SetPos(Vector2(576, 360));

	}

	UI::~UI()
	{

	}

	void UI::UpdateActor(float deltaTime)
	{
		Actor::UpdateActor(deltaTime);

	}

	Selector::Selector(Game* game) :
		Actor(game)
	{
		SpriteComp* sc = new SpriteComp(this);
		sc->SetTexture(game->GetTexture("src/Assets/Select.png"));

		SetPos(Vector2(-200, -200));

	}

	Selector::~Selector()
	{

	}

	void Selector::UpdateActor(float deltaTime)
	{
		Actor::UpdateActor(deltaTime);
	}

	Dot::Dot(Game* game) :
		Actor(game)
	{
		SpriteComp* sc = new SpriteComp(this);
		sc->SetTexture(game->GetTexture("src/Assets/Point.png"));

		SetPos(Vector2(-200, -200));

	}

	Dot::~Dot()
	{

	}

	void Dot::UpdateActor(float deltaTime)
	{
		Actor::UpdateActor(deltaTime);
	}

	TextPlate::TextPlate(Game* game) :
		Actor(game)
	{
		tc = new TextComponent(this);
	}

	TextPlate::~TextPlate()
	{

	}

	void TextPlate::UpdateActor(float deltaTime)
	{
		Actor::UpdateActor(deltaTime);
	}

	void TextPlate::UpdateText(std::string s) {
		tc->SetText(s);
	}

	void TextPlate::IncreaseWidth(int e) {
		tc->setTextWi(e);
	}
}