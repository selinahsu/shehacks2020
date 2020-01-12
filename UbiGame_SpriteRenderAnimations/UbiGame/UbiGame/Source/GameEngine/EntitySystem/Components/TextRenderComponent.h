#pragma once
#include "GameEngine\EntitySystem\Components\RenderComponent.h"

namespace GameEngine
{
	class TextRenderComponent : public RenderComponent
	{
	public:
		TextRenderComponent();
		~TextRenderComponent();

		virtual void Render(sf::RenderTarget* target) override;
	private:
		sf::Font m_font;
		sf::Text m_text;
		sf::Clock m_clock;
	};
}




