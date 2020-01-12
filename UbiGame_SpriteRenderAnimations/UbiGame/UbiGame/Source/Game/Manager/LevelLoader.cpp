
#include "LevelLoader.h"

#include <assert.h>
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Color.hpp"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "../Components/PlayerMovementComponent.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/CollectComponent.h"
#include "GameEngine/EntitySystem/Components/FinishComponent.h"

//#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"

using namespace Game;

LevelLoader* LevelLoader::sm_instance = nullptr;
std::string items[6] = { "cash.png", "id.png", "leaf.png", "log.png", "meds.png", "phone.png" };

LevelLoader::LevelLoader()
	: m_levelGridSize(30.f)
{

}

void LevelLoader::LoadLevelTexture(GameEngine::eTexture::type texture)
{
	sf::Texture* levelTexture = GameEngine::TextureManager::GetInstance()->GetTexture(texture);
	assert(levelTexture);

	sf::Image levelImage = levelTexture->copyToImage();

	for (unsigned int y = 0; y < levelImage.getSize().y; y++)
	{
		for (unsigned int x = 0; x < levelImage.getSize().x; x++)
		{
			sf::Color pixelColor = levelImage.getPixel(x, y);			

			if (pixelColor.b == 255 && pixelColor.r == 0 && pixelColor.g == 0)
				SpawnPlayer(sf::Vector2i(x, y));
			else if (pixelColor.b == 0 && pixelColor.r == 0 && pixelColor.g == 0)
				SpawnObstacle(sf::Vector2i(x, y));
			else if (pixelColor.b == 0 && pixelColor.r == 255 && pixelColor.g == 0)
				SpawnItem(sf::Vector2i(x, y));
			else if (pixelColor.b == 0 && pixelColor.r == 0 && pixelColor.g == 255)
				SpawnFinish(sf::Vector2i(x, y));
		}
	}
}


void LevelLoader::SpawnObstacle(sf::Vector2i coords)
{
	float spawnPosX = coords.x * m_levelGridSize + (m_levelGridSize / 2.f);
	float spawnPosY = coords.y * m_levelGridSize + (m_levelGridSize / 2.f);

	GameEngine::Entity* obstacle = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);

	obstacle->SetPos(sf::Vector2f(spawnPosX, spawnPosY));
	obstacle->SetSize(sf::Vector2f(m_levelGridSize, m_levelGridSize));

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>
															(obstacle->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetTexture(GameEngine::eTexture::Obstacle);
	render->SetFillColor(sf::Color::Transparent);

	obstacle->AddComponent<GameEngine::CollidableComponent>();
}


void LevelLoader::SpawnPlayer(sf::Vector2i coords)
{
	float spawnPosX = coords.x * m_levelGridSize + (m_levelGridSize / 2.f);
	float spawnPosY = coords.y * m_levelGridSize + (m_levelGridSize / 2.f);

	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(spawnPosX, spawnPosY));
	m_player->SetSize(sf::Vector2f(50.f, 50.f));

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>
		(m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetTexture(GameEngine::eTexture::Player);
	render->SetFillColor(sf::Color::Transparent);

	m_player->AddComponent<PlayerMovementComponent>();
	m_player->AddComponent<GameEngine::AnimationComponent>();
	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}

void LevelLoader::SpawnItem(sf::Vector2i coords)
{
	float spawnPosX = coords.x * m_levelGridSize + (m_levelGridSize / 2.f);
	float spawnPosY = coords.y * m_levelGridSize + (m_levelGridSize / 2.f);

	GameEngine::Entity* item = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(item);

	item->SetPos(sf::Vector2f(spawnPosX, spawnPosY));
	item->SetSize(sf::Vector2f(m_levelGridSize, m_levelGridSize));

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>
		(item->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetTexture(GameEngine::eTexture::Item);
	render->SetFillColor(sf::Color::Transparent);

	item->AddComponent<GameEngine::CollectComponent>();
}

void LevelLoader::SpawnFinish(sf::Vector2i coords)
{
	float spawnPosX = coords.x * m_levelGridSize + (m_levelGridSize / 2.f);
	float spawnPosY = coords.y * m_levelGridSize + (m_levelGridSize / 2.f);

	GameEngine::Entity* item = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(item);

	item->SetPos(sf::Vector2f(spawnPosX, spawnPosY));
	item->SetSize(sf::Vector2f(m_levelGridSize, m_levelGridSize));

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>
		(item->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetTexture(GameEngine::eTexture::Finish);
	render->SetFillColor(sf::Color::Black);

	item->AddComponent<GameEngine::FinishComponent>();
}

LevelLoader::~LevelLoader()
{

}

