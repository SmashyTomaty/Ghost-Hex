#include "TextComponent.h"
#include "Actor.h"
#include "Game.h"

namespace Engine {
	TextComponent::TextComponent(Actor* owner, int drawOrder) :
		Component(owner),
		m_Texture(nullptr),
		m_DrawOrder(drawOrder),
		m_TexWi(90),
		m_TexHi(30)
	{
		m_Owner->GetGame()->AddText(this);
	}

	TextComponent::~TextComponent()
	{
		m_Owner->GetGame()->RemoveText(this);
	}

	void TextComponent::Draw(SDL_Renderer* render)
	{
		TTF_Font* m_Font = TTF_OpenFont("src/Assets/Emulogic-zrEw.ttf", 20);
		m_Surf = TTF_RenderText_Solid(m_Font, m_String.c_str(), SDL_Color{ 255, 255, 255 });
		m_Texture = SDL_CreateTextureFromSurface(render, m_Surf);

			SDL_Rect r;
			r.w = static_cast<int>(m_TexWi * m_Owner->GetScale());
			r.h = static_cast<int>(m_TexHi * m_Owner->GetScale());

			r.x = static_cast<int>(m_Owner->GetPos().x - r.w / 2);
			r.y = static_cast<int>(m_Owner->GetPos().y - r.h / 2);

			SDL_RenderCopy(render, m_Texture, NULL, &r);
	}
}
