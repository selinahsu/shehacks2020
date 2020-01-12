#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\CollidablePhysicsComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"

#include "Game\Components\PlayerMovementComponent.h"
#include "Game\Manager\LevelLoader.h"
#include "GameEngine\EntitySystem\Components\TextRenderComponent.h"

#include <ctime>

using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_levelGridSize(50.f)
{
	//CreatePlayer();
	//CreateObstacle();
	CreateText();

	LevelLoader::GetInstance()->LoadLevelTexture(GameEngine::eTexture::Level);
}


GameBoard::~GameBoard()
{

}


void GameBoard::CreatePlayer()
{
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	
	m_player->SetPos(sf::Vector2f(150.f, 150.f));
	m_player->SetSize(sf::Vector2f(50.f, 50.f));
	
	//Render
	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
												      (m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	spriteRender->SetFillColor(sf::Color::Transparent);
	spriteRender->SetTexture(GameEngine::eTexture::Player);

	//Movement
	m_player->AddComponent<PlayerMovementComponent>();
	m_player->AddComponent<GameEngine::AnimationComponent>();

	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}

void GameBoard::CreateObstacle()
{
	GameEngine::Entity* obstacle = new GameEngine::Entity();	
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);

	obstacle->SetPos(sf::Vector2f(350.f, 150.f));
	obstacle->SetSize(sf::Vector2f(150.f, 150.f));

	//Render
	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
		(obstacle->AddComponent<GameEngine::SpriteRenderComponent>());

	spriteRender->SetFillColor(sf::Color::Transparent);
	spriteRender->SetTexture(GameEngine::eTexture::Obstacle);

	obstacle->AddComponent<GameEngine::CollidableComponent>();
}

void GameBoard::CreateText()
{
	GameEngine::Entity* text = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(text);

	text->SetPos(sf::Vector2f(350.f, 150.f));
	text->SetSize(sf::Vector2f(150.f, 150.f));

	//Render
	GameEngine::TextRenderComponent* textRender = static_cast<GameEngine::TextRenderComponent*>
		(text->AddComponent<GameEngine::TextRenderComponent>());

	textRender->SetFillColor(sf::Color::Black);
}

void GameBoard::Update()
{	
	
}