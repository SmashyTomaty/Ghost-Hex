#include "SpriteComp.h"
#include "Actor.h"
#include "Game.h"

namespace Engine {
	SpriteComp::SpriteComp(Actor* owner, int drawOrder) :
		Component(owner),
		m_Texture(nullptr),
		m_DrawOrder(drawOrder),
		m_isFlipped(false),
		m_TexWi(0),
		m_TexHi(0)
	{
		m_Owner->GetGame()->AddSprite(this);
	}

	SpriteComp::~SpriteComp()
	{
		m_Owner->GetGame()->RemoveSprite(this);
	}

	void SpriteComp::Draw(SDL_Renderer* render)
	{
		if (m_Texture) {
			SDL_Rect r;
			r.w = static_cast<int>(m_TexWi * m_Owner->GetScale());
			r.h = static_cast<int>(m_TexHi * m_Owner->GetScale());

			r.x = static_cast<int>(m_Owner->GetPos().x - r.w / 2);
			r.y = static_cast<int>(m_Owner->GetPos().y - r.h / 2);

			if (!m_isFlipped) {
				SDL_RenderCopyEx(render, m_Texture, nullptr, &r,
					-CustomMath::ToDegrees(m_Owner->GetRota()), nullptr, SDL_FLIP_NONE);
			}
			else {
				SDL_RenderCopyEx(render, m_Texture, nullptr, &r,
					-CustomMath::ToDegrees(m_Owner->GetRota()), nullptr, SDL_FLIP_HORIZONTAL);
			}
		}
	}

	void SpriteComp::SetTexture(SDL_Texture* texture)
	{
		m_Texture = texture;
		SDL_QueryTexture(texture, nullptr, nullptr, &m_TexWi, &m_TexHi);
	}

	void SpriteComp::flip() {
		m_isFlipped = true;
	}
}
