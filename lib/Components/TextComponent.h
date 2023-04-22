#pragma once
#include "Component.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

namespace Engine
{
	class TextComponent : public Component {
	public:
		// DrawOrder from Front 1 to back 100
		TextComponent(class Actor* owner, int drawOrder = 89);
		~TextComponent();

		virtual void Draw(SDL_Renderer* render);
		
		void SetText(std::string s) { m_String = s; }

		int GetDrawOrder() const { return m_DrawOrder; }
		int getTextWi() const { return m_TexWi; }
		int getTextHi() const { return m_TexHi; }
		void setTextWi(int f) { m_TexWi = f; }
	private:
		SDL_Texture* m_Texture;
		SDL_Surface* m_Surf;
		TTF_Font* m_Font;
		std::string m_String;
		int m_DrawOrder;
		int m_TexWi;
		int m_TexHi;
	};
}