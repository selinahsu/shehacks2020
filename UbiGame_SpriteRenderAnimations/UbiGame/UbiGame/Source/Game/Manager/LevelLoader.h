#pragma once

#include "GameEngine/Util/TextureManager.h"
#include "SFML/System/Vector2.hpp"

namespace GameEngine { class Entity; }


namespace Game
{
	class LevelLoader
	{
	public:
		~LevelLoader();

		static LevelLoader* GetInstance() { if (!sm_instance) sm_instance = new LevelLoader(); return sm_instance; }
		void LoadLevelTexture(GameEngine::eTexture::type texture);

		GameEngine::Entity* GetPlayer() { return m_player; }

	private:
		void SpawnObstacle(sf::Vector2i coords);
		void SpawnPlayer(sf::Vector2i coords);
		void SpawnItem(sf::Vector2i coords);
		void SpawnFinish(sf::Vector2i coords);

		LevelLoader();
		static LevelLoader* sm_instance;

		float m_levelGridSize;

		GameEngine::Entity* m_player;
	};
}