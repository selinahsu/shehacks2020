#include "TextRenderComponent.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <sstream>
#include "GameEngine/GameEngineMain.h"

#define MAX_TIME 60

GameEngine::TextRenderComponent::TextRenderComponent()
{
	std::string filePath;
	filePath.append("Resources/img/");
	filePath.append("arial.ttf");
	if (!m_font.loadFromFile(filePath))
	{
		// error...
	}
}


GameEngine::TextRenderComponent::~TextRenderComponent()
{
}


void GameEngine::TextRenderComponent::Render(sf::RenderTarget* target)
{
	//__super::Render(target);

	sf::Text text;

	// select the font
	text.setFont(m_font); // font is a sf::Font

	sf::Time a = m_clock.getElapsedTime();
	int elapsedSeconds = a.asSeconds();
	int remainingSeconds = MAX_TIME - elapsedSeconds;
	if (remainingSeconds < 0)
	{
		//m_clock.restart();
		GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->close();
	}
	text.setString(std::to_string(remainingSeconds));
	target->draw(text);
}