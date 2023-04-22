#pragma once
#include "Component.h"
#include "SDL.h"

namespace Engine 
{
	class SpriteComp : public Component {
	public:
		// DrawOrder from Front 1 to back 100
		SpriteComp(class Actor* owner, int drawOrder = 100);
		~SpriteComp();

		virtual void Draw(SDL_Renderer* render);
		virtual void SetTexture(SDL_Texture* texture);

		void flip();

		int GetDrawOrder() const { return m_DrawOrder; }
		int getTextWi() const { return m_TexWi; }
		int getTextHi() const { return m_TexHi; }
	private:
		SDL_Texture* m_Texture;
		bool m_isFlipped;
		int m_DrawOrder;
		int m_TexWi;
		int m_TexHi;
	};
}